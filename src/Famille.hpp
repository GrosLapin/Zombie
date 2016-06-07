#ifndef famille
#define famille
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <vector>

class Humain;
class Habitation;
class Famille
{
	public:
		Famille(void);
		Famille(sf::Vector2f localisation);
		~Famille(void);
		std::vector<Humain* > membre;
		Habitation* logement;
	private:


};

#endif // famille
