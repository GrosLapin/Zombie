#ifndef fonction
#define fonction
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include<string>
#include<iostream>
#include<cmath>
#include <vector>
class Arme;
class Etre;
class Humain;
class Habitation;



	sf::CircleShape makeCircle (int x, int y, int diam, auto color, int largeur)
	{
		sf::CircleShape returne ;
		returne.setPosition(x,y);
		returne.setRadius(diam);
		returne.setFillColor(color);
		returne.setOutlineColor(color);
		returne.setOutlineThickness(largeur);
		return returne;
	};

	sf::RectangleShape makeRectangle  (auto hg, auto bd, auto color, int largeur, sf::Color in = sf::Color::Transparent)
	{
		sf::RectangleShape returne  ;
		returne.setPosition(hg);
//std::cout << bd.x << "   " << " : "  << hg.x  << " "<< bd.x - hg.x << " ::::: " << bd.y  << " " <<  hg.y  <<  " :" << bd.y - hg.y << std::endl;
		returne.setSize({bd.x - hg.x, bd.y - hg.y});
		returne.setFillColor(in);
		returne.setOutlineColor(color);
		returne.setOutlineThickness(largeur);
		return returne;
	};
void lapin ();
void resteDehors (float&x,float&y, Etre* hum);
void displayEtre (Etre& e, sf::Shape& cercle , sf::Shape& cercle2, sf::RenderWindow& app, sf::CircleShape&  cercleVision,sf::Shape& cercleArme);
std::string getDossier(std::string cheminExe);
Habitation*  creationHabitation (sf::Vector2f dimMax);
bool pointDansMaison (sf::Vector2f point);
bool pointDansMaison (float x, float y);
bool maisonValide (float x, float y, float longeur, float hauteur);
void displayPoint (sf::Vector2f& e, sf::Shape& cercle , sf::RenderWindow& app);
float distance (sf::Vector2f a, sf::Vector2f b);
void displayHabitation ( std::vector<Habitation*>& vec , sf::RectangleShape& form , sf::RenderWindow&  app);

#endif // function
