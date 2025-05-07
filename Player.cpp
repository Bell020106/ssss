#include "Player.h"
#include <iostream>
using namespace std;
using namespace chrono;

Player::Player(const string& name)
    : Entity(name), killCount(0), lastSmiteTime(steady_clock::now() - seconds(10)) {
}

void Player::incrementKill() {
    killCount++;
}

void Player::smite(Monster& monster, int smiteDamage, int reactionTimeMs) {
    auto now = steady_clock::now();
    auto elapsed = duration_cast<seconds>(now - lastSmiteTime);
    if (elapsed.count() < 7) {
        cout << "강타 재사용 대기 중 (" << (7 - elapsed.count()) << "초 남음)\n";
        return;
    }
    lastSmiteTime = now;

    if (monster.getHp() <= smiteDamage) {
        monster.kill();
        incrementKill();
        cout << ">> 처치 성공! 반응 시간: " << reactionTimeMs << "ms\n";
    }
    else {
        monster.decreaseHp(smiteDamage);
        cout << ">> 실패! 남은 체력: " << monster.getHp()
            << " | 반응 시간: " << reactionTimeMs << "ms\n";
    }
}

void Player::info() const {
    cout << "[플레이어] " << name << " | 총 킬 수: " << killCount << "\n";
}
