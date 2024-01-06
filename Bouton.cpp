#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include "Bouton.h"

Bouton::Bouton(double x, double y)
{
    this->x = x;
    this->y = y;
    this->etat = false;
}

void Bouton::set_x(double x)
{
    std::lock_guard<std::mutex> lock(mutex);
    this->x = x;
}

void Bouton::set_y(double y)
{
    std::lock_guard<std::mutex> lock(mutex);
    this->y = y;
}

void Bouton::change_etat()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (this->etat == true)
    {
        this->etat = false;
    }
    else
    {
        this->etat = true;
    }
}

double Bouton::get_x()
{
    std::lock_guard<std::mutex> lock(mutex);
    return this->x;
}

double Bouton::get_y()
{
    std::lock_guard<std::mutex> lock(mutex);
    return this->y;
}

bool Bouton::get_etat()
{
    std::lock_guard<std::mutex> lock(mutex);
    return this->etat;
}
