#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Rame.h"

// vector<Rame> init_rame(vector<Station> stations, vector<int> lignes, vector<int> capacity, vector<Rame> &RameList);
void move_rame(Rame &rame, double t_ref, double acceleration, int nb_station, vector<Station> &station_list, Bouton &urgence);
vector<double> mercatorProjection(double latitude, double longitude, double mapWidth, double mapHeight);
