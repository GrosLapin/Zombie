#include "Arme.hpp"
#include "Etre.hpp"
#include <iostream>
#include "Humain.hpp"
void Arme::tire (Etre * cible, double temps,  Humain* tireur)
{
    if ( munition > 0 && tempsAvantTir <= 0 )// && cible->vivant )
    {

        tempsAvantTir = delais;
        munition --;
         World::munitionDisponible --;
        int monRand =  rand() % 100;




        if (monRand < hitRate*100 )
        {

            cible->vivant = false;
            cible->tueur = tireur;

        }
    }

    if ( tempsAvantTir > 0)
    {
        tempsAvantTir -= temps;
    }
}



Arme::Arme(void)
{
    range =  World::range;
    delais = World::delais; //sec ?
    tempsAvantTir = 0;
    munition = World::munition ;
    World::munitionDisponible += munition;
    hitRate = 0.7;
}


Arme::~Arme(void)
{
}
