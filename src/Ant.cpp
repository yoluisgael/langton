#include "Ant.h"

sf::Texture ant_texture;
std::mutex nest_mtx;

sf::Sprite Ant::up() {
    return sprite;
}

sf::Sprite Ant::right() {
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width - GRID_SIZE, bounds.height);
    temp.rotate(90.0f);
    return temp;
}

sf::Sprite Ant::down() {
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width, bounds.height);
    temp.rotate(180.0f);
    return temp;
}

sf::Sprite Ant::left() {
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width, bounds.height - GRID_SIZE);
    temp.rotate(270.0f);
    return temp;
}

const std::string Ant::type() {
    return "Worker";
}

const int Ant::get_dir() {
    return direction;
}

const std::pair<int, int> Ant::get_position() {
    return {x, y};
}

const std::pair<int, int> Ant::get_prev_pos() {
    return {prevX, prevY};
}

const sf::Sprite Ant::get_sprite() {
    sprite.setPosition(x * GRID_SIZE, y * GRID_SIZE);
    switch (direction) {
        case UP:    return up();
        case RIGHT: return right();
        case DOWN:  return down();
        default:    return left();
    }
}

void Ant::set_dir(int dir) {
    direction = dir;
}

void Ant::set_texture(sf::Texture texture) {
    sprite.setTexture(texture);
}

const void Ant::turn_right() {
    direction = (direction + 1) % 4;
}

const void Ant::turn_left() {
    direction = (direction + 3) % 4;
}

void Ant::advance() {
    prevX = x;
    prevY = y;

    {
        std::lock_guard<std::mutex> lock(nest_mtx);
        if (nest[x][y])
            this->turn_left();
        else
            this->turn_right();
        nest[x][y] = !nest[x][y];
    }

    switch (direction) {
        case UP:    y = (y > 0) ? y - 1 : NUM_ROWS - 1; break;
        case RIGHT: x = (x < NUM_COLS - 1) ? x + 1 : 0; break;
        case DOWN:  y = (y < NUM_ROWS - 1) ? y + 1 : 0; break;
        default:    x = (x > 0) ? x - 1 : NUM_COLS - 1; break;
    }
    age++;
}

const std::pair<int, int> Ant::get_front() {
    int front_x = x, front_y = y;
    switch (direction) {
        case UP:    front_y = (y > 0) ? y - 1 : NUM_ROWS - 1; break;
        case RIGHT: front_x = (x < NUM_COLS - 1) ? x + 1 : 0; break;
        case DOWN:  front_y = (y < NUM_ROWS - 1) ? y + 1 : 0; break;
        default:    front_x = (x > 0) ? x - 1 : NUM_COLS - 1; break;
    }
    return {front_x, front_y};
}

const int Ant::get_age() {
    return age;
}

const void Ant::die() {
    age = DYING_AGE + 1;
}

void Ant::reproduce() {}
