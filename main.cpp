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
#include "Bouton.h"

using namespace std;

mutex mutex;

int main()
{

    vector<Station> L1;
    vector<Station> L2;

    vector<Rame> L1_rame;
    vector<Rame> L2_rame;

    vector<string> Station_name_L1 = {"Départ", "Quatre Cantons - Stade Pierre-Mauroy", "Cité scientifique - Professeur Gabillard", "Triolo", "Villeneuve-d'Ascq - Hôtel de Ville", "Pont de Bois", "Square Flandres", "Mairie d'Hellemmes", "Marbrerie", "Fives", "Caulier", "Gare Lille-Flandres", "Rihour", "République - Beaux-Arts", "Gambetta", "Wazemmes", "Porte des Postes", "CHU - Centre Oscar-Lambret", "CHU - Eurasanté"};
    vector<vector<double>> Station_position_L1 = {{1745, 40}, {1342, 75}, {1106, 125}, {817, 191}, {792, 309}, {817, 396}, {757, 555}, {665, 651}, {478, 715}, {264, 715}, {155, 760}, {5.5, 5.5}, {6, 6}, {6.5, 6.5}, {7, 7}, {7.5, 7.5}, {8, 8}, {8.5, 8.5}, {9, 9}};
    vector<int> Max_Pass_L1 = {0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

    cout << Station_name_L1.size() << endl;
    cout << Station_position_L1.size() << endl;
    cout << Max_Pass_L1.size() << endl;

    vector<double> coordonates = {1920, 1080};

    Bouton urgence = Bouton((double)10, (double)10);

    for (int i = 0; i < 10; i++)
    {
        L1.emplace_back(Station_name_L1[i], Station_position_L1[i][0], Station_position_L1[i][1], Max_Pass_L1[i]);
    }

    for (int i = 0; i < L1.size(); i++)
    {
        L1[i].calculate_distance(L1);
    }

    

    Rame Rame1 = Rame("Départ", 1, 30, L1_rame.begin(), L1);
    Rame Rame2 = Rame("Quatre Cantons - Stade Pierre-Mauroy", 1, 30, L1_rame.begin(), L1);

    // Créer une fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Déplacement carré");

    thread thread1(move_rame, ref(Rame1), 16, 1.3, 8, L1, ref(urgence));
    thread thread2(move_rame, ref(Rame2), 16, 1.3, 9, L1, ref(urgence));

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

        sf::CircleShape bouton_urgence;
        bouton_urgence.setRadius(20);
        bouton_urgence.setFillColor(sf::Color::Red);
        // Il faut faire en sorte que quand on clique dessus on fait "urgence.change_etat();"

        for (auto start = L1.begin(); start != L1.end(); start++)
        {
            sf::CircleShape station;
            station.setRadius(20);
            if (start->get_occupied() == true)
            {
                if (start->get_leaving() == 1)
                {
                    station.setFillColor(sf::Color::Yellow);
                    // 2 personnes sortent du train par secondes
                }
                else if (start->get_leaving() == 2)
                {
                    station.setFillColor(sf::Color::White);
                    // 2 personnes entrent dans le train par secondes
                }
                else
                {
                    station.setFillColor(sf::Color::Blue);
                }
            }
            else
            {
                station.setFillColor(sf::Color::Green);
            }

            station.setPosition(start->get_x() - 20, start->get_y() - 20);
            window.draw(station);
        }

        sf::RectangleShape r1(sf::Vector2f(30.0f, 10.0f));
        r1.setFillColor(sf::Color::Red);
        r1.setRotation(Rame1.get_arg(L1));
        r1.setPosition(Rame1.get_x() + 15, Rame1.get_y() + 5);

        sf::RectangleShape r2(sf::Vector2f(30.0f, 10.0f));
        r2.setFillColor(sf::Color::Red);
        r2.setRotation(Rame2.get_arg(L1));
        r2.setPosition(Rame2.get_x() + 15, Rame2.get_y() + 5);

        window.draw(r1);
        window.draw(r2);

        window.display();
    }
    thread1.join();
    thread2.join();

    return 0;
}
