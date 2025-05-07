#pragma once
#include <string>
#include <vector>

struct SmiteResult {
    std::string monsterName;
    bool success;
    int remainingHp;
    int smiteDamage;
    int reactionTimeMs;
};

class ScoreManager {
private:
    std::vector<SmiteResult> results;
public:
    void log(const std::string& name, bool success, int hp, int smiteDmg, int reactionMs);
    void exportCSV(const std::string& filename) const;
};
