#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Station.h"

using namespace std;

Station::Station(string const &name, const float &x, const float &y, const int &max_pass){
    this->name = name;
    this->x = x;
    this->y = y;
    this->waiting_pass = 0;
    this->max_pass = 100;
    this->occupied = false;
    this->distance = 0;
}

int Station::add_waiting(const int &nb) {
    this->waiting_pass += nb;
    return nb;
}

void Station::arrive() {
    this->occupied = true;
}

void Station::leaves() {
    this->occupied = false;
}

float Station::distance_to(Station Other) {
    cout << "this->x : " << this->x << endl;
    cout << "this->y : " << this->y << endl;
    cout << "Other->x : " << Other.x << endl;
    cout << "Other->y : " << Other.y << endl;
    
    return sqrt(pow(Other.x - this->x, 2) + pow(Other.y - this->y, 2));
}

float Station::get_next_dist(){
    return this->distance;
}

void Station::connection(Station &Other) {
    
}

string Station::get_name(){
    return this->name;
}

float Station::get_x(){
    return this->x;
}

float Station::get_y(){
    return this->y;
}

void Station::calculate_distance(vector<Station>& list) {
    for (size_t i = 0; i < list.size(); i++) {
        if (this->name == list[i].get_name()) {
            this->distance = this->distance_to(list[(i+1)% list.size()]);
            cout << this->name << "  : " << this->distance << endl;
        }
    }
}
