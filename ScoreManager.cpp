#include "ScoreManager.h"
#include <fstream>

void ScoreManager::log(const std::string& name, bool success, int hp, int smiteDmg, int reactionMs) {
    results.push_back({ name, success, hp, smiteDmg, reactionMs });
}

void ScoreManager::exportCSV(const std::string& filename) const {
    std::ofstream out(filename);
    out << "Monster,Success,RemainingHp,SmiteDamage,ReactionTimeMs\n";
    for (const auto& r : results) {
        out << r.monsterName << "," << (r.success ? "1" : "0") << "," << r.remainingHp
            << "," << r.smiteDamage << "," << r.reactionTimeMs << "\n";
    }
    out.close();
}
