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
Rame::Rame(string &station, int &Ligne, int &Nb_pass_Max, vector<Rame*> &RameList, vector<Station> &station_list) {
    this->x = 0;
    this->y = 0;
    this->Speed = 0;
    this->Speed_max = 100;
    this->Id = RameList.size();
    this->Ligne = Ligne;
    this->Nb_pass_Max = Nb_pass_Max;
    this->Nb_pass = 0;


    this->Next_Station = station_list.begin();
    ++this->Next_Station; 
    
    

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
void Rame::arrive_Station(const string &station, map<string, bool>&station_occuped, vector<Station>station_list ){
    if (station_occuped.at(station) == false ){
        station_occuped[station] = true;
        ++this->Next_Station;
        if (this->Next_Station == station_list.end()){
            this->Next_Station = station_list.begin();
        }
    } else if (station_occuped.at(station) == true) {
        cout << "ERROR : Station occuped" << endl;
    } else {
        cout << "ERROR in fucntion arrive_Station" << endl;
    }


}
void Rame::leave_station(const string &station, map<string,bool>&station_occuped, vector<Station> &table_station ){
    if (station_occuped.at(station) == true ){
        station_occuped[station] = false;
        
        
    } else if (station_occuped.at(station) == false) {
        cout << "ERROR : Station is already not occuped" << endl;
    } else {
        cout << "ERROR in fucntion arrive_Station" << endl;
    }
    

}

int Rame::go_to_next_station(float acceleration, float t_mili){
    if(!acceleration) {return -1;}

    float t1 = this->Speed_max / (float) acceleration;
    float x1 = acceleration * t1 * 0.5;

    float distance = Next_Station->get_next_dist();

    if(distance >= 2 * x1){
        t1;
        float t2 = (distance - (2.0*x1))this->Speed;
        float t3 = this->Speed_max / (float) acceleration;

        if()
        
        //accelerate
        //croisière
        //descelerate
    }
    else{
        //accelerate
        //descelerate
    }

    return EXIT_SUCCESS;
}


float Rame::dist_next_rame(){
    return sqrt(pow(this->x - Next_Rame->get_x(), 2) + pow(this->y - Next_Rame->get_y(), 2));
}
float Rame::dist_next_station(){
    return 0;
}
