#pragma once
#include <string>

class ReactionTester {
public:
    void run();  // 반응속도 테스트
    static std::string getGrade(int ms);  //등급
};
