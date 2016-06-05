#include "Humain.hpp"
#include "Famille.hpp"
#include <iostream>
#include "ComportementRencontre.hpp"
#include "Arme.hpp"
#include "Habitation.hpp"
#include "Zombie.hpp"
#include "Etre.hpp"
#include "fonction.hpp"
 sf::Vector2f Humain::baryCentreZombie()
 {
     int nb = 0;
     sf::Vector2f centre ;
     for ( Etre * z : World::vecEtre )
     {
         if ( distance(position, z->position) < rangeVision && !vueCommeUnHummain(z) && z != this )
         {
            if ( nb == 0)
            {
                centre = z->position;
            }
            else
            {
                centre.x = (nb*centre.x + z->position.x)/ (nb+1);
                centre.y = (nb*centre.y + z->position.y)/ (nb+1);
            }

             nb++;
         }
     }

     return centre;

 }


bool Humain::vueCommeUnHummain (Etre *e)
{
    if (( inquietude -30 ) < e->lookGood || e == this)
        return true;
    return false;
}
bool Humain::detectionZombie ()
{
    for ( Etre* e : World::vecEtre )
    {

        if ( !vueCommeUnHummain(e)  && distance(position,e->position) < rangeVision )
        {
            return true;
        }
    }
    return false;
}

Etre* Humain::detectionCible ()
{
    Etre * retour = NULL;
    int nbVue = 0;
    float distanceZ;
     if ( a_arme != NULL )
     {
         for ( Etre* e : World::vecEtre )
        {
            float temp = distance(position,e->position);
            if (!vueCommeUnHummain(e)  && temp < a_arme->range )
            {
                if ( nbVue == 0)
                {
                    distanceZ = temp;
                    retour = e;
                }
                else
                {
                    if ( temp < distanceZ )
                    {
                        distanceZ = temp;
                        retour = e;
                    }
                }

                nbVue++;
            }
        }
     }

    return retour;
}



Humain::Humain()
{
    sousEtat = 0;
    estHumain = 1;
    valeurAttaqueCac = 1;
    a_arme = NULL;
}

 Humain::Humain(float x_, float y_):Etre(x_,y_)
 {

valeurAttaqueCac =0;
     sousEtat = 0;
      estHumain = 1;
      valeurAttaqueCac = 1;
       a_arme = NULL;
 }

bool Humain::updateComportement ( double temps )
{
    age += temps; // on met à jour l'âge du monsieur
    //std::cout << age << std::endl;
    int delais = World::dureeJournee;



    // etat normal : je vais au boulot et je rentre chez moi
    // est ce que tout va bien
    if ( ! detectionZombie () )
    {

        if ( ((int)age % delais) < delais/2 ) // toutes les 10 sec on change
        {
            if ( pointDestination.size() == 0)
                pointDestination.push_back( a_famille->logement->localisation);
            if ( sousEtat != 0)
            {
                //depart = sf::Vector2f(x,y);
                pointDestination.clear();
                pointDestination.push_back( a_famille->logement->localisation);
                sousEtat = 0;
            }
           // std::cout << sousEtat<< std::endl;
            // maison


        }
        else
        {
            // pourquoi ça ralenti
            if ( pointDestination.size() == 0)
                pointDestination.push_back( a_taff->localisation);
            if ( sousEtat != 1)
            {
                //depart = sf::Vector2f(x,y);
                sousEtat = 1;
                  pointDestination.clear();
                   pointDestination.push_back(a_taff->localisation);
               // std::cout<< "ci" << sousEtat <<  std::endl;
            }

            // taff
            //std::cout << sousEtat<< std::endl;


        }
    }
    else // s'il y a un zombie
    {


       if ( pointDestination.size() == 0)
       {
            if ( ((int)age % delais) < delais/2 ) // toutes les 10 sec on change
            {
               pointDestination.push_back( a_famille->logement->localisation);
            }
            else
            {
                pointDestination.push_back( a_taff->localisation);
            }
       }

        Etre* test = this;

        //comportement réaliste ^^
        if ( position.x != a_famille->logement->localisation.x &&
             position.y != a_famille->logement->localisation.y &&
             position.x != a_taff->localisation.x &&
             position.y != a_taff->localisation.y)

        {

             sf::Vector2f centreZombie = baryCentreZombie();
            sf::Vector2f pointCible;
            pointCible.x =  position.x + ( position.x - centreZombie.x) *1  ;
            pointCible.y =  position.y + ( position.y - centreZombie.y) *1  ;

             if (   position.x == centreZombie.x &&  position.y  ==centreZombie.y )
            {
                // il est sur toi cours :!!
                std::cout << "il est sur moi !" << std::endl;
                pointCible .x =  rand() % ( - (int)World::villeHG.x + (int)World::villeBD.x ) + World::villeHG.x ;
                pointCible. y =  rand() % ( - (int)World::villeHG.y+ (int)World::villeBD.y ) + World::villeHG.y;
            }

            pointDestination.clear();
            pointDestination.push_back(pointCible);
        }



        Etre* cible  = detectionCible();
        if ( cible != NULL )
        {

            a_arme->tire(cible, temps, this);
        }

        //std::cout  << "moi :" << position.x <<" " <<position.y << " les zombis " << centreZombie.x << " " << centreZombie.y << " et le resulat " <<  pointCible.x << "  " << pointCible.y <<std::endl;
        // (*a_comportementRencontre)(*test,vec);



        // si on a fuit assez loin ou si on a tué le zombie on continue sa vie
    }


    avance(temps);
    return true;

}

Humain::~Humain()
{

}
