//
// Created by yolui on 6/15/2024.
//

#include "Breeder.h"

sf::Texture breeder_texture;

const void Breeder::interact(){
    std::pair<int, int> front = this->get_front();
    for(auto &ant: ants){
        if(ant == this) continue;
        if(ant->get_position() == front or ant->get_position() == this->get_position()){
            // REPRODUCE
            if(ant->type() == "Queen"){
                if(ant->get_position() == this->get_position()){
                    ant->reproduce();
                }
                else{
                    int dir = ant->get_dir();
                    if(
                        (direction == 0 and dir == 2) ||
                        (direction == 1 and dir == 3) ||
                        (direction == 2 and dir == 0) ||
                        (direction == 3 and dir == 1))
                        ant->reproduce();
                }
            }
        }
    }
}

const std::string Breeder::type(){
    return "Breeder";
}

void Breeder::advance() {
    interact();
    Ant::advance();
}
