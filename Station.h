#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>

using namespace std;


class Station {

    private:
        string name;
        float x;
        float y;
        int waiting_pass; // Personne en attente
        int max_pass;
        bool occupied; // Elle est occupé ?
        map<string, float> others; // station reliée et la distance

    public:
        Station(const string &name, const float &x, const float &y, const int &max_pass);

        int add_waiting(const int &nb);
        void connection(Station &Other);
        void arrive();
        void leaves();
        float distance_to(Station &Other);
        string get_name();

};



