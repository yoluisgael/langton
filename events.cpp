//
// Created by yolui on 6/16/2024.
//

#include "events.h"

void left_click(int col, int row){
    bool new_ant = true;
    for(auto &ant: ants){
        if(col == ant->get_position().first and row == ant->get_position().second){
            ant->turn_right();
            new_ant = false;
            break;
        }
    }
    if(new_ant){
        ants.push_back(new Ant(0, col, row));
    }
}

void right_click(int col, int row){
    for(int i=0; i<ants.size(); i++){
        if(col == ants[i]->get_position().first and row == ants[i]->get_position().second){
            std::string type = ants[i]->type();
            int dir, x, y, age;
            dir = ants[i]->get_dir();
            x = ants[i]->get_position().first;
            y = ants[i]->get_position().second;
            age = ants[i]->get_age();
            if(type == "Worker")
                ants.push_back(new Queen(dir, x, y, age));
            else if(type == "Queen")
                ants.push_back(new Breeder(dir, x, y, age));
            else if(type == "Breeder")
                ants.push_back(new Soldier(dir, x, y, age));
            else
                ants.push_back(new Ant(dir, x, y, age));
            delete(ants[i]);
            ants.erase(ants.begin()+i);
            return;
        }
    }
}

void middle_click(int col, int row){
    for(int i=0; i<ants.size(); i++){
        if(col == ants[i]->get_position().first and row == ants[i]->get_position().second){
            delete(ants[i]);
            ants.erase(ants.begin()+i);
            return;
        }
    }
}

void enter(){
    for(auto ant = ants.begin(); ant != ants.end();){
        delete *ant;
        ant = ants.erase(ant);
    }
    for (auto& row : nest) {
        std::fill(row.begin(), row.end(), false);
    }

    int total_cells = NUM_COLS * NUM_ROWS * PROB / 100;
    for(int i=0; i<total_cells; i++){
        int random = rand() % 100;
        int direction = rand() % 4;
        int x = rand() % NUM_COLS;
        int y = rand() % NUM_ROWS;
        if(random < prob_queen)
            ants.push_back(new Queen(direction, x, y));
        else if(random < prob_queen + prob_worker)
            ants.push_back(new Ant(direction, x, y));
        else if(random < prob_queen + prob_breeder + prob_worker)
            ants.push_back(new Breeder(direction, x, y));
        else
            ants.push_back(new Soldier(direction, x, y));
    }
}