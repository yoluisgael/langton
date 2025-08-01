//
// Created by yolui on 4/30/2024.
//

#include "Queen.h"

sf::Texture queen_texture;

int prob_worker;
int prob_queen;
int prob_breeder;

const void Queen::interact() {
    std::pair<int, int> front = this->get_front();
    for(auto &ant: ants){
        if(ant == this) continue;
        int prob;
        if(ant->get_position() == front or ant->get_position() == this->get_position()){
            // FIGHT
            if(ant->type() == "Queen"){
                if(ant->get_age() - this->get_age() <= -60)
                    prob = 20;
                else if(ant->get_age() - this->get_age() >= 60)
                    prob = 80;
                else
                    prob = 50;
                if(rand() % 100 < prob)
                    ant->die();
                else
                    this->die();
            }
            // REPRODUCE
            else if(ant->type() == "Breeder"){
                if(ant->get_position() == this->get_position()){
                    eggs++;
                }
                else{
                    int dir = ant->get_dir();
                    if(
                    (direction == 0 and dir == 2) ||
                    (direction == 1 and dir == 3) ||
                    (direction == 2 and dir == 0) ||
                    (direction == 3 and dir == 1))
                        eggs++;
                }
            }
        }
    }
}

const std::string Queen::type() {
    return "Queen";
}

const void Queen::spawn() {
    if(eggs > 0){
        int random = rand() % 100;
        int direction = rand() % 4;
        Ant* new_ant = nullptr;

        if(random < prob_queen) {
            new_ant = new Queen(direction, prevX, prevY);
        } else if(random < prob_queen + prob_worker) {
            new_ant = new Ant(direction, prevX, prevY);
        } else if(random < prob_queen + prob_worker + prob_breeder) {
            new_ant = new Breeder(direction, prevX, prevY);
        } else {
            new_ant = new Soldier(direction, prevX, prevY);
        }

        if (new_ant) {
            std::lock_guard<std::mutex> lock(ants_mtx); // Ensure thread safety
            ants.push_back(new_ant);
        }
        eggs--;
    }
}

void Queen::advance() {
    interact();
    Ant::advance();
    spawn();
}

void Queen::reproduce() {
    eggs++;
}