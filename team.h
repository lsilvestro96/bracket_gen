#include<string>

/* A simple class that represents a team.
   Contains the team name and its seed */
class Team {
    private:
        std::string _name;
        int _seed;
    public:
        Team(const std::string &name, int seed);
        std::string getName() const;
        int getSeed() const;
};
