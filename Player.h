#pragma once
#include "Entity.h"
#include "Monster.h"
#include <chrono>

class Player : public Entity {
private:
    int killCount;
    std::chrono::steady_clock::time_point lastSmiteTime;
public:
    Player(const std::string& name);
    void smite(Monster& monster, int smiteDamage, int reactionTimeMs);
    void incrementKill();
    void info() const override;
};
