#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include "Station.h"
#include "Rame.h"
#include "function.h"

using namespace std;

int main()
{
    vector<Station> L1;
    vector<Station> L2;

    vector<Rame> L1_rame;
    vector<Rame> L2_rame;

    vector<string> Station_name_L1 = {"Départ", "Quatre Cantons - Stade Pierre-Mauroy", "Cité scientifique - Professeur Gabillard", "Triolo", "Villeneuve-d'Ascq - Hôtel de Ville", "Pont de Bois", "Square Flandres", "Mairie d'Hellemmes", "Marbrerie", "Fives", "Caulier", "Gare Lille-Flandres", "Rihour", "République - Beaux-Arts", "Gambetta", "Wazemmes", "Porte des Postes", "CHU - Centre Oscar-Lambret", "CHU - Eurasanté"};
    // vector<vector<double>> Station_position_L1 = {{0,0}, {10000, 10000}, {1,1}, {1.5, 1.5}, {2,2}, {2.5, 2.5}, {3,3}, {3.5, 3.5}, {4,4}, {4.5, 4.5}, {5,5}, {5.5, 5.5}, {6,6}, {6.5, 6.5}, {7,7}, {7.5, 7.5}, {8,8}, {8.5, 8.5}, {9,9}};
    vector<vector<double>> Station_position_L1 = {{1745, 20}, {1342, 75}, {1106, 125}, {817, 191}, {792, 309}, {817, 396}, {757, 555}, {665, 651}, {478, 715}, {264, 715}, {155, 760}, {5.5, 5.5}, {6, 6}, {6.5, 6.5}, {7, 7}, {7.5, 7.5}, {8, 8}, {8.5, 8.5}, {9, 9}};
    vector<int> Max_Pass_L1 = {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    cout << Station_name_L1.size() << endl;
    cout << Station_position_L1.size() << endl;
    cout << Max_Pass_L1.size() << endl;

    vector<double> coordonates = {1920, 1080};

    for (int i = 0; i < 10; i++)
    {
        L1.emplace_back(Station_name_L1[i], Station_position_L1[i][0], Station_position_L1[i][1], Max_Pass_L1[i], coordonates);
    }

    for (int i = 0; i < L1.size(); i++)
    {
        L1[i].calculate_distance(L1);
    }

    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Déplacement carré");

    Rame Rame1 = Rame("Départ", 1, 30, L1_rame.begin(), L1);
    Rame Rame2 = Rame("Quatre Cantons - Stade Pierre-Mauroy", 1, 30, L1_rame.begin(), L1);

    thread thread1(move_rame, Rame1, 100, 1.3, 8, L1);

    while (window.isOpen())
    {
        // Gére les événements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Créer un carré
        sf::RectangleShape square(sf::Vector2f(50.0f, 50.0f));
        square.setFillColor(sf::Color::Green);

        square.setPosition(Rame1.get_x(), Rame1.get_y());

        // thread thread2(move_rame, Rame2, 16, 1.3, 9, L1);
    }
    thread1.join();
    // thread2.join();

    return 0;
}
