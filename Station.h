#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>



using namespace std;


class Station {

    private:
        string name;
        float x;
        float y;
        float distance;
        int waiting_pass; // Personne en attente
        int max_pass;
        bool occupied; // Elle est occupé ?

    public:
        Station(const string &name, const float &x, const float &y, const int &max_pass);

        int add_waiting(const int &nb);
        void connection(Station &Other);
        void arrive();
        void leaves();
        void calculate_distance(vector<Station>& list);
        float distance_to(Station Other);
        float get_next_dist();
        string get_name();

};



