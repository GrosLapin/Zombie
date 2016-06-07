#include "Famille.hpp"
#include "Humain.hpp"
#include "Habitation.hpp"

Famille::Famille(sf::Vector2f localisation)
{
    logement = new Habitation ();
    logement->localisation = localisation;
}
Famille::Famille(void)
{
}


Famille::~Famille(void)
{
}
