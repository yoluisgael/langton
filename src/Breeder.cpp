#include "Breeder.h"
#include "Queen.h"

sf::Texture breeder_texture;

const std::string Breeder::type() {
    return "Breeder";
}

const void Breeder::interact() {
    std::pair<int, int> front = this->get_front();
    for (auto& ant : ants) {
        if (ant == this) continue;
        if (ant->get_position() == front || ant->get_position() == this->get_position()) {
            if (ant->type() == "Queen") {
                if (ant->get_position() == this->get_position()) {
                    ant->reproduce();
                } else {
                    int dir = ant->get_dir();
                    if ((direction == UP    && dir == DOWN)  ||
                        (direction == RIGHT && dir == LEFT)  ||
                        (direction == DOWN  && dir == UP)    ||
                        (direction == LEFT  && dir == RIGHT))
                        ant->reproduce();
                }
            }
        }
    }
}

void Breeder::advance() {
    interact();
    Ant::advance();
}
