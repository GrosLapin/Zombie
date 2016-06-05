#include "Zombie.hpp"
#include <SFML/Graphics.hpp>
#include "Word.hpp"
#include "fonction.hpp"
#include "Humain.hpp"
#include "Habitation.hpp"
#include "Famille.hpp"
Zombie::Zombie()
{
    estHumain = 0;
    rangeVision = World::rangeVisionZombie;
    rangeAttaque = 4;
    valeurAttaqueCac = World::valeurAttaqueCacZombie;
}

Zombie::Zombie(float x, float y)
{

    sf::Vector2f laba = sf::Vector2f(x,y);
    emplacementValide(laba);
    position = laba;

    estHumain = 0;
    rangeVision =  World::rangeVisionZombie;
    rangeAttaque = 4;
    valeurAttaqueCac = World::valeurAttaqueCacZombie;
}
void Zombie::emplacementValide (sf::Vector2f& coord)
{
    for ( Habitation * hab : World::vecBatiment )
    {
        if (   coord.x > hab->localisation.x    &&
               coord.x < hab->localisation.x + hab->dimention.x      &&
               coord.y > hab->localisation.y    &&
               coord.y < hab->localisation.y + hab->dimention.y
            )
        {
            sf::Vector2f hg (hab->localisation.x,hab->localisation.y);
            sf::Vector2f bg (hab->localisation.x,hab->localisation.y+ hab->dimention.y);
            sf::Vector2f hd (hab->localisation.x+ hab->dimention.x,hab->localisation.y);
            sf::Vector2f bd (hab->localisation.x+ hab->dimention.x,hab->localisation.y+ hab->dimention.y);

                // on replace le point
            float min = abs(coord.x - hg.x );
            int cas = 0;
            if ( min >  abs(coord.x - hd.x ))
            {
                min =  abs(coord.x - hd.x );
                cas = 1;
            }
            if ( min >  abs(coord.y - hg.y ))
             {
                min=  abs(coord.y - hg.y );
                cas = 2;
            }

            if ( min >  abs(coord.y - bg.y ))
            {
                 min=  abs(coord.y - bg.y );
                 cas = 3;
            }
            switch (cas)
            {
                case 0 : coord.x = hg.x ;

                    break;
                case 1 :coord.x = hd.x ;

                    break;
                case 2 : coord.y = hg.y  ;

                    break;
                case 3 : coord.y = bg.y ;

                    break;
            }
        }
    }

}
Zombie::~Zombie()
{
    //dtor
}

bool Zombie::updateComportement ( double temps )
{
    age += temps*1000; // on met à jour l'âge du monsieur


    // on est à 1 si on voit qqn sinon on est à 0

    Etre* cible = NULL;
    for ( Etre* e : World::vecEtre )
    {
        // est ce que c'est a porté
        if ( e->estHumain == 1  && distance(position,e->position) < rangeVision )
        {

            Humain* E = (Humain*)e;
            // maison !! mais eu... j'etait dans la maison, tu as pas le droit !!! je vais le dire a la maitresse
            if ( E->position.x != E->a_famille->logement->localisation.x &&
                 E->position.y != E->a_famille->logement->localisation.y &&
                 E->position.x != E->a_taff->localisation.x &&
                 E->position.y != E->a_taff->localisation.y)
            cible = e;
        }


    }

    etat = 0;
    if ( cible != NULL )
        etat = 1;


    switch (etat)
    {
        // état normal : je me balade sans but
        case 0 :

            vitesse = 50;
            // si on sait pas ou aller , on crée un point ^^
            if ( pointDestination.size() == 0)
            {

                int x =  rand() % ( - (int)World::villeHG.x + (int)World::villeBD.x ) + World::villeHG.x ;
                int y =  rand() % ( - (int)World::villeHG.y+ (int)World::villeBD.y ) + World::villeHG.y;
                sf::Vector2f laba = sf::Vector2f (x, y );
                emplacementValide(laba);
                pointDestination.push_back(laba);
            }

            break;
        case 1 :
            vitesse = World::VitesseHumain * World::ZombieSprint;
           // std::cout  <<  World::VitesseHumain << "  *  "<<   World::ZombieSprint<<" = "<< vitesse <<  std::endl;
            // si on peut on le mange
            if ( distance(cible->position, position) < rangeAttaque )
            {

                float teta = (valeurAttaqueCac / (float)( valeurAttaqueCac + cible->valeurAttaqueCac)) * 100;
                if ( rand() % 100 < teta )
                {
                    // zombie gagne
                   /* Zombie* sophie = new Zombie(cible->position.x, cible->position.y) ;
                    sophie->pointDestination.push_back(sf::Vector2f(rand()% World::maxX, rand()% World::maxY ));
                    World::vecEtre.push_back(sophie);*/

                    cible -> vivant = false;
                    cible -> zombieKill = true;
                     cible ->tueur = this;
                    std::cout << teta << std::endl;
                }
                else
                {
                    // humain bad ass
                    World::nbZombieKilledByHand ++;
                    vivant = false;
                    tueur = cible;
                    std::cout << "Noris" << std::endl;


                }

            }

            if ( pointDestination.size() == 0)
            {
                pointDestination.push_back(cible->position);
            }
            else
            {
                pointDestination[0] = cible->position ;
            }

            break;
    }

    avance(temps);
    return true;

}
