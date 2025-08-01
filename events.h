//
// Created by yolui on 6/16/2024.
//


#include "Ant.h"
#include "Queen.h"
#include "Breeder.h"
#include "Soldier.h"
#ifndef CA_EVENTS_H
#define CA_EVENTS_H

extern std::vector<std::vector<bool>> nest;
extern int NUM_COLS;
extern int NUM_ROWS;
extern int PROB;
extern std::vector<Ant*> ants;
extern sf::Texture queen_texture;

void left_click(int col, int row); // Rotar o crear hormiga
void right_click(int col, int row); // Cambiar tipo de hormiga
void middle_click(int col, int row); // Borrar hormiga
void enter(); // Generar hormigas con porcentaje actual

#endif //CA_EVENTS_H
