#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>

class Ant;

enum Direction { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

extern const int SEED;
extern int GRID_SIZE;
extern int NUM_COLS;
extern int NUM_ROWS;
extern int DYING_AGE;
extern int PROB;

extern std::vector<std::vector<bool>> nest;
extern std::vector<Ant*> ants;
extern std::mutex nest_mtx;
extern std::mutex ants_mtx;

extern sf::Texture ant_texture;
extern sf::Texture queen_texture;
extern sf::Texture breeder_texture;
extern sf::Texture soldier_texture;

extern int prob_worker;
extern int prob_queen;
extern int prob_breeder;
