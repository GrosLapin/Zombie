#include "fonction.hpp"
#include "Etre.hpp"
#include "Habitation.hpp"
#include "Humain.hpp"
#include "Word.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Arme.hpp"

using namespace std;
bool maisonValide (float x, float y, float longeur, float hauteur)
{
    // on supose que tout les points de la maison sont valide
     int i = 0;
    bool pointOk = true;

    // on est dans personne
    while (  i < World::vecBatiment.size()  && pointOk )
    {
        Habitation * hab =  World::vecBatiment[i];

        std::vector<sf::Vector2f> vec;
        vec.push_back( sf::Vector2f(hab->localisation.x                      ,hab->localisation.y                    ) ) ;
        vec.push_back( sf::Vector2f(hab->localisation.x + hab->dimention.x   ,hab->localisation.y                    ) ) ;
        vec.push_back( sf::Vector2f(hab->localisation.x                      ,hab->localisation.y +  hab->dimention.y) ) ;
        vec.push_back( sf::Vector2f(hab->localisation.x + hab->dimention.x   ,hab->localisation.y +  hab->dimention.y) ) ;

        for ( sf::Vector2f point : vec )
        {
            if ( point.x > x    && point.x < x +  longeur     &&
                 point.y > y    && point.y < y +  hauteur
               )
            {
                pointOk = false;
            }
        }

        i++;
    }

    return pointOk;
}
bool pointDansMaison (sf::Vector2f point)
{
    int i = 0;
    bool pointOk = true;

    // on est dans personne
    while (  i < World::vecBatiment.size()  && pointOk )
    {
        Habitation * hab =  World::vecBatiment[i];
        if ( point.x > hab->localisation.x    && point.x < hab->localisation.x + hab->dimention.x      &&
             point.y > hab->localisation.y    && point.y < hab->localisation.y + hab->dimention.y
            )
        {
            pointOk = false;
        }
        i++;
    }

    return !pointOk;
}
bool pointDansMaison (float x, float y)
{
    return pointDansMaison(sf::Vector2f(x,y));
}
float distance (sf::Vector2f a, sf::Vector2f b)
 {
     return  sqrt((a.x - b.x)*(a.x -b.x) + (a.y - b.y)*(a.y - b.y));
    }
void resteDehors (float&x,float&y,Etre* hum)
{



    // peut avoir des effet de bord si 2 maison se chevoche
    for ( Habitation* hab : World::vecBatiment )
    {
        // si on est dans un batiement

        sf::Vector2f hg (hab->localisation.x,hab->localisation.y);
        sf::Vector2f bg (hab->localisation.x,hab->localisation.y+ hab->dimention.y);
        sf::Vector2f hd (hab->localisation.x+ hab->dimention.x,hab->localisation.y);

        sf::Vector2f bd (hab->localisation.x+ hab->dimention.x,hab->localisation.y+ hab->dimention.y);

        //test debug
        if ( hum->pointDestination.back().x > hab->localisation.x    &&
             hum->pointDestination.back().x < hab->localisation.x + hab->dimention.x      &&
             hum->pointDestination.back().y > hab->localisation.y     &&
             hum->pointDestination.back().y < hab->localisation.y + hab->dimention.y
            )
        {
            float min = abs(hum->pointDestination.back().x - hg.x );
            int cas = 0;
            if ( min >  abs(hum->pointDestination.back().x - hd.x ))
            {
                min =  abs(hum->pointDestination.back().x - hd.x );
                cas = 1;
            }
            if ( min >  abs(hum->pointDestination.back().y - hg.y ))
             {
                min=  abs(hum->pointDestination.back().y - hg.y );
                cas = 2;
            }

            if ( min >  abs(hum->pointDestination.back().y - bg.y ))
            {
                 min=  abs(hum->pointDestination.back().y - bg.y );
                 cas = 3;
            }
            switch (cas)
            {
                case 0 : hum->pointDestination.back().x = hg.x ;


                    break;
                case 1 : hum->pointDestination.back().x = hd.x ;

                    break;
                case 2 : hum->pointDestination.back().y = hg.y  ;

                    break;
                case 3 : hum->pointDestination.back().y = bg.y ;

                    break;
            }
        }
        //fin test

        if ( x > hab->localisation.x    && x < hab->localisation.x + hab->dimention.x      &&
             y > hab->localisation.y    && y < hab->localisation.y + hab->dimention.y
            )
        {

            // on replace le point
            float min = abs(x - hg.x );
            int cas = 0;
            if ( min >  abs(x - hd.x ))
            {
                min =  abs(x - hd.x );
                cas = 1;
            }
            if ( min >  abs(y - hg.y ))
             {
                min=  abs(y - hg.y );
                cas = 2;
            }

            if ( min >  abs(y - bg.y ))
            {
                 min=  abs(y - bg.y );
                 cas = 3;
            }
            std::pair<sf::Vector2f,sf::Vector2f> pointProche;
            std::pair<sf::Vector2f,sf::Vector2f> deuxiemePointProche;
            switch (cas)
            {
                case 0 : x = hg.x ;
                    pointProche.first = hg ;
                    pointProche.second = bg;

                    deuxiemePointProche.first = hd;
                    deuxiemePointProche.second = bd;
                    break;
                case 1 : x = hd.x ;
                    pointProche.first = hd ;
                    pointProche.second = bd;

                    deuxiemePointProche.first = hg;
                    deuxiemePointProche.second = bg;
                    break;
                case 2 : y = hg.y  ;
                    pointProche.first = hg ;
                    pointProche.second = hd;

                    deuxiemePointProche.first = bg;
                    deuxiemePointProche.second = bd;
                    break;
                case 3 : y = bg.y ;
                    pointProche.first = bg ;
                    pointProche.second = bd;

                    deuxiemePointProche.first = hg;
                    deuxiemePointProche.second = hd;
                    break;
            }

            //
            sf::Vector2f PremierPoint = pointProche.first;
            sf::Vector2f pointElimine = pointProche.second;
            bool premier = true;

            float distanceFirst =  distance(hum->pointDestination.front() ,pointProche.first);
            float distanceSecond =  distance(hum->pointDestination.front(),pointProche.second);
            if ( distanceSecond <  distanceFirst )
            {
                premier = false;
                PremierPoint = pointProche.second;
                pointElimine = pointProche.first;
            }


            // on regarde maintenant si on a besoin d'un coins en plus
            if ( premier )
            {
                if (   distance (PremierPoint, hum->pointDestination.back() ) >  distance (deuxiemePointProche.first, hum->pointDestination.back() ) )
                {
                    hum->pointDestination.push_back(deuxiemePointProche.first);
                    // std::cout << " 2 " << std::endl;
                }

            }
            else
            {
                if (   distance (PremierPoint, hum->pointDestination.back() ) >  distance (deuxiemePointProche.second, hum->pointDestination.back() ) )
                {
                    hum->pointDestination.push_back(deuxiemePointProche.second);
                   //  std::cout << " 2 2 " << std::endl;

                }
            }

             hum->pointDestination.push_back(PremierPoint);



        }
    }

}

void displayPoint (sf::Vector2f& e, sf::Shape& cercle , sf::RenderWindow& app)
{
    cercle.setPosition(e);
    app.draw(cercle);
}


void displayEtre (Etre& e, sf::Shape& cercle , sf::Shape& cercle2, sf::RenderWindow& app, sf::CircleShape&  cercleVision,sf::Shape& cercleArme)
{

    sf::Shape* test;
     if ( e.estHumain == 1)
     {

        Humain* grr = (Humain*)(&e);
        if ( grr->a_arme != NULL )
        {
            cercleVision = makeCircle(e.position.x ,e.position.y,grr->a_arme->range,sf::Color::Green,1);
			cercleVision.setFillColor(sf::Color::Transparent);
            app.draw(cercleVision);
        }

      /*  cercleVision = sf::CircleShape (e.position.x ,e.position.y,  grr->rangeVision,sf::Color::Green,(float)1,sf::Color::Green )   ;
        cercleVision.EnableFill(false);
        cercleVision.EnableOutline(true);
        app.draw(cercleVision);*/
		 cercleVision = sf::CircleShape ();
			cercleVision.setPosition(e.position.x ,e.position.y);
			cercleVision.setRadius(grr->rangeVision);
			cercleVision.setOutlineColor(sf::Color::Green);
			cercleVision.setFillColor(sf::Color::Green )   ;
			cercleVision.setOutlineThickness((float)1);

        test = &cercle;
     }
    else
    {
          test = &cercle2;
         // cercleVision = sf::Shape::Circle (e.position.x ,e.position.y, 4,sf::Color::Green,(float)0.1,sf::Color::Green )   ;
		  cercleVision = sf::CircleShape ();
			cercleVision.setPosition(e.position.x ,e.position.y);
			cercleVision.setRadius(4);
			cercleVision.setOutlineColor(sf::Color::Green);
			cercleVision.setFillColor(sf::Color::Green )   ;
			cercleVision.setOutlineThickness((float)0.1);

         /* if ( e.pointDestination.size() > 0 )
          {

            cercle.SetX(e.pointDestination[0].x);
               cercle.SetY(e.pointDestination[0].y);
              app.Draw(cercle);
          }*/
    }





/*  test->SetX(e.position.x);
    test->SetY(e.position.y);*/
	test->setPosition(e.position.x,e.position.y);
 /*test->EnableFill(false);

// Active l'affichage de sa bordure
 test->EnableOutline(true);*/
    app.draw(*test);

    // la destination

    if (  e.estHumain == 0 && e.lookGood > 50 )
    {

        /*cercleArme .SetX(e.position.x);
        cercleArme .SetY(e.position.y );*/
	test->setPosition(e.position.x,e.position.y);

         app.draw(cercleArme);
    }

}




std::string getDossier(std::string cheminExe)
{
    int possition = cheminExe.find_last_of("/\\");
    std::string temp = cheminExe.substr(0,possition) +"/";
    return  temp;
}

Habitation*  creationHabitation (sf::Vector2f dimMax)
{

    int x,y,longeur,hauteur;

    do
    {

        longeur =  (rand() % (int)dimMax.x/2 ) +dimMax.x/2 ;
        hauteur =  (rand() % (int)dimMax.y/2 ) +dimMax.y/2 ;

        x =  rand() % abs( - (int)World::villeHG.x - longeur + (int)World::villeBD.x ) + World::villeHG.x ;
        y =  rand() % abs( - (int)World::villeHG.y - hauteur + (int)World::villeBD.y ) + World::villeHG.y;


    }
    while ( pointDansMaison(x         ,y        ) ||
            pointDansMaison(x+longeur ,y        ) ||
            pointDansMaison(x         ,y+hauteur) ||
            pointDansMaison(x+longeur ,y+hauteur) ||
            !maisonValide(x,y,longeur,hauteur) );





    Habitation* retour = new Habitation();
    retour->localisation = sf::Vector2f  (x,y);
    retour->dimention = sf::Vector2f  (longeur,hauteur);

    return retour;
}

void displayHabitation ( std::vector<Habitation*>& vec , sf::RectangleShape& form , sf::RenderWindow&  app)
{
    std::vector<Habitation*>::iterator it = vec.begin();
    for ( it ; it  != vec.end() ; it++ )
    { 
		form = makeRectangle( 	sf::Vector2f((*it)->localisation.x, (*it)->localisation.y) , 
								sf::Vector2f((*it)->localisation.x+(*it)->dimention.x,(*it)->localisation.y+(*it)->dimention.y ),
								sf::Color::Blue,
								5);
/*
        form  = sf::Shape::Rectangle(
                                     
                                     sf::Color::White,
                                     0,
                                     sf::Color::White);*/

   //form.EnableFill(false);
        app.draw(form);

       /* sf::Shape shapeHumain = sf::Shape::Circle((*it)->localisation.x ,(*it)->localisation.y ,2,sf::Color::Red);
        app.Draw(shapeHumain);
        shapeHumain = sf::Shape::Circle((*it)->localisation.x +(*it)->dimention.x,(*it)->localisation.y ,2,sf::Color::Red);
 app.Draw(shapeHumain);
        shapeHumain = sf::Shape::Circle((*it)->localisation.x ,(*it)->localisation.y+(*it)->dimention.y ,2,sf::Color::Red);
 app.Draw(shapeHumain);
        shapeHumain = sf::Shape::Circle((*it)->localisation.x +(*it)->dimention.x,(*it)->localisation.y+(*it)->dimention.y ,2,sf::Color::Red);
 app.Draw(shapeHumain);*/
    }
}
