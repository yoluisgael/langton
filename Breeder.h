//
// Created by yolui on 6/15/2024.
//
#include "Ant.h"
#ifndef CA_BREEDER_H
#define CA_BREEDER_H

extern std::vector<std::vector<bool>> nest;
extern int NUM_COLS;
extern int NUM_ROWS;
extern std::vector<Ant*> ants;
extern sf::Texture breeder_texture;

class Breeder: public Ant {
public:
    const std::string type() override;              // Da el tipo de hormiga
    const void interact();                          // Interactua con reinas
    void advance() override;                        // Modifica el avance para interactuar primero

    Breeder(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age) {
        sprite.setTexture(breeder_texture);
    }
    ~Breeder(){};
};


#endif //CA_BREEDER_H
