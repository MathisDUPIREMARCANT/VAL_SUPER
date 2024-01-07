#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

using namespace std;

class Bouton
{

private:
    double x;
    double y;

    bool etat; // True : Arret Urgence / False : RAS

public:
    Bouton(double x, double y);

    void set_x(double x);
    void set_y(double y);
    void change_etat();

    double get_x();
    double get_y();
    bool get_etat();
};
