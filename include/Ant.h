#pragma once
#include "globals.h"
#include "graphics.h"

class Ant {
public:
    sf::Sprite up();
    sf::Sprite right();
    sf::Sprite down();
    sf::Sprite left();

    virtual const std::string type();
    const int get_dir();
    const std::pair<int, int> get_position();
    const std::pair<int, int> get_prev_pos();
    const std::pair<int, int> get_front();
    const sf::Sprite get_sprite();
    const int get_age();

    void set_dir(int dir);
    void set_texture(sf::Texture texture);

    const void turn_right();
    const void turn_left();
    virtual void advance();
    virtual void reproduce();
    const void die();

    Ant(int direction = 0, int x = 0, int y = 0, int age = 0)
        : direction(direction), x(x), y(y), prevX(x), prevY(y), age(age) {
        sprite.setTexture(ant_texture);
    }
    virtual ~Ant() {}

protected:
    int direction, age;
    int x, y, prevX, prevY;
    sf::Sprite sprite;
};
