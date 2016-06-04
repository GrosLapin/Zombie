#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Etre.hpp"


class Zombie : public Etre
{
    public:
        Zombie();
        Zombie(float x, float y);
        virtual ~Zombie();
        virtual bool updateComportement( double temps );
        float rangeAttaque;

    protected:
        void emplacementValide (sf::Vector2f& coord);
    private:
};

#endif // ZOMBIE_H
