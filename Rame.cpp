#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Rame.h"

using namespace std;

// Constructor :
Rame::Rame(string station, int Ligne, int Nb_pass_Max, vector<Rame>::iterator &RameList, vector<Station> &station_list)
{

    this->Next_Station = station_list.begin();

    for (int i = 0; i < station_list.size(); i++)
    {
        if (station == station_list[i].get_name())
        {
            this->x = station_list[i].get_x();
            this->y = station_list[i].get_y();
            this->Next_Station += i;
        }
    }

    this->Speed = 0;
    this->Speed_max = 19.5;
    this->Ligne = Ligne;
    this->Nb_pass_Max = Nb_pass_Max;
    this->Nb_pass = 0;
}

double Rame::get_x()
{
    std::lock_guard<std::mutex> lock(mutex);
    return this->x;
}

double Rame::get_y()
{
    std::lock_guard<std::mutex> lock(mutex);
    return this->y;
}

void Rame::leaving_pass(const int &Nb)
{
    this->Next_Station->change_leaving(1);
    for (int i = 0; i < Nb; i++)
    {
        this->Nb_pass--;
        cout << "this-Nb_pass : " << this->Nb_pass << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    this->Next_Station->change_leaving(0);
    this_thread::sleep_for(chrono::milliseconds(500));
}
void Rame::incomming_pass(const int &Nb)
{
    this->Next_Station->change_leaving(2);
    for (int i = Nb; i > 0; i--)
    {
        this->Nb_pass++;
        this->Next_Station->decrease_pass();
        cout << "this-Nb_pass : " << this->Nb_pass << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    this->Next_Station->change_leaving(0);
    this_thread::sleep_for(chrono::milliseconds(500));
}
void Rame::arrive_Station(vector<Station>::iterator &station, vector<Station> &station_list)
{
    if (this->Next_Station->get_occupied() == false)
    {
        this->Next_Station->change_occupied(true);
    }
    else
    {
        cout << "err" << endl;
    }
}
void Rame::leave_station(vector<Station>::iterator &station, vector<Station> &station_list)
{
    if (this->Next_Station->get_occupied() == true)
    {
        this->Next_Station->change_occupied(false);
    }
    else
    {
        cout << "err" << endl;
    }
}

int Rame::go_to_next_station(double acceleration, int t_ref, vector<Station> &station_list)
{
    if (!acceleration)
    {
        return -1;
    }

    //     cout << "Speed : " << this->Speed << endl;
    // cout << "Next : " << this->Next_Station->get_name() << endl;

    double t1 = this->Speed_max / (double)acceleration;
    double d1 = acceleration * 0.5 * pow(t1, 2);

    double distance = Next_Station->get_next_dist();
    double argument = Next_Station->get_next_arg();
    auto degree = argument * 180 / 3.14;

    // if (this->Next_Station == station_list.end())
    // {
    //     this->Next_Station = station_list.begin();
    // }
    // else
    // {
    this->Next_Station++;
    // }
    double where = this->dist_next_station();

    while (this->Next_Station->get_occupied() == true)
    {
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    // cout << "Name : " << this->Next_Station->get_name() << endl;
    // cout << "Argument : " << argument * 180 / 3.14 << endl;
    // cout << "Argument : " << argument << endl;

    // return EXIT_SUCCESS;

    if (distance > (d1 * 2))
    {

        double t3 = this->Speed_max / (double)acceleration;
        double d3 = acceleration * 0.5 * pow(t3, 2);

        double d2 = distance - d1 - d3;

        // cout << "distance : " << distance << endl;
        // cout << "where : " << where << endl;

        while (where > 0)
        {
            double where = this->dist_next_station();
            if (distance - where < d1)
            {
                // accelerate
                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;
                this->Speed = this->Speed + (acceleration * ((double)t_ref / 1000));
            }

            else if (distance - where < d2 + d1)
            {
                // croisière
                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;
                this->Speed = this->Speed_max;
            }

            else
            {
                // descelerate
                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;
                this->Speed = this->Speed - (acceleration * ((double)t_ref / 1000));
            }

            this->y += (this->Speed * ((double)t_ref / 1000)) * sin(argument);
            this->x += (this->Speed * ((double)t_ref / 1000)) * cos(argument);

            if (this->Speed < 0 || distance - where >= distance)
            {
                this->Speed = 0;
                this->x = this->Next_Station->get_x();
                this->y = this->Next_Station->get_y();

                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;

                // cout << this->Next_Station->get_name() << endl;

                this->arrive_Station(this->Next_Station, station_list);

                random_device rd;
                mt19937 generator(rd());
                uniform_int_distribution<int> distribution_leave(0, this->Nb_pass);

                int nb = distribution_leave(generator);
                this->leaving_pass(nb);

                uniform_int_distribution<int> distribution_arrive(this->Nb_pass, this->Nb_pass_Max);
                nb = distribution_arrive(generator);
                this->incomming_pass(min(nb, this->Next_Station->get_max()));

                this->leave_station(this->Next_Station, station_list);

                this->Next_Station->increase_pass();

                return EXIT_SUCCESS;
            }
            this_thread::sleep_for(chrono::milliseconds(t_ref));
        }
    }
    else
    {
        double d0 = distance / 2.0;
        // cout << "d0 : " << d0 << endl;

        while (where > 0)
        {
            double where = this->dist_next_station();
            if (distance - where < d0)
            {
                // accelerate
                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;
                this->Speed = this->Speed + (acceleration * ((double)t_ref / 1000));
            }
            else
            {
                // descelerate
                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;
                this->Speed = this->Speed - (acceleration * ((double)t_ref / 1000));
            }
            this->y += (this->Speed * ((double)t_ref / 1000)) * sin(argument);
            this->x += (this->Speed * ((double)t_ref / 1000)) * cos(argument);

            if (this->Speed < 0 || distance - where >= distance)
            {
                this->Speed = 0;
                this->x = this->Next_Station->get_x();
                this->y = this->Next_Station->get_y();

                // cout << "Speed : " << this->Speed << endl;
                // cout << "x: " << this->x << endl;
                // cout << "y: " << this->y << endl;

                cout << this->Next_Station->get_name() << endl;

                this->arrive_Station(this->Next_Station, station_list);

                random_device rd;
                mt19937 generator(rd());
                uniform_int_distribution<int> distribution_leave(0, this->Nb_pass);

                int nb = distribution_leave(generator);
                // cout << "AAAAAAAAAAAAAA : " << nb << endl;
                this->leaving_pass(nb);

                uniform_int_distribution<int> distribution_arrive(this->Nb_pass, this->Nb_pass_Max);
                nb = distribution_arrive(generator);
                this->incomming_pass(nb);

                this->leave_station(this->Next_Station, station_list);

                return EXIT_SUCCESS;
            }
            this_thread::sleep_for(chrono::milliseconds(t_ref));
        }
    }

    return EXIT_SUCCESS;
}

double Rame::dist_next_rame()
{
    return sqrt(pow(Next_Rame->get_x() - this->x, 2) + pow(Next_Rame->get_y() - this->y, 2));
}
double Rame::dist_next_station()
{
    return sqrt(pow(this->Next_Station->get_x() - this->x, 2) + pow(this->Next_Station->get_y() - this->y, 2));
}

void Rame::draw(sf::RenderWindow &window) const
{
    // Créer un carré
    sf::RectangleShape square(sf::Vector2f(50.0f, 50.0f));
    square.setFillColor(sf::Color::Red);

    square.setPosition(this->x, this->y);

    window.draw(square);
}

double Rame::get_arg(vector<Station> &station_list)
{
    for (int i = 0; i < station_list.size(); i++)
    {
        if (station_list[i].get_name() == this->Next_Station->get_name())
        {
            auto where = this->dist_next_station();
            if (where < 20)
            {
                return ((where * station_list[i - 1].get_next_arg() * 180 / 3.14) + (20 - where) * this->Next_Station->get_next_arg() * 180 / 3.14) / 20;
            }
            else if (this->Next_Station->get_occupied())
            {
                return ((station_list[i - 1].get_next_arg() * 180 / 3.14) + this->Next_Station->get_next_arg() * 180 / 3.14) / 2;
            }
            //             else if(this->dist_next_station() - where < 20){
            // return (((20 - where) * station_list[i - 1].get_next_arg() * 180 / 3.14) + where * this->Next_Station->get_next_arg() * 180 / 3.14) / 20;
            //             }
            else
            {
                return station_list[i - 1].get_next_arg() * 180 / 3.14;
            }
        }
    }
    return 0;
}
