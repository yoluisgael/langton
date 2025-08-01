//
// Created by yolui on 4/30/2024.
//
#include <SFML/Graphics.hpp>
#include <mutex>
#include "graphics.h"
#ifndef ANT_H
#define ANT_H
extern const int SEED;
extern int GRID_SIZE;
extern int NUM_COLS;
extern int NUM_ROWS;
extern int DYING_AGE;
extern std::vector<std::vector<bool>> nest;

extern sf::Texture ant_texture;

extern std::mutex nest_mtx;

class Ant{
public:
    // Da los sprites de la hormiga con rotaciones
    sf::Sprite up();
    sf::Sprite right();
    sf::Sprite down();
    sf::Sprite left();

    virtual const std::string type();           // Da el tipo de hotmiga
    const int get_dir();                        // Da la dirección de la hormiga
    const std::pair<int, int> get_position();   // Da la posición de la hormiga
    const std::pair<int, int> get_prev_pos();   // Da la posición previa de la hormiga
    const std::pair<int, int> get_front();      // Da la posición del frente
    const sf::Sprite get_sprite();              // Da el sprite con orientación de la hormiga
    const int get_age();                        // Da la edad de la hormiga

    void set_dir(int dir);                      // Pone la dirección de la hormiga
    void set_texture(sf::Texture texture);      // Pone la textura de la hormiga

    const void turn_right();                    // Gira la hormiga a la derecha
    const void turn_left();                     // Gira la hormiga a la izquierda
    virtual void advance();                     // Avanza a la hormiga, cambia el estado de la celda y aumenta su edad
    virtual void reproduce();                   // Función base para otras hormigas

    const void die();                           // Avanza la edad hasta la muerte

    Ant(int direction = 0, int x = 0, int y = 0, int age = 0)
    : direction(direction), x(x), y(y), prevX(x), prevY(y), age(age){
        sprite.setTexture(ant_texture);
    }
    virtual ~Ant(){}
protected:
    int direction, age;
    int x, y, prevX, prevY;
    sf::Sprite sprite;
};

#endif //ANT_H
