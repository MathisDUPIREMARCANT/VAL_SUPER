#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <map>
#include "Station.h"

using namespace std;

Station::Station(string const &name, const float &x, const float &y, const int &max_pass){
    this->name = name;
    this->x = x;
    this->y = y;
    this->waiting_pass = 0;
    this->max_pass = 100;
    this->occupied = false;
    this->others;
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

float Station::distance_to(Station* Other) {
    return sqrt(pow(Other->x - this->x, 2) + pow(Other->y - this->y, 2));
}

void Station::connection(Station &Other) {
    
}

string Station::get_name(){
    return this->name;
}

void Station::calculate_distance(vector<Station> list){
    for (int i = 0; i < list.size(); i++){
        if (this->name == list[i].get_name()){
            NULL;
        }
    }
}