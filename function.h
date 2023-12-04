#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Rame.h"

vector<Rame> init_rame(vector<string> stations, vector<int> lignes, vector<int> capacity, vector<Rame*> RameList);
