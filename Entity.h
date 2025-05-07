#pragma once
#include <string>

class Entity {
protected:
    std::string name;
public:
    Entity(const std::string& name) : name(name) {}
    virtual void info() const = 0;
    std::string getName() const { return name; }
    virtual ~Entity() {}
};
