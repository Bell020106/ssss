#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <numeric>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _WIN32
#include <conio.h>
#define getch _getch
#else
#endif

using namespace std;
using namespace chrono;

Game::Game() : player("소환사") {
    monsters.emplace_back("전령", 3000);
    monsters.emplace_back("드래곤", 3500);
    monsters.emplace_back("내셔 남작", 4000);
}

void Game::start() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    default_random_engine rng(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> smiteRange(850, 1100);
    uniform_int_distribution<int> healDist(200, 400);
    uniform_int_distribution<int> damageDist(150, 250);

    vector<int> reactionTimes;
    int totalAttempts = 0, successCount = 0;

    while (true) {
        cout << "\n========== Smite 연습 게임 ==========\n";
        cout << "1. 전령 처치하기\n";
        cout << "2. 드래곤 처치하기\n";
        cout << "3. 내셔 남작 처치하기\n";
        cout << "0. 종료\n";
        cout << "=====================================\n";

        if (totalAttempts > 0) {
            double avg = accumulate(reactionTimes.begin(), reactionTimes.end(), 0.0) / reactionTimes.size();
            double rate = (double)successCount / totalAttempts * 100.0;
            cout << "평균 반응속도: " << (int)avg << "ms, 성공률: " << (int)rate << "%\n";
        }
        else {
            cout << "아직 기록된 연습 결과가 없습니다.\n";
        }

        cout << "번호를 입력하세요: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "게임을 종료합니다.\n";
            break;
        }

        if (choice < 1 || choice > 3) {
            cout << "잘못된 선택입니다. 다시 입력해주세요.\n";
            continue;
        }

        Monster monster = monsters[choice - 1];
        PlaySound(TEXT("전투.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

        bool smiteUsed = false;
        bool smiteWindowOpened = false;
        steady_clock::time_point smiteReadyTime;
        int smiteDamage = smiteRange(rng);

        // 랜덤 데미지
        thread damageThread([&]() {
            while (monster.isAlive()) {
                this_thread::sleep_for(seconds(1));
                int dmg = damageDist(rng);
                monster.decreaseHp(dmg);
                if (!smiteWindowOpened && monster.getHp() <= smiteDamage) {
                    smiteReadyTime = steady_clock::now();
                    smiteWindowOpened = true;
                }
            }
            });

        // 랜덤 회복
        thread healThread([&]() {
            while (monster.isAlive()) {
                this_thread::sleep_for(seconds(4));
                int heal = healDist(rng);
                monster.increaseHp(heal);
            }
            });

        while (monster.isAlive() && !smiteUsed) {
            system("cls");

            monster.printBar();
            SetConsoleTextAttribute(hConsole, 12);
            cout << "예상 강타 데미지: " << smiteDamage << "\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << "[스페이스바 = 강타, I = 정보 확인]\n";

            for (int i = 0; i < 10; ++i) {
                this_thread::sleep_for(milliseconds(50));
                if (_kbhit()) break;
            }

            if (_kbhit()) {
                char key = getch();
                if (key == ' ') {
                    PlaySound(TEXT("강타.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    auto smiteTime = steady_clock::now();
                    bool success = monster.getHp() <= smiteDamage;
                    totalAttempts++;

                    cout << "\n=============================\n";
                    cout << "  [ 강타 사용됨 ] 데미지: " << smiteDamage << "\n";
                    cout << "=============================\n";

                    if (success) {
                        monster.kill();
                        PlaySound(NULL, 0, 0);  // BGM 정지
                        cout << "처치 성공!\n";
                        successCount++;
                    }
                    else {
                        monster.decreaseHp(smiteDamage);
                        cout << "처치 실패. 남은 체력: " << monster.getHp() << "\n";
                    }

                    if (smiteWindowOpened) {
                        int elapsedMs = duration_cast<milliseconds>(smiteTime - smiteReadyTime).count();
                        reactionTimes.push_back(elapsedMs);
                        string grade;
                        if (elapsedMs <= 250) grade = "개빠름";
                        else if (elapsedMs <= 400) grade = "빠름";
                        else if (elapsedMs <= 600) grade = "보통";
                        else if (elapsedMs <= 900) grade = "느림";
                        else grade = "많이 느림";

                        cout << "반응 속도: " << elapsedMs << "ms (" << grade << ")\n";
                    }
                    else {
                        cout << "※ 체력 900 이하가 되기 전에 강타가 시전되었습니다.\n";
                        reactionTimes.push_back(1500);
                    }

                    smiteUsed = true;
                }
                else if (key == 'i' || key == 'I') {
                    monster.info();
                    system("pause");
                }
            }
        }

        damageThread.join();
        healThread.join();
        cout << monster.getName() << " 라운드 종료.\n";
    }
}
