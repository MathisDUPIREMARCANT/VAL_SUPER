#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Station.h"
//#include "Rame.h"

using namespace std;


void test(int a){
    for(int i = 0; i<a; i++){
        cout << "hey : " << i << endl;
    }
}

int main(){
    // vector<Station> L1;
    // vector<Station> L2;

    // vector<string> Station_name_L1 = {"Départ", "Quatre Cantons - Stade Pierre-Mauroy", "Cité scientifique - Professeur Gabillard", "Triolo", "Villeneuve-d'Ascq - Hôtel de Ville", "Pont de Bois", "Square Flandres", "Mairie d'Hellemmes", "Marbrerie", "Fives", "Caulier", "Gare Lille-Flandres", "Rihour", "République - Beaux-Arts", "Gambetta", "Wazemmes", "Porte des Postes", "CHU - Centre Oscar-Lambret", "CHU - Eurasanté"};
    // vector<vector<float>> Station_position_L1 = {{0,0}, {0.5, 0.5}, {1,1}, {1.5, 1.5}, {2,2}, {2.5, 2.5}, {3,3}, {3.5, 3.5}, {4,4}, {4.5, 4.5}, {5,5}, {5.5, 5.5}, {6,6}, {6.5, 6.5}, {7,7}, {7.5, 7.5}, {8,8}, {8.5, 8.5}, {9,9}};
    // vector<int> Max_Pass_L1 = {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
    
    // cout << Station_name_L1.size() << endl;
    // cout << Station_position_L1.size() << endl;
    // cout << Max_Pass_L1.size() << endl;

    // for(int i = 0; i < Station_name_L1.size(); i++){
    //     L1.emplace_back(Station_name_L1[i], Station_position_L1[i][0], Station_position_L1[i][1], Max_Pass_L1[i]);
    // }

    // for(int i = 0; i < L1.size(); i++){
    //     L1[i].calculate_distance(L1);
    // }

    //constexpr pdp("Porte des postes",2,3)

    //Rame Rame1 = Rame("Quatre Cantons - Stade Pierre-Mauroy", 1, 10, RameList);

    thread thread1(test, 43);
    thread thread2(test, 100);

    thread1.join();
    thread2.join();




    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}