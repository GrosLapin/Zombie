#ifndef ARm
#define ARm

class Etre;
class Humain;
class Arme
{
	public:
		Arme(void);
		~Arme(void);


		float range;
		double delais;
		double tempsAvantTir;
		double hitRate;
		int munition;

		void tire (Etre * cible, double temps, Humain* tireur);

    private :

};


#endif // ARm
