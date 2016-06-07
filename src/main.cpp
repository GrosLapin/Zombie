#include <iostream>
#include <fstream>
#include <string>
#include "fonction.hpp"
#include <map>
#include <set>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <math.h>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>
#include <thread>
#include "Etre.hpp"
#include "Humain.hpp"
#include "Habitation.hpp"
#include "Famille.hpp"
#include "fonction.hpp"
#include "Word.hpp"
#include "Zombie.hpp"
#include "Arme.hpp"

using namespace std;
int main( int argc, char *argv[])
{

    std::string dossier =  World::getDossier(argv[0]);
    World::ChargeFile(dossier);

    sf::RenderWindow  app(sf::VideoMode(World::maxX,World::maxY, 32), "SFML Window");
    bool Running = true;



    sf::CircleShape shapeHumain = makeCircle(0,0,5,sf::Color::Red,0);
    sf::CircleShape shapeCible = makeCircle (0,0,5,sf::Color::Blue,0);
    sf::CircleShape superZombie =makeCircle(0,0,5,sf::Color::Cyan,0);
    sf::RectangleShape carre = makeRectangle(World::villeHG, World::villeBD, sf::Color::White,1);
    // Désactive le remplissage de la forme
	
    //carre.enableFill(false);
    // Active l'affichage de sa bordure
    //carre.EnableOutline(true);


    sf::CircleShape cercleVision;
    srand(time(NULL));

    /// liste des bâtiments c'est redondant mais ça me simplifie la vie
   // std::vector<Habitation *> vecBatiment;
    //std::vector<Etre *> vecEtre;
    ///création des bureaux
    int nbBureau = World::nbBureau;
    float dimMaxMaison = World::dimMaxMaison;
    std::vector<Habitation *> vecBureau;

      std::vector<Famille *> vecFamille;
    int nbFamille = World::nbFamille;
    int nbMembreMax = World::nbMembreMax;
    int tauxArme = World::tauxArme;
    int  nbZ =World::nbZombie;

    // perte de confiance
    float variationConfiance = World::variationConfiance;
    // augmentation du FF
    float variationInquitudeFix = World::variationInquitudeFix;
    float variationInquitudePourCent = World::variationInquitudePourCent;

    for (int i =0 ; i< nbBureau; i++)
    {
        vecBureau.push_back(creationHabitation (sf::Vector2f(dimMaxMaison,dimMaxMaison) ));
        World::vecBatiment.push_back(vecBureau[i]);
    }

    /// création des familles avec leurs maisons et leurs membres
    for ( int i =0 ; i <  nbFamille ; i ++ )
    {
         Famille* temp = new Famille();
         // creation d'une maison quelque part ^^
         temp->logement = creationHabitation (sf::Vector2f(dimMaxMaison,dimMaxMaison) );
         World::vecBatiment.push_back(temp->logement);
         int nbMembre = nbMembreMax;//  rand() % (nbMembreMax -1) +1;
         for ( int j = 0 ; j < nbMembre ; j++ )
         {
             Humain* hum = new Humain( temp->logement->localisation.x , temp->logement->localisation.y  );

             // armement
             if ( rand() %100 < tauxArme )
             hum->a_arme = new Arme();

             // parano
             hum->inquietude =rand() %  (int)World::inquietudeMax ;
             hum->lookGood   =rand() %  (int)World::bonneTeteMax + 30; //45;


             hum->a_famille = temp;
             hum->age = rand() % 1000;
             hum->a_taff = vecBureau[rand()%nbBureau];
             // eventuellement mettre un rand sur l'âge qu'il ne bouge pas tous en même temps
             temp->membre.push_back(hum);
             World::vecEtre.push_back(hum);
         }
         vecFamille.push_back(temp);
    }


    Zombie* lapin;

    for ( int i = 0 ; i < nbZ ; i++ )
    {

        lapin = new Zombie( World::maxX /2  ,  World::maxY /2 );
        int lookok =rand() % (int)World::bonneTeteMaxZombie;
        lapin->lookGood   = lookok;
        World::vecEtre.push_back(lapin);

    }

    sf::RectangleShape Rect;
    sf::Clock timer;
	double temps = 0;
    World::saveStat(dossier,  0.0);
    while (Running)
    {

        app.clear(sf::Color::Black);
		temps = timer.getElapsedTime().asSeconds();
		timer.restart();
        sf::Event Event;
        while (app.pollEvent(Event))
        {
            // Fenêtre fermée
            if (Event.type == sf::Event::Closed)
                Running = false;

            // Touche 'echap' appuyée
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                Running = false;
        }





        // affichage de truc
        displayHabitation(World::vecBatiment,Rect,app);


        for ( int i = 0 ; i < World::vecEtre.size() ; i++)
        {
            displayEtre (*(World::vecEtre[i]),shapeHumain,shapeCible,app, cercleVision,superZombie);


            //World::vecEtre[i]->updateComportement(app.GetFrameTime());
			World::vecEtre[i]->updateComportement(temps);
        }


        int bnEtre = World::vecEtre.size();

        for ( int i = bnEtre-1 ; i >= 0 ; i--)
        {

            Etre * e = World::vecEtre[i];
            if ( ! e->vivant )
            {
                if( e->zombieKill  )
                {
                    Zombie* sophie = new Zombie(e->position.x, e->position.y) ;
                    sophie->pointDestination.push_back(sf::Vector2f(rand()% World::maxX, rand()% World::maxY ));

                    int lookok ;
                    if (  World::garderConfiance == 0)
                       lookok = rand() % (int)World::bonneTeteMaxZombie;
                    else
                        lookok = e->lookGood;

                    std::cout << lookok << std::endl;
                    sophie->lookGood   = lookok;
                    World::vecEtre.push_back(sophie);

                }


                // si la victime est un humain, le tireur perd de la réputition
                if ( e->tueur != NULL )
                {
                   if ( e->estHumain == 1 )
                    {
                    World::nbHumainKilled ++;
                       e->tueur->lookGood *= variationConfiance;

                       // Si un humain est tuer par un Zombie
                       if ( e->tueur->estHumain == 0 )
                       {
                           // on fait un calcul pour que ceux  qui auraient fait confiance au tueur, soit plus méfiant,
                           for ( Etre* E : World::vecEtre )
                           {
                               if ( E->estHumain == 1 && E->vivant)
                               {
                                   Humain * H = (Humain*)E;
                                   // H aurais fait confiance a ce zombie
                                   if ( H->vueCommeUnHummain(e->tueur) )
                                   {
                                        H->inquietude += variationInquitudeFix;
                                        H->inquietude *= variationInquitudePourCent;
                                   }
                               }
                           }
                       }
                       else
                       {
                           std::cout<<"shoot d'allier" << std::endl;
                           World::nbFF++;
                       }
                    }
                    else
                    {
                       e->tueur->lookGood /= variationConfiance;
                        World::nbZombieKilled++;


                    }
                }




                if ( std::find ( World::vecEtre.begin() , World::vecEtre.end() , e ) != World::vecEtre.end() )
                {
                    World::vecEtre.erase(std::find ( World::vecEtre.begin() , World::vecEtre.end() , e ) );
                    delete e;
                }


            }
        }

//    	World::saveStat(dossier, app.GetFrameTime());
		World::saveStat(dossier, temps);

        //app.Draw ( carre);
     app.display();


    }
    return EXIT_SUCCESS;
}
