#include "events.h"
#include "globals.h"
#include "Ant.h"
#include "Queen.h"
#include "Breeder.h"
#include "Soldier.h"

void left_click(int col, int row) {
    for (auto& ant : ants) {
        if (ant->get_position().first == col && ant->get_position().second == row) {
            ant->turn_right();
            return;
        }
    }
    ants.push_back(new Ant(0, col, row));
}

void right_click(int col, int row) {
    for (size_t i = 0; i < ants.size(); i++) {
        if (ants[i]->get_position().first == col && ants[i]->get_position().second == row) {
            std::string type = ants[i]->type();
            int dir = ants[i]->get_dir();
            int x   = ants[i]->get_position().first;
            int y   = ants[i]->get_position().second;
            int age = ants[i]->get_age();

            Ant* replacement = nullptr;
            if (type == "Worker")
                replacement = new Queen(dir, x, y, age);
            else if (type == "Queen")
                replacement = new Breeder(dir, x, y, age);
            else if (type == "Breeder")
                replacement = new Soldier(dir, x, y, age);
            else
                replacement = new Ant(dir, x, y, age);

            delete ants[i];
            ants[i] = replacement;
            return;
        }
    }
}

void middle_click(int col, int row) {
    for (size_t i = 0; i < ants.size(); i++) {
        if (ants[i]->get_position().first == col && ants[i]->get_position().second == row) {
            delete ants[i];
            ants.erase(ants.begin() + i);
            return;
        }
    }
}

void enter() {
    for (auto ant : ants)
        delete ant;
    ants.clear();

    for (auto& row : nest)
        std::fill(row.begin(), row.end(), false);

    int total = NUM_COLS * NUM_ROWS * PROB / 100;
    for (int i = 0; i < total; i++) {
        int random    = rand() % 100;
        int direction = rand() % 4;
        int x         = rand() % NUM_COLS;
        int y         = rand() % NUM_ROWS;

        if (random < prob_queen)
            ants.push_back(new Queen(direction, x, y));
        else if (random < prob_queen + prob_worker)
            ants.push_back(new Ant(direction, x, y));
        else if (random < prob_queen + prob_worker + prob_breeder)
            ants.push_back(new Breeder(direction, x, y));
        else
            ants.push_back(new Soldier(direction, x, y));
    }
}
