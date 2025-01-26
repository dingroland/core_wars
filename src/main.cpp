#include "../libs/galib/ga/ga.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

// Constants for Core War simulation
const int CORESIZE = 8000;
const int MAXLENGTH = 100;

// Valid Redcode opcodes, modifiers, and addressing modes
const std::vector<std::string> OPCODES = {
    "DAT", "MOV", "ADD", "SUB", "MUL", "DIV", "MOD",
    "JMP", "JMZ", "JMN", "DJN", "SPL", "SLT", "CMP",
    "SEQ", "SNE", "NOP", "LDP", "STP"
};

const std::vector<std::string> MODIFIERS = {
    ".A", ".B", ".AB", ".BA", ".F", ".X", ".I"
};

const std::vector<std::string> ADDRESSING_MODES = {
    "#", "$", "@", "<", ">", "*", "{", "}"
};

// Function to generate a random Redcode instruction
std::string generateRandomInstruction() {
    std::ostringstream instruction;

    // Randomly choose an opcode
    instruction << OPCODES[rand() % OPCODES.size()];

    // Randomly add a modifier
    if (rand() % 2) { // 50% chance to add a modifier
        instruction << MODIFIERS[rand() % MODIFIERS.size()];
    }

    // Generate two operands with random addressing modes and values
    int operandA = rand() % CORESIZE;
    int operandB = rand() % CORESIZE;
    instruction << " " << ADDRESSING_MODES[rand() % ADDRESSING_MODES.size()] << operandA;
    instruction << ", " << ADDRESSING_MODES[rand() % ADDRESSING_MODES.size()] << operandB;

    return instruction.str();
}

// Function to generate a random warrior
std::string generateRandomWarrior(int length) {
    if (length <= 0) {
        throw std::invalid_argument("Warrior length must be greater than 0.");
    }

    std::ostringstream warrior;
    warrior << ";redcode\n";
    warrior << ";name RandomWarrior\n";
    warrior << ";author GA\n";

    for (int i = 0; i < length; ++i) {
        warrior << generateRandomInstruction() << "\n";
    }

    return warrior.str();
}

// Function to log a warrior to file and console
void logWarrior(const std::string& warriorCode) {
    if (warriorCode.empty()) {
        std::cerr << "Error: Attempted to log an empty warrior.\n";
        return;
    }

    // Write to log file
    std::ofstream logFile("warrior_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << warriorCode;
        logFile << "---------------------------------------------\n";
        logFile.close();
    } else {
        std::cerr << "Error: Unable to open warrior_log.txt for writing.\n";
    }

    // Write to console
    std::cout << "Warrior Logged:\n" << warriorCode << "\n";
}

// Fitness function to evaluate a warrior's performance
float evaluateFitness(GAGenome& g) {
    GA1DArrayGenome<std::string>& genome = static_cast<GA1DArrayGenome<std::string>&>(g);

    // Combine genome into a single warrior
    std::ostringstream warriorCode;
    warriorCode << ";redcode\n";
    warriorCode << ";name EvaluatedWarrior\n";
    warriorCode << ";author GA\n";

    for (int i = 0; i < genome.size(); ++i) {
        const std::string& gene = genome.gene(i);
        if (gene.empty()) {
            std::cerr << "Error: Genome contains an empty gene at index " << i << ".\n";
            return -1.0f; // Penalize invalid genes
        }
        warriorCode << gene << "\n";
    }

    std::string warrior = warriorCode.str();
    logWarrior(warrior);

    // Save to warrior.red for pMARS simulation
    std::ofstream warriorFile("warrior.red");
    if (warriorFile.is_open()) {
        warriorFile << warrior;
        warriorFile.close();
    } else {
        std::cerr << "Error: Unable to open warrior.red for writing.\n";
        return -1.0f;
    }

    // Run pMARS simulation
    std::string command = "./pmars -r 10 warrior.red test_eval.red > results.txt";
    int ret = system(command.c_str());
    if (ret != 0) {
        std::cerr << "Error: pMARS simulation failed.\n";
        return -1.0f;
    }

    // Parse results.txt for fitness scores
    std::ifstream resultsFile("results.txt");
    if (!resultsFile.is_open()) {
        std::cerr << "Error: Unable to open results.txt for parsing.\n";
        return -1.0f;
    }

    std::string line;
    int wins = 0, losses = 0, ties = 0;
    while (std::getline(resultsFile, line)) {
        if (line.find("Win") != std::string::npos) wins++;
        if (line.find("Loss") != std::string::npos) losses++;
        if (line.find("Tie") != std::string::npos) ties++;
    }
    resultsFile.close();

    std::cout << "Fitness: Wins=" << wins << ", Losses=" << losses << ", Ties=" << ties << "\n";

    return wins - losses + 0.5f * ties; // Fitness formula
}

int main() {
    const int genomeLength = 10; // Number of warrior instructions
    const int populationSize = 50; // Population size
    const int generations = 100; // Number of generations

    srand(static_cast<unsigned>(time(nullptr))); // Seed RNG

    // Create genome and initialize with random instructions
    GA1DArrayGenome<std::string> genome(genomeLength, evaluateFitness);
    for (int i = 0; i < genomeLength; ++i) {
        genome.gene(i, generateRandomInstruction());
    }

    // Log the initial warrior
    std::ostringstream initialWarrior;
    for (int i = 0; i < genomeLength; ++i) {
        initialWarrior << genome.gene(i) << "\n";
    }
    logWarrior(initialWarrior.str());

    // Set up and run the genetic algorithm
    GASimpleGA ga(genome);
    ga.populationSize(populationSize);
    ga.nGenerations(generations);
    ga.pMutation(0.01f);
    ga.pCrossover(0.9f);
    ga.elitist(gaTrue);

    ga.evolve();

    // Save the best warrior
    const GA1DArrayGenome<std::string>& best = static_cast<const GA1DArrayGenome<std::string>&>(ga.statistics().bestIndividual());
    std::ostringstream bestWarrior;
    bestWarrior << ";redcode\n";
    bestWarrior << ";name BestWarrior\n";
    bestWarrior << ";author GA\n";
    for (int i = 0; i < best.length(); ++i) {
        bestWarrior << best.gene(i) << "\n";
    }

    std::ofstream bestWarriorFile("best_warrior.red");
    if (bestWarriorFile.is_open()) {
        bestWarriorFile << bestWarrior.str();
        bestWarriorFile.close();
    } else {
        std::cerr << "Error: Unable to open best_warrior.red for writing.\n";
    }

    std::cout << "Best Warrior:\n" << bestWarrior.str() << "\n";

    return 0;
}