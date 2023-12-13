#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include"Rame.h"
#include "function.h"

// Faire la fonction avec les different if (si on arrive au bout alors on repars en arrière -1.)
// Si on est au debut on avance en +1 jusqu'a atteindre le bout et donc repartir en arriere.
// On accede au next rame grace a un vecteur qui contient des ppointeur vers des station. Ensuite on utilise get name pour le nom.
void move_rame(Rame rame, float t_ref, float acceleration, int nb_station){
    //wrapper
    
    for(int i = 0; i < nb_station ; i++){
    rame.go_to_next_station(acceleration, t_ref);
    
    cout << "AAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAAAAAAA\nAAAAAAAAAAAAAAAAA\nAAAAAAAAAAA" << endl;
    }
}