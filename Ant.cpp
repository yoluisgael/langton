//
// Created by yolui on 4/30/2024.
//

#include "Ant.h"
enum Directions {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};

sf::Texture ant_texture;
std::mutex nest_mtx;

sf::Sprite Ant::up(){
    return sprite;
}
sf::Sprite Ant::right(){
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width - GRID_SIZE, bounds.height);
    temp.rotate(90.0f);
    return temp;
}
sf::Sprite Ant::down(){
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width, bounds.height);
    temp.rotate(180.0f);
    return temp;
}
sf::Sprite Ant::left(){
    sf::Sprite temp = sprite;
    sf::FloatRect bounds = temp.getGlobalBounds();
    temp.setOrigin(bounds.width, bounds.height - GRID_SIZE);
    temp.rotate(270.0f);
    return temp;
}

const std::string Ant::type(){
    return "Worker";
}
const int Ant::get_dir(){
    return direction;
}
const std::pair<int, int> Ant::get_position(){
    return {x, y};
}
const std::pair<int, int> Ant::get_prev_pos(){
    return {prevX, prevY};
}
const sf::Sprite Ant::get_sprite(){
    sprite.setPosition(x*GRID_SIZE, y*GRID_SIZE);
    switch(direction){
        case UP:
            return up();
        case RIGHT:
            return right();
        case DOWN:
            return down();
    }
    return left();
}

void Ant::set_dir(int dir){
    direction = dir;
}

void Ant::set_texture(sf::Texture texture){
    sprite.setTexture(texture);
}

const void Ant::turn_right(){
    direction++;
    if(direction > 3)
        direction = 0;
}
const void Ant::turn_left(){
    direction--;
    if(direction < 0)
        direction = 3;
}
void Ant::advance(){
    prevX = x;
    prevY = y;

    nest_mtx.lock();
    if(nest[x][y])
        this->turn_left();
    else
        this->turn_right();
    nest[x][y] = !nest[x][y];
    nest_mtx.unlock();
    switch(direction){
        case UP:
            if(y > 0)
                y--;
            else
                y = NUM_ROWS - 1;
            break;
        case RIGHT:
            if(x < NUM_COLS - 1)
                x++;
            else
                x = 0;
            break;
        case DOWN:
            if(y < NUM_ROWS - 1)
                y++;
            else
                y = 0;
            break;
        default:
            if(x > 0)
                x--;
            else
                x = NUM_COLS - 1;
    }
    age++;
}

const std::pair<int, int> Ant::get_front(){
    int front_x = x, front_y = y;
    switch(direction){
        case 0:
            if(y > 0)
                front_y = y - 1;
            else
                front_y = NUM_ROWS - 1;
            break;
        case 1:
            if(x < NUM_COLS - 1)
                front_x = x + 1;
            else
                front_x = 0;
            break;
        case 2:
            if(y < NUM_ROWS - 1)
                front_y = y + 1;
            else
                front_y = 0;
            break;
        default:
            if(x > 0)
                front_x = x - 1;
            else
                front_x = NUM_COLS - 1;
    }
    return {front_x, front_y};
}

const int Ant::get_age() {
    return age;
}

const void Ant::die(){
    this->age = DYING_AGE + 1;
}

void Ant::reproduce() {

}