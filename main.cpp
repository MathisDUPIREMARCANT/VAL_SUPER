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

#define ACC 1.3

using namespace std;

mutex mutex;

int main()
{

    vector<Station> L1;
    vector<Station> L2;

    vector<Rame> L1_rame;
    vector<Rame> L2_rame;

    vector<string> Station_name_L1 = {"Depart", "A_Lille Europe", "A_Lile Flandre ", "A_Rihour", "A_Republique", "A_Gambetta", "A_Wazemme", "A_Porte des Postes", "A_CHU", "Arrivee", "R_CHU", "R_Porte des Postes", "R_Wazemme", "R_Gambetta", "R_Republique", "R_Rihour", "R_Lille Flandre", "R_Lille Europe"};
    vector<vector<double>> Station_position_L1 = {{1745, 40}, {1342, 75}, {1106, 125}, {817, 191}, {792, 309}, {817, 396}, {757, 555}, {665, 651}, {478, 715}, {264, 715}, {518, 755}, {705, 691}, {797, 595}, {857, 436}, {832, 349}, {857, 231}, {1146, 165}, {1382, 115}};
    vector<int> Max_Pass_L1 = {0, 10, 10, 10, 10, 10, 10, 10, 0, 0, 10, 10, 10, 10, 10, 10, 10, 0};

    vector<double> coordonates = {1920, 1080};

    Bouton urgence = Bouton((double)10, (double)10);

    for (int i = 0; i < Station_name_L1.size(); i++)
    {
        L1.emplace_back(Station_name_L1[i], Station_position_L1[i][0], Station_position_L1[i][1], Max_Pass_L1[i]);
    }

    for (int i = 0; i < Station_name_L1.size(); i++)
    {
        L1[i].calculate_distance(L1);
    }

    Rame Rame1 = Rame("Depart", 1, 30, L1_rame.begin(), ref(L1));
    Rame Rame2 = Rame("R_Rihour", 1, 30, L1_rame.begin(), ref(L1));
    Rame Rame3 = Rame("A_Rihour", 1, 30, L1_rame.begin(), ref(L1));

    sf::RenderWindow window(sf::VideoMode(coordonates[0], coordonates[1]), "VAL : DUPIRE-MARCANT & LAROUZIERE");

    thread thread1(move_rame, ref(Rame1), 16, ACC, 20, ref(L1), ref(urgence));
    thread thread2(move_rame, ref(Rame2), 16, ACC, 20, ref(L1), ref(urgence));
    thread thread3(move_rame, ref(Rame3), 16, ACC, 20, ref(L1), ref(urgence));

    // station 
    sf::Texture stationTexture;
    if (!stationTexture.loadFromFile("../../image/station.png")) {
        return -1; // Erreur de chargement de l'image de la station
    }

    // background
    sf::Texture backgroundTexture;

    if (!backgroundTexture.loadFromFile("../../image/image.jpg")) {
        
    }

    sf::Texture enteringTexture, exitingTexture;
    
    // Charger les images personne
    enteringTexture.loadFromFile("../../image/entering.png");
    exitingTexture.loadFromFile("../../image/exiting.png");

    // Charger une texture pour l'objet
    sf::Texture objectTexture;
    if (!objectTexture.loadFromFile("../../image/metro.png")) {
        return -2; // Erreur de chargement de l'image de l'objet
    }

    // Créer un sprite pour l'arrière-plan
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    sf::Sprite r1(objectTexture);
    sf::Sprite r2(objectTexture);
    sf::Sprite r3(objectTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);

        sf::CircleShape bouton_urgence;
        bouton_urgence.setRadius(20);
        bouton_urgence.setFillColor(sf::Color::Red);

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                // Obtiens la position du clic et compare avec la position et la taille du bouton
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f buttonPos = bouton_urgence.getPosition();

                float radius = bouton_urgence.getRadius();
                sf::Vector2f buttonSize(radius * 2, radius * 2);

                // Vérifie si le clic est à l'intérieur du bouton
                if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x && mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y) {
                    // Le clic est sur le bouton, appele change_etat()
                    urgence.change_etat();
                    bouton_urgence.setFillColor(sf::Color::Blue);
                }
            }
        }
        

        for (auto start = L1.begin(); start != L1.end(); start++) {
            sf::Sprite station(stationTexture);
            station.setPosition(start->get_x(), start->get_y());
            station.setRotation((start->get_next_arg() * 180 / 3.14) - 90);

            window.draw(station);

            if (start->get_occupied() == true) {
                sf::Sprite stateSprite;
                if (start->get_leaving() == 1) 
                {
                    stateSprite.setTexture(exitingTexture);
                } else if (start->get_leaving() == 2) 
                {
                    stateSprite.setTexture(enteringTexture);
                }
                stateSprite.setPosition(start->get_x(), start->get_y());
                window.draw(stateSprite);
            }
            
        }

        
        r1.setRotation(Rame1.get_arg(L1, 0));
        r1.setPosition(Rame1.get_x(), Rame1.get_y());

        
        r2.setRotation(Rame2.get_arg(L1, 0));
        r2.setPosition(Rame2.get_x(), Rame2.get_y() + 10);

        
        r3.setRotation(Rame3.get_arg(L1, 0));
        r3.setPosition(Rame3.get_x(), Rame3.get_y() + 10);

        window.draw(r1);
        window.draw(r2);
        window.draw(r3);
        window.draw(bouton_urgence);

        window.display();
    }
    thread1.join();
    thread2.join();
    thread3.join();

    return 0;
}
