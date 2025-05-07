#pragma once
#include <vector>
#include "Monster.h"
#include "Player.h"
#include "Scenario.h"
#include "ScoreManager.h"

class Game {
private:
    std::vector<Monster> monsters;
    Player player;
    Scenario scenario;
    ScoreManager scoreManager;
public:
    Game();
    void start();
};
