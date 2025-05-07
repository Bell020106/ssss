#include "Test.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#ifdef _WIN32
#include <conio.h>
#define getch _getch
#endif

using namespace std;
using namespace chrono;

void ReactionTester::run() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "\n ���� �ӵ� �׽�Ʈ\n";
    cout << "ȭ�鿡 [GO!]�� �߸� �����̽��ٸ� ��������.\n";
    cout << "�غ� ��...\n";

    int delay = rand() % 3000 + 2000;
    this_thread::sleep_for(milliseconds(delay));

    cout << "\n[GO!]\n";
    auto start = steady_clock::now();

    while (true) {
        if (getch() == ' ') {
            auto end = steady_clock::now();
            int ms = duration_cast<milliseconds>(end - start).count();
            cout << " ���� �ð�: " << ms << "ms\n";
            cout << " ����: " << getGrade(ms) << "\n";
            break;
        }
    }
}

string ReactionTester::getGrade(int ms) {
    if (ms < 150) return "Perfect";
    if (ms < 300) return "Great";
    if (ms < 500) return "Good";
    if (ms < 700) return "Late";
    return "Fail";
}
