#include"team.h"
Team::Team(const std::string &name, int seed) {
    _name = name;
    _seed = seed;    
}

std::string Team::getName() const {
    return std::string(_name);
}

int Team::getSeed() const {
    return _seed;
}
