#pragma once
#include "Ant.h"

class Soldier : public Ant {
public:
    const std::string type() override;

    Soldier(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age) {
        sprite.setTexture(soldier_texture);
    }
    ~Soldier() {}
};
