#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <thread>
#include <iostream>
#include <functional>
#include <fstream>
#include <mutex>
#include "gnuplot.h"
#include "Ant.h"
#include "Queen.h"
#include "graphics.h"
#include "events.h"
using namespace std;

const int SEED = static_cast<unsigned int>(time(nullptr));
int GRID_SIZE = 10;
int NUM_COLS = 200;
int NUM_ROWS = 200;
int DYING_AGE = 80;
int PROB = 50;
enum Directions {UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};
vector<vector<bool>> nest(NUM_COLS, vector<bool>(NUM_ROWS, 0));
vector<Ant*> ants;
mutex nest_mutex, ants_mtx;

//Reina 1%
//Soldado 55%
//Reproductora 9%
//Obreros 35%

// Avanza a las hormigas
void update_ants(vector<Ant*>::iterator start, vector<Ant*>::iterator end){
    for(auto it = start; it != end; it++){
        Ant* ant = *it;
        ant->advance();
    }
}

// Avanza a las hormigas y luego aplica muerte a las ancianas
void step(){
    int num_threads = std::thread::hardware_concurrency();
    vector<std::thread> threads;
    int ants_per_thread = ants.size() / num_threads;
    auto start = ants.begin();

    for(int i = 0; i < num_threads - 1; ++i){
        auto end = start + ants_per_thread;
        threads.push_back(std::thread(update_ants, start, end));
        start = end;
    }
    threads.push_back(std::thread(update_ants, start, ants.end()));

    for(auto &t : threads){
        t.join();
    }

    for(auto ant = ants.begin(); ant != ants.end();){
        if((*ant)->get_age() >= DYING_AGE){
            delete(*ant);
            ant = ants.erase(ant);
        }
        else{
            ++ant;
        }
    }
}

int main() {
    bool pause = true;
    bool one_step = true;
    int step_delay = 1;
    int speed = 50;
    int iterations = 0;
    std::srand(SEED);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "CA Lab", sf::Style::Fullscreen);
    sf::View view;
    sf::Font font;
    sf::Clock step_delay_timer, speed_delay_timer, prob_delay_timer;
    sf::Color brown(70,24,24);
    sf::Color peach(215, 145, 110);

    float col_size = window.getSize().x / NUM_COLS;
    float row_size = window.getSize().y / NUM_ROWS;
    if(col_size < 5) NUM_COLS = window.getSize().x/5;
    if(row_size < 5) NUM_ROWS = window.getSize().y/5;
    GRID_SIZE = max(int(min(window.getSize().x / NUM_COLS, window.getSize().y / NUM_ROWS)), 5);

    font.loadFromFile("C:\\fonts\\roboto.ttf");
    ant_texture = loadImage("../images/ant.png", GRID_SIZE, GRID_SIZE);
    queen_texture = loadImage("../images/queen.png", GRID_SIZE, GRID_SIZE);
    breeder_texture = loadImage("../images/breeder.png", GRID_SIZE, GRID_SIZE);
    soldier_texture = loadImage("../images/soldier.png", GRID_SIZE, GRID_SIZE);

    prob_queen = 1;
    prob_worker = 55;
    prob_breeder = 9;


    sf::RectangleShape dirt;
    dirt.setSize(sf::Vector2f(NUM_COLS*GRID_SIZE, NUM_ROWS*GRID_SIZE));
    dirt.setFillColor(brown);

    sf::Texture grass_txtr = loadImage("../images/grass.jpg", window.getSize().x, window.getSize().y);
    sf::Sprite grass(grass_txtr);

    sf::Text speed_txt;
    speed_txt.setFont(font);
    speed_txt.setFillColor(sf::Color::White);
    string speed_str;

    sf::Text prob_txt;
    prob_txt.setFont(font);
    prob_txt.setFillColor(sf::Color::White);
    prob_txt.setPosition(window.getSize().x - 200, 20);
    string prob_str;

    sf::Text it_txt;
    it_txt.setFont(font);
    it_txt.setFillColor(sf::Color::White);
    it_txt.setPosition(NUM_COLS * GRID_SIZE / 2 - 100, NUM_ROWS * GRID_SIZE / 2 - 10);
    string it_str;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    exit(0);
                }
                if (event.key.code == sf::Keyboard::Tab) {
                    one_step = true;
                }
                if(event.key.code == sf::Keyboard::Space){
                    pause = !pause;
                    speed_delay_timer.restart();
                    prob_delay_timer.restart();
                }
                if(event.key.code == sf::Keyboard::Enter){
                    enter();
                    iterations = 0;
                }
                if(event.key.code == sf::Keyboard::Right){
                    if(speed < 100){
                        speed += 5;
                        step_delay -= 10;
                        speed_delay_timer.restart();
                    }
                }
                if(event.key.code == sf::Keyboard::Left){
                    if(speed > 1){
                        speed -= 5;
                        step_delay += 10;
                        speed_delay_timer.restart();
                    }
                }
                if(event.key.code == sf::Keyboard::Up){
                    if(PROB < 100)
                        PROB += 5;
                }
                if(event.key.code == sf::Keyboard::Down){
                    if(PROB > 0)
                        PROB -= 5;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                int col = mousePos.x / GRID_SIZE;
                int row = mousePos.y / GRID_SIZE;
                if(col >= NUM_COLS or row >= NUM_ROWS) break;
                if(event.mouseButton.button == sf::Mouse::Left){
                    left_click(col, row);
                }
                if(event.mouseButton.button == sf::Mouse::Right){
                    right_click(col, row);
                }
                if(event.mouseButton.button == sf::Mouse::Middle){
                    middle_click(col, row);
                }
            }
        }



        window.clear(sf::Color::Green);
        window.draw(grass);
        window.draw(dirt);

        if(ants.empty()){
            pause = true;
            it_str = "Iterations: ";
            it_str += to_string(iterations);
            it_txt.setString(it_str);
            window.draw(it_txt);
        }

        if(pause or prob_delay_timer.getElapsedTime().asSeconds() < 3){
            prob_str = "Prob: ";
            prob_str += to_string(PROB);
            prob_txt.setString(prob_str);
            window.draw(prob_txt);
            speed_txt.setPosition(window.getSize().x - 200, 60);
        }
        else {
            speed_txt.setPosition(window.getSize().x - 200, 20);
        }
        if(pause or speed_delay_timer.getElapsedTime().asSeconds() < 3){
            speed_str = "Speed: ";
            speed_str += to_string(speed);
            speed_txt.setString(speed_str);
            speed_txt.setOutlineColor(sf::Color::Black);
            window.draw(speed_txt);
        }

        if ((!pause and step_delay_timer.getElapsedTime().asMilliseconds() >= step_delay) or one_step) {
            step();
            step_delay_timer.restart();
            if(one_step)
                one_step = false;
            if(!ants.empty())
                iterations++;
        }

        for(Ant* ant: ants){
            window.draw(ant->get_sprite());
        }

        window.display();
    }



    return 0;
}
