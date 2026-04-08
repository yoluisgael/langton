#include "Queen.h"

sf::Texture queen_texture;

int prob_worker;
int prob_queen;
int prob_breeder;

const std::string Queen::type() {
    return "Queen";
}

const void Queen::interact() {
    std::pair<int, int> front = this->get_front();
    for (auto& ant : ants) {
        if (ant == this) continue;
        if (ant->get_position() == front || ant->get_position() == this->get_position()) {
            if (ant->type() == "Queen") {
                int prob;
                int age_diff = ant->get_age() - this->get_age();
                if (age_diff <= -60)
                    prob = 20;
                else if (age_diff >= 60)
                    prob = 80;
                else
                    prob = 50;

                if (rand() % 100 < prob)
                    ant->die();
                else
                    this->die();
            } else if (ant->type() == "Breeder") {
                if (ant->get_position() == this->get_position()) {
                    eggs++;
                } else {
                    int dir = ant->get_dir();
                    if ((direction == UP    && dir == DOWN)  ||
                        (direction == RIGHT && dir == LEFT)  ||
                        (direction == DOWN  && dir == UP)    ||
                        (direction == LEFT  && dir == RIGHT))
                        eggs++;
                }
            }
        }
    }
}

const void Queen::spawn() {
    if (eggs > 0) {
        int random = rand() % 100;
        int dir = rand() % 4;
        Ant* new_ant = nullptr;

        if (random < prob_queen)
            new_ant = new Queen(dir, prevX, prevY);
        else if (random < prob_queen + prob_worker)
            new_ant = new Ant(dir, prevX, prevY);
        else if (random < prob_queen + prob_worker + prob_breeder)
            new_ant = new Breeder(dir, prevX, prevY);
        else
            new_ant = new Soldier(dir, prevX, prevY);

        if (new_ant) {
            std::lock_guard<std::mutex> lock(ants_mtx);
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
