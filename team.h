#include<string>
class Team {
    private:
        std::string _name;
        int _seed;
    public:
        Team(const std::string &name, int seed);
        std::string getName() const;
        int getSeed() const;
};
