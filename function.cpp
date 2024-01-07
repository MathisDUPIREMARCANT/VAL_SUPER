#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cmath>
#include "Rame.h"
#include "function.h"

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884L
#endif

void move_rame(Rame &rame, double t_ref, double acceleration, int nb_station, vector<Station> &station_list, Bouton &urgence)
{
    // wrapper like

    for (int i = 0; i < nb_station; i++)
    {
        rame.go_to_next_station(acceleration, t_ref, station_list, ref(urgence));
    }
}

vector<double> mercatorProjection(double latitude, double longitude, double mapWidth, double mapHeight)
{
    double x = (longitude + 180.0) * (mapWidth / 360.0);
    double y = (mapHeight / 2.0) * (1.0 - log(tan(latitude * M_PI / 180.0) + 1.0 / cos(latitude * M_PI / 180.0)) / M_PI);

    return {x, y};
}
