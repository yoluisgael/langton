//
// Created by yolui on 4/30/2024.
//
#include "Ant.h"
#include "Breeder.h"
#include "Soldier.h"
#ifndef CA_QUEEN_H
#define CA_QUEEN_H

extern std::vector<std::vector<bool>> nest;
extern int NUM_COLS;
extern int NUM_ROWS;
extern std::vector<Ant*> ants;
extern sf::Texture queen_texture;
extern std::mutex ants_mtx;

extern int prob_worker;
extern int prob_queen;
extern int prob_breeder;

class Queen: public Ant {
public:
    const void interact();                  // Interactua con reinas y reproductoras
    const void spawn();                     // Aparece hormigas nuevas
    const std::string type() override;      // Da el tipo de hormiga
    void advance() override;                // Interactúa, avanza y se reproduce
    void reproduce() override;              // Reproduce al encontrar reproductoras

    Queen(int direction = 0, int x = 0, int y = 0, int age = 0)
        : Ant(direction, x, y, age), eggs(0) {
        sprite.setTexture(queen_texture);
    }
    ~Queen(){};
private:
    int eggs;
};


#endif //CA_QUEEN_H
