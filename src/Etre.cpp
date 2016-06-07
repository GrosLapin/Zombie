#include "Etre.hpp"
#include "fonction.hpp"


void Etre::constr ()
{
    //depart = sf::Vector2f (0,0);
    rangeVision = World::rangeVisionHumain;
    vitesse =World::VitesseHumain ;
    faim = 10;
    age = 0;
    etat = 0;
    vivant = true;
    zombieKill = false;
    tueur = NULL;
}
Etre::Etre()
{
    position.x = position.y = 0;
   constr ();

}

Etre::Etre(float x_, float y_)
{
    position.x =x_;
    position.y=y_;
   constr ();
}

 bool Etre::avance(double tmp)
{


    if (pointDestination.size() == 0  )
    {
        std::cout <<" FALSE" <<std::endl;
        return false;
    }


    if ( abs(position.x-pointDestination[pointDestination.size()-1].x) < 2 && abs(position.y-pointDestination[pointDestination.size()-1].y)  <2 )
    {
        position.x = pointDestination[pointDestination.size()-1].x;
        position.y = pointDestination[pointDestination.size()-1].y;



        pointDestination.erase( pointDestination.begin() + pointDestination.size() - 1 );
        return true;
    }

    double distance  = vitesse * tmp ;

    int coefX = 1, coefY = 1;
    if ( position.x > pointDestination[pointDestination.size()-1].x )// && point.y>pointDestination.y)
    {
        coefX = coefY = -1;
    }



    if (position.x != pointDestination[pointDestination.size()-1].x )
    {


         //calcul de la pente modulo le fait qu'on soit dans le bon cas
         double a =  (position.y - pointDestination[pointDestination.size()-1].y ) / ( position.x - pointDestination[pointDestination.size()-1].x );
         double b = position.y - a *position.x;

         // d² = x² + y² >> d² = x² +a²x² >> d² = x² ( 1 + a² ) >> x² = d² / ( 1 + a² )
         double x_ =  sqrt( (distance*distance) /( 1 + a*a) ) ;
         double y_= a*x_;

         position.x += (coefX*x_);
         position.y += (coefY* y_);
    }
    else
    {

        if (  position.y > pointDestination[pointDestination.size()-1].y )
            coefY = -1;

         position.y += (coefY*distance);

    }

    resteDehors (position.x,position.y, this);
   //  std::cout << pointDestination.size() << std::endl;
    return false;


}


Etre::~Etre()
{


}
