#pragma once
#include "Entity.h"

class Monster : public Entity {
private:
    int maxHp;
    int hp;
    bool alive;
public:
    Monster(const std::string& name, int hp);
    void decreaseHp(int amount);
    void printBar() const;
    bool isAlive() const;
    int getHp() const;
    void kill();
    void info() const override;
    std::string getName() const;
    void increaseHp(int amount);

};
