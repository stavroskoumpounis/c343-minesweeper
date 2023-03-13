#include <string>

class Player {
private:
    std::string name;
//    int timer;
//    int score;
//    hasWon,hasLost
public:
    explicit Player(std::string name) : name(std::move(name)) {}

    const std::string &getName() const { return name; }

    void setName(const std::string &name) { this->name = name; }
};