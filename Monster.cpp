#include "Monster.h"
#include <iostream>
using namespace std;

Monster::Monster(const string& name, int hp) : Entity(name), maxHp(hp), hp(hp), alive(true) {}

void Monster::decreaseHp(int amount) {
    if (!alive) return;
    hp -= amount;
    if (hp <= 0) {
        hp = 0;
        alive = false;
    }
}
void Monster::increaseHp(int amount) {
    if (!alive) return;
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}


void Monster::printBar() const {
    int width = 50;
    int filled = static_cast<int>((double)hp / maxHp * width);
    cout << name << " [";
    for (int i = 0; i < width; ++i)
        cout << (i < filled ? "#" : " ");
    cout << "] " << hp << "/" << maxHp << endl;
}

bool Monster::isAlive() const { return alive; }
int Monster::getHp() const { return hp; }
void Monster::kill() { alive = false; }
void Monster::info() const { printBar(); }
string Monster::getName() const { return name; }
