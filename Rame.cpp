#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include<cmath>
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Rame.h"
//#include "Station.h"


using namespace std;

// Constructor :
Rame::Rame(string station, int Ligne, int Nb_pass_Max, vector<Rame>::iterator &RameList, vector<Station> &station_list) {
    
    for(int i = 0; i < station_list.size(); i++){
        if(station == station_list[i].get_name()){
            this->x = station_list[i].get_x();
            this->y = station_list[i].get_y();
        }
    }
    
    this->Speed = 0;
    this->Speed_max = 100;
    //this->Id = RameList.size();
    this->Ligne = Ligne;
    this->Nb_pass_Max = Nb_pass_Max;
    this->Nb_pass = 0;


    this->Next_Station = station_list.begin();
    ++this->Next_Station; 
    

    // if (RameList.empty()){
    //     this->Next_Rame = NULL;
    // }
    // else{
    //     this->Next_Rame = RameList.back();
    // }

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

    cout << "Speed : " << this->Speed << endl;

    float t1 = this->Speed_max / (float) acceleration;
    float d1 = acceleration * 0.5 * pow(t1, 2);

    float distance = Next_Station->get_next_dist();
    float where = this->dist_next_station();

    while (this->dist_next_station() > 0){
        cout << "Speed : " << this->Speed << endl;
        cout << "t1 : " << t1 << endl;
        cout << "d1 : " << d1 << endl;
        cout << "distance : " << distance << endl;


        if(distance >= 2 * d1){
            t1;
            d1;

            float t2 = (distance - (2.0*d1)) / this->Speed;
            float d2 = acceleration * 0.5 * pow(t2, 2);

            float t3 = this->Speed_max / (float) acceleration;
            float d3 = acceleration * 0.5 * pow(t3, 2);

            if(distance - where > d1){
                //accelerate
                this->Speed = this->Speed + (acceleration * (t_mili/1000));

            }

            else if(distance - where > d2){
                //croisière
                this->Speed = this->Speed_max;
            }

            else if(distance - where > d3){
                //descelerate
                this->Speed = this->Speed - (acceleration * (t_mili/1000));
            }
            
        }
        else{
        t1;
        //accelerate
        //descelerate
        }
        //this_thread::sleep_for(chrono::milliseconds(t_mili));
    }
    return EXIT_SUCCESS;
}


float Rame::dist_next_rame(){
    return sqrt(pow(this->x - Next_Rame->get_x(), 2) + pow(this->y - Next_Rame->get_y(), 2));
}
float Rame::dist_next_station(){
    return sqrt(pow(this->x - this->Next_Station->get_x(), 2) + pow(this->y - this->Next_Station->get_y(), 2));
}
