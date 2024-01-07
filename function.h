#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Rame.h"

void move_rame(Rame &rame, double t_ref, double acceleration, int nb_station, vector<Station> &station_list, Bouton &urgence);
vector<double> mercatorProjection(double latitude, double longitude, double mapWidth, double mapHeight);
