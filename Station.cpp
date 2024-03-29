#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include "Station.h"
#include "function.h"
#include "Bouton.h"

using namespace std;

Station::Station(string const &name, const double &x, const double &y, const int &max_pass)
{
    this->name = name;
    this->x = x;
    this->y = y;
    this->waiting_pass = 0;
    this->max_pass = max_pass;
    this->occupied = false;
    this->distance = 0;
    this->argument = 0;
    this->leaving = true;
}

int Station::add_waiting(const int &nb)
{
    this->waiting_pass += nb;
    return nb;
}

int Station::get_max()
{
    return this->max_pass;
}

void Station::arrive()
{
    this->occupied = true;
}

void Station::leaves()
{
    this->occupied = false;
}

double Station::distance_to(Station Other)
{
    return sqrt(pow(Other.x - this->x, 2) + pow(Other.y - this->y, 2));
}

double Station::get_next_dist()
{
    return this->distance;
}

double Station::get_next_arg()
{
    return this->argument;
}

void Station::connection(Station &Other)
{
}

string Station::get_name()
{
    return this->name;
}

double Station::get_x()
{
    return this->x;
}

double Station::get_y()
{
    return this->y;
}

bool Station::get_occupied()
{
    return this->occupied;
}

void Station::change_occupied(bool etat)
{
    this->occupied = etat;
}

void Station::calculate_distance(vector<Station> &list)
{
    for (size_t i = 0; i < list.size(); i++)
    {
        if (this->name == list[i].get_name())
        {
            auto before = list[(i - 1) % list.size()];
            auto next = list[(i + 1) % list.size()];
            this->distance = this->distance_to(next);
            auto a = next.get_x() - this->x;
            auto b = next.get_y() - this->y;
            this->argument = atan2(b, a);

            a = this->x - before.get_x();
            b = this->y - before.get_y();
            this->b_argument = atan2(b, a);
        }
    }
}

void Station::decrease_pass()
{
    this->waiting_pass--;
}

void Station::increase_pass()
{
    if (this->max_pass != 0)
    {
        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution_leave(this->waiting_pass, this->max_pass);

        int nb = distribution_leave(generator);

        this->waiting_pass += nb;
    }
}

void Station::change_leaving(int etat)
{
    this->leaving = etat;
}

int Station::get_leaving()
{
    return this->leaving;
}
