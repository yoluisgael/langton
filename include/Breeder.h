#pragma once
#include "Ant.h"

class Breeder : public Ant {
public:
    const std::string type() override;
    const void interact();
    void advance() override;

    Breeder(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age) {
        sprite.setTexture(breeder_texture);
    }
    ~Breeder() {}
};
