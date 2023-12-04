#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include"Rame.h"

vector<Rame> init_rame(vector<string> stations, vector<int> lignes, vector<int> capacity, vector<Rame*> RameList){
    vector<Rame> result;
    for(int i=0; i<stations.size(); i++){
        Rame wagon = Rame(stations[i], lignes[i], capacity[i], RameList);
        RameList.push_back(&wagon);
        result.push_back(wagon);
    }
    result[0].Next_Rame = &result.back();
    return result;
}


void Next_Station(){
    if ( == size){

    } 
} 
// Faire la fonction avec les different if (si on arrive au bout alors on repars en arrière -1.)
// Si on est au debut on avance en +1 jusqu'a atteindre le bout et donc repartir en arriere. 
//On accede au next rame grace a un vecteur qui contient des ppointeur vers des station. Ensuite on utilise get name pour le nom. 