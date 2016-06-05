#include "Word.hpp"
#include "Habitation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>
#include <vector>
#include "Etre.hpp"
#include "Humain.hpp"
std::vector<Habitation *>World::vecBatiment;
std::vector<Etre *> World::vecEtre;



int World::maxX = 800;
int World::maxY = 800 ;
float World::ZombieSprint = 1.25;
float World::VitesseHumain = 200;
float World::dureeJournee = 10;
int World::nbBureau = 10;
float World::dimMaxMaison = 60;
int World::nbFamille = 4;
int World::nbMembreMax = 4;
int World::tauxArme = 00;
int World:: nbZombie = 5;
// perte de confiance
float World::variationConfiance = 0.8;
// augmentation du FF
float World::variationInquitudeFix = 2;
float World::variationInquitudePourCent = 1.3;
float World::bordure = 0.15;
int World::munition = 6;
float World::range = 20;
float World::delais = 0.2;

float World::rangeVisionHumain = 30;
float World::rangeVisionZombie = 50;
float World::valeurAttaqueCacZombie = 4;

float World::inquietudeMax = 50;
float World::bonneTeteMax = 70;

float World::bonneTeteMaxZombie = 60;
float World::garderConfiance = 0;

int World::munitionDisponible = 0;
int World::nbFF = 0;
int World::nbZombieKilled = 0;
int World::nbZombieKilledByHand = 0;
int World::nbHumainKilled = 0;
sf::Vector2f  World::villeHG(World::maxX*World::bordure,World::maxY*World::bordure);
sf::Vector2f  World::villeBD(World::maxX*(1-World::bordure),World::maxY*(1-World::bordure));

float World::age = 0;
float World::delay = 1;
float World::tempsAvantMesure=0;
bool World::debut = true;
std::vector <std::string> World::fichier;
void World::saveStat(std::string chemin, double temps)
{


    // concaténation
    std::stringstream s1,s2,s3,s4,s5,s6,s7,s8;
    s1 << chemin << "/Imax/" << rand() << ".csv";
    s3 << chemin << "/Imed/" << rand() << ".csv";
    s2 << chemin << "/Imin/" << rand() << ".csv";
    s4 << chemin << "/Munition/" << rand() << ".csv";
    s5 << chemin << "/nbFF/" << rand() << ".csv";
    s6 << chemin << "/nbHKilled/" << rand() << ".csv";
    s7 << chemin << "/nbZkilled/" << rand() << ".csv";
    s8 << chemin << "/nbZkilledHand/" << rand() << ".csv";


     if ( debut )
    {
        debut = false;
        fichier.push_back(s1.str().c_str());
        fichier.push_back(s2.str().c_str());
        fichier.push_back(s3.str().c_str());
        fichier.push_back(s4.str().c_str());
        fichier.push_back(s5.str().c_str());
        fichier.push_back(s6.str().c_str());
        fichier.push_back(s7.str().c_str());
        fichier.push_back(s8.str().c_str());

    }
    // ouverteur ou créeation
    std::ofstream myfile[8];
    for ( int i= 0 ; i < 8 ; i++)
    {

        myfile[i].open (fichier[i] ,std::ios_base::out | std::ios_base::app );
    }



    tempsAvantMesure -= temps;
    age += temps;

    float Imax = -1;
    float Imin = 10000000;
    float Imoyenne = 0;
    float nbHumain = 0;
    for ( Etre* e : vecEtre)
    {
        if ( e->estHumain == 1 )
        {
            Humain* E = (Humain*) e;
            if ( Imin > E->inquietude )
            {
                Imin = E->inquietude;
            }
            if ( Imax < E->inquietude )
            {
                Imax = E->inquietude;
            }
            Imoyenne += E->inquietude;
            nbHumain++;
        }
    }
    if ( nbHumain == 0)
    {
        Imax = Imin =Imoyenne =0;
    }
    if ( tempsAvantMesure <= 0 )
    {

			std::cout << "____" << age << "____" <<std::endl;


             myfile[0] <<Imax << std::endl;
             myfile[1] <<Imoyenne/nbHumain << std::endl;
             myfile[2] <<Imin << std::endl;
             myfile[3] <<munitionDisponible << std::endl;
             myfile[4] <<nbFF << std::endl;
             myfile[5] <<nbHumainKilled << std::endl;
             myfile[6] <<nbZombieKilled << std::endl;
             myfile[7] <<nbZombieKilledByHand << std::endl;





        tempsAvantMesure = delay;
    }




  for ( int i= 0; i < 8 ; i++)
        myfile[i].close();


    // fermeture

}

void World::ChargeFile(std::string chemin)
{


    std::stringstream myString;
    std::string fileName = "param.txt";
    myString << chemin << fileName ;
    // ouverture
    std::ifstream myfile;
    myfile.open (myString.str().c_str());
    // concaténation
    std::cout << "chemin :" << myString.str() << std::endl;


    //lectrure du fichier
    std::string ligne;
    int i = 0;
    while ( myfile.good())
    {

        std::getline(myfile,ligne);
        std::string mot = ligne.substr (0,ligne.find("#"));
        switch (i)
        {
            case 1 :  maxX  = atof(mot.c_str())          ; break;
            case 2 :  maxY  = atof(mot.c_str())          ; break;
            case 3 :  ZombieSprint  = atof(mot.c_str())          ; break;
            case 4 :  VitesseHumain  = atof(mot.c_str())          ; break;
            case 5 :  dureeJournee  = atof(mot.c_str())          ; break;
            case 6 :  nbBureau  = atof(mot.c_str())          ; break;
            case 7 :  dimMaxMaison  = atof(mot.c_str())          ; break;
            case 8 :  nbFamille  = atof(mot.c_str())          ; break;
            case 9 :  nbMembreMax  = atof(mot.c_str())          ; break;
            case 10:  tauxArme  = atof(mot.c_str())          ; break;
            case 11:  nbZombie  = atof(mot.c_str())          ; break;
            case 12:  variationConfiance  = atof(mot.c_str())          ; break;
            case 13:  variationInquitudeFix  = atof(mot.c_str())          ; break;
            case 14:  variationInquitudePourCent  = atof(mot.c_str())          ; break;
            case 15:  bordure  = atof(mot.c_str())          ; break;
            case 16:  munition  = atof(mot.c_str())          ; break;
            case 17:  range  = atof(mot.c_str())          ; break;
            case 18:  delais  = atof(mot.c_str())          ; break;
            case 19:  rangeVisionHumain  = atof(mot.c_str())          ; break;
            case 20:  rangeVisionZombie  = atof(mot.c_str())          ; break;
            case 21:  valeurAttaqueCacZombie  = atof(mot.c_str())          ; break;
            case 22:  inquietudeMax  = atof(mot.c_str())          ; break;
            case 23:  bonneTeteMax  = atof(mot.c_str())          ; break;
            case 24:  bonneTeteMaxZombie  = atof(mot.c_str())          ; break;
            case 25:  garderConfiance  = atof(mot.c_str())          ; break;




        }
        i++;
        if ( nbBureau == 0 ) nbBureau++;
    }

    // fermeture
    myfile.close();
}

std::string World::getDossier(std::string cheminExe)
{
    int possition = cheminExe.find_last_of("/\\");
    return  cheminExe.substr(0,possition) +"/";
}

World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}
