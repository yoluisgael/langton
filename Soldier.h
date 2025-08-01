//
// Created by yolui on 6/15/2024.
//

#include "Ant.h"
#ifndef CA_SOLDIER_H
#define CA_SOLDIER_H

extern std::vector<std::vector<bool>> nest;
extern int NUM_COLS;
extern int NUM_ROWS;
extern std::vector<Ant*> ants;
extern sf::Texture soldier_texture;

class Soldier: public Ant {
public:
    const std::string type() override;      // Da el tipo de hormiga

    Soldier(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age) {
        sprite.setTexture(soldier_texture);
    }
    ~Soldier(){};
};


#endif //CA_SOLDIER_H
