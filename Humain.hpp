#ifndef humain
#define humain
#include "Etre.hpp"
class Arme;
class Habitation;


class Famille;
class ComportementRencontre;
class Humain : public Etre
{

	public:
		Humain();
		~Humain();
		 Humain(float x_, float y_);
        virtual bool updateComportement( double temps );
		ComportementRencontre* a_comportementRencontre; // classe foncteur pour implémenter fuyard / fighteur / mixte

        sf::Vector2f baryCentreZombie();

        bool detectionZombie ();
        Etre* detectionCible ();


        std::vector<Etre> listZombie() { return std::vector<Etre>() ;};
        float tauxReproductionAn;
        bool vueCommeUnHummain (Etre *e);
		float inquietude;		// plus il est inquiet moins il va hésiter avant de taper sur qqn

		Arme* a_arme;
		Famille* a_famille;
		Habitation* a_taff;
	private :
        int sousEtat;



};

#endif
