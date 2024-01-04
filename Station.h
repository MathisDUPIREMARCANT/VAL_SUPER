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
        double x;
        double y;
        double distance;
        double argument;
        int waiting_pass; // Personne en attente
        int max_pass;
        bool occupied; // Elle est occupé ?

    public:
        Station(const string &name, const double &x, const double &y, const int &max_pass);

        int add_waiting(const int &nb);
        void connection(Station &Other);
        void arrive();
        void leaves();
        void calculate_distance(vector<Station>& list);
        double distance_to(Station Other);
        double get_next_dist();
        double get_next_arg();
        string get_name();
        double get_x();
        double get_y();

};



