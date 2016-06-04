#ifndef ETRE_H
#define ETRE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Word.h"
#include <algorithm>
class Etre
{
    public:
        Etre();
        Etre(float x_, float y_);
        virtual ~Etre();
        sf::Vector2f position;
        std::vector<sf::Vector2f> pointDestination;
        //sf::Vector2f depart;

        bool avance(double tmp);

        virtual bool updateComportement( double temps ) = 0;
        float lookGood;			// plus tu as une tete correcte, moins on te tape dessus, delis de sale guelle quoi

        int etat;
        float rangeVision;
        float vitesse;
		float faim;
		float age;
		int estHumain;
        float valeurAttaqueCac;
        bool vivant;
        Etre* tueur;
        bool zombieKill;
    protected:
        void constr ();


    private:
};

#endif // ETRE_H
