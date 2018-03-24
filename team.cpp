#include"team.h"

// Constructor
Team::Team(const std::string &name, int seed) {
    _name = name;
    _seed = seed;    
}

// Get the name of the team
std::string Team::getName() const {
    return std::string(_name);
}

// Get the team's seed
int Team::getSeed() const {
    return _seed;
}
