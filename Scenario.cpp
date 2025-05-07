#include "Scenario.h"

Scenario::Scenario() {
    frames.push_back({ 4000, 0 });
    frames.push_back({ 3600, 600 });
    frames.push_back({ 3200, 1200 });
    frames.push_back({ 2800, 1800 });
    frames.push_back({ 2300, 2400 });
    frames.push_back({ 1800, 3000 });
    frames.push_back({ 1300, 3600 });
    frames.push_back({ 900, 4200 });
    frames.push_back({ 600, 4700 });
    frames.push_back({ 200, 5300 });
    frames.push_back({ 0, 6000 });
}

const std::vector<ScenarioFrame>& Scenario::getFrames() const {
    return frames;
}
