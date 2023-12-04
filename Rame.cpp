#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Rame.h"
//#include "Station.h"


using namespace std;

// Constructor :
Rame::Rame(string &Station, int &Ligne, int &Nb_pass_Max, vector<Rame*> &RameList) {
    this->x = 0;
    this->y = 0;
    this->Speed_Act = 0;
    this->Speed_max = 100;
    this->Id = RameList.size();
    this->Ligne = Ligne;
    this->Nb_pass_Max = Nb_pass_Max;
    this->Nb_pass = 0;
    this->Next_Station;//Table_of_Line[1];

    if (RameList.empty()){
        this->Next_Rame = NULL;
    }
    else{
        this->Next_Rame = RameList.back();
    }

}

float Rame::get_x(){
    return this->x;
}

float Rame::get_y(){
    return this->y;
}


int Rame::leaving_pass(const int &Nb){
    this->Nb_pass -= Nb;

    return Nb;
}
int Rame::incomming_pass(const int &Nb){
    this->Nb_pass += Nb;

    return Nb;
}
void Rame::arrive_Station(const string &Station, map<string, bool>&station_occuped ){
    if (station_occuped.at(Station) == false ){
        station_occuped[Station] = true;
    } else if (station_occuped.at(Station) == true) {
        cout << "ERROR : Station occuped" << endl;
    } else {
        cout << "ERROR in fucntion arrive_Station" << endl;
    }


}
void Rame::leave_station(const string &station, map<string,bool>&station_occuped, vector<Station*> &table_station ){
    if (station_occuped.at(station) == true ){
        station_occuped[station] = false;
        
        
    } else if (station_occuped.at(station) == false) {
        cout << "ERROR : Station is already not occuped" << endl;
    } else {
        cout << "ERROR in fucntion arrive_Station" << endl;
    }
    

}

void Rame::go_to_next_station(){
    
}


float Rame::dist_next_rame(){
    return sqrt(pow(this->x - Next_Rame->get_x(), 2) + pow(this->y - Next_Rame->get_y(), 2));
}
float Rame::dist_next_station(){
    return 0;
}
