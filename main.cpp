#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"team.h"
#include<string>
#include<random>
#include<chrono>

/* Choose a winning team from Team1 and Team2 using a bernoulli distribtuion, 
   which favors better seeded teams.*/
Team getWinner(std::default_random_engine &gen, const Team &team1, const Team &team2) {
    int seed1 = team1.getSeed();
    int seed2 = team2.getSeed();
    float p = 1 - seed1/(float)(seed1+seed2);
    std::bernoulli_distribution dist(p);
    if (dist(gen)) {
        return team1;
    }
    return team2;
}

// Choose a random string from str1 and str2 from a random, uniform distribution
std::string randStr(const std::string &str1, const std::string &str2) {
    unsigned randSeed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(randSeed);
    std::uniform_int_distribution<int> dist(0,1);
    int i = dist(gen);
    if (i == 0) {
        return str1;
    }
    return str2;
}

/* Parse team names and seeds from a file and populate a vector
   with the teams. Bracket will be generated from the resulting vector */
std::vector<Team> parseTeams(char* teamFileName) {
    std::vector<Team> teams;
    std::ifstream teamFile(teamFileName);
    std::string line;
    // Each line contains a team and a seed. Parse the line into a Team object
    while (std::getline(teamFile, line)) {
        size_t delim = line.find(" ");
        std::string name = line.substr(delim+1);
        std::string seedStr = line.substr(0, delim);
        int seed;
        std::stringstream seedToInt(seedStr);
        seedToInt >> seed;
        // If the line contains a First Four team pair, randomly choose a winner
        size_t nameIdx = name.find("/");
        if (nameIdx != std::string::npos) {
            std::string name1 = name.substr(0, nameIdx);
            std::string name2 = name.substr(nameIdx+1);
            name = randStr(name1, name2);
        }
        Team newTeam(name, seed);
        teams.push_back(newTeam);
    }
    teamFile.close();
    return teams;
}

// Generate the bracket by choosing a winner for every pair of teams.
std::vector<std::vector<Team> > genBracket(const std::vector<Team> &teams) {
    unsigned randSeed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(randSeed);
    std::vector<Team> winners = teams;
    std::vector<std::vector<Team> > results;
    // Winners will continue to be chosen until one winning team remains
    while (winners.size() >= 2) {
        std::vector<Team> newWinners; // Create a new vector for each round
        for (size_t i = 0; i < winners.size(); i+=2) {
            Team winner = getWinner(gen, winners[i], winners[i+1]);
            newWinners.push_back(winner);
        }
        winners = newWinners;
        results.push_back(winners);
    }
    return results;
}

// print the bracket into a file with the specified name
void printBracket(const std::vector<std::vector<Team> > &b, char* outName) {
    std::ofstream outFile(outName);
    for (size_t i = 0; i < b.size(); ++i) {
        outFile << "Round " << i + 1 << " Winners:" << std::endl;
        for (size_t j = 0; j < b[i].size(); ++j) {
            outFile << b[i][j].getName() << std::endl;
        }
        outFile << std::endl;
    }
    outFile.close();
} 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of arguments" << std::endl;
        exit(1);
    }
    std::vector<Team> teams = parseTeams(argv[1]);
    std::vector<std::vector<Team> > b = genBracket(teams);
    printBracket(b, argv[2]);
    return 0;
}
