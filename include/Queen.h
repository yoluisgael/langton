#pragma once
#include "Ant.h"
#include "Breeder.h"
#include "Soldier.h"

class Queen : public Ant {
public:
    const void interact();
    const void spawn();
    const std::string type() override;
    void advance() override;
    void reproduce() override;

    Queen(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age), eggs(0) {
        sprite.setTexture(queen_texture);
    }
    ~Queen() {}

private:
    int eggs;
};
