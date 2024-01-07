#pragma once
#define MaxPassWagon 25
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Station.h"

using namespace std;

class Rame
{

private:
    double x;         // en m
    double y;         // en m
    double Speed;     // en m/s
    double Speed_max; // en m/s
    int Id;           // Pas besoin relier par reference a l'autre rame
    int Ligne;
    int Nb_pass_Max;
    int Nb_pass;
    vector<Rame>::iterator Next_Rame;
    vector<Station>::iterator Next_Station;

public:
    Rame(string station, int Ligne, int Nb_pass_Max, vector<Rame>::iterator &RameList, vector<Station> &station_list);

    void leaving_pass(const int &Nb);
    void incomming_pass(const int &Nb);
    void arrive_Station(vector<Station>::iterator &station, vector<Station> &station_list);
    void leave_station(vector<Station>::iterator &station, vector<Station> &station_list);

    int go_to_next_station(double acceleration, int t_ref, vector<Station> &station_list, Bouton &urgence);

    double dist_next_rame();
    double dist_next_station();
    double get_x();
    double get_y();
    double get_arg(vector<Station> &station_list, int a);
};