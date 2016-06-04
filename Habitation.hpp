#ifndef habitation
#define habitation
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>

class Habitation
{
	public:
		Habitation(void);
		~Habitation(void);
        int stocke;
		bool alarm;
		sf::Vector2f localisation;
		sf::Vector2f dimention;



	private :


};

#endif // habitation
