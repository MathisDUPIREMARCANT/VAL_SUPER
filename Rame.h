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

class Rame {

    private:
        float x;
        float y;
        float Speed_Act;
        float Speed_max;
        int Id; //Pas besoin relier par reference a l'autre rame
        int Ligne;
        int Nb_pass_Max;
        int Nb_pass;

        vector<Station>::iterator Next_Station;


    public:
        Rame* Next_Rame;
        Rame(string &station, int &Ligne, int &Nb_pass_Max, vector<Rame*> &RameList, vector<Station>::iterator station_list);

        int leaving_pass(const int &Nb);
        int incomming_pass(const int &Nb);
        void arrive_Station(const string &station, map<string,bool>&station_occuped, vector<Station>station_list );
        void leave_station(const string &station, map<string,bool>&station_occuped, vector<Station> &table_station  );
        void go_to_next_station();
        void accelerate(float second);
        void decelerate(float second);
        float dist_next_rame();
        float dist_next_station();
        float get_x();
        float get_y();

    //urgence si la distance avec la prochaine station est plus grande que la distance avec le prochain wagon alors on arrete à la station
    // sinon on arrete sur les rails
};