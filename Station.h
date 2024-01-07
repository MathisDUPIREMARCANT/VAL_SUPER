#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "Bouton.h"

using namespace std;

class Station
{

private:
    string name;
    double x;
    double y;
    double distance;
    double argument;
    double b_argument;
    int waiting_pass; // Personne en attente
    int max_pass;
    bool occupied; // Elle est occupé ?
    int leaving;   // etat1 2 personnes sortent par secondes / etat2 2 personnes entrent par secondes //etat0 rien

public:
    Station(const string &name, const double &x, const double &y, const int &max_pass);

    int add_waiting(const int &nb);
    int get_max();
    void connection(Station &Other);
    void arrive();
    void leaves();
    void decrease_pass();
    void increase_pass();
    void calculate_distance(vector<Station> &list);
    double distance_to(Station Other);
    double get_next_dist();
    double get_next_arg();
    string get_name();
    double get_x();
    double get_y();
    void change_leaving(int etat);
    int get_leaving();
    bool get_occupied();
    void change_occupied(bool etat);
};
