#ifndef World_H
#define World_H
#include <vector>
#include <string>
#include <SFML/Window.hpp>
class Habitation;
class Etre;
class Zombie;
class World
{
    public:
        World();
        virtual ~World();

        static int maxX , maxY ;
        static sf::Vector2f villeHG, villeBD;
        static std::vector<Habitation *> vecBatiment;
        static std::vector<Etre *> vecEtre;
        static int munitionDisponible;
        static int nbFF;
        static int nbZombieKilled ;
        static int nbZombieKilledByHand;
        static  int nbHumainKilled ;
        static float ZombieSprint;
        static float VitesseHumain;
        static float dureeJournee;
        static int nbBureau ;
        static float dimMaxMaison ;
        static int nbFamille ;
        static int nbMembreMax ;
        static int tauxArme;
        static int nbZombie;
        // perte de confiance
        static float variationConfiance ;
        // augmentation du FF
        static float variationInquitudeFix ;
        static float variationInquitudePourCent ;
        static float  bordure;
        static float range;
        static float delais;
        static int munition;
        static float rangeVisionHumain;
        static float rangeVisionZombie;
        static float valeurAttaqueCacZombie;
        static float inquietudeMax ;
        static float bonneTeteMax;

        static float bonneTeteMaxZombie ;
        static float garderConfiance ;


        static float age ;
        static float delay ;
        static float tempsAvantMesure;
        static std::vector <std::string> fichier;
        static void  saveStat(std::string chemin, double temps);
        static void ChargeFile(std::string chemin);
        static std::string getDossier(std::string cheminExe);
        static bool debut;
    protected:
    private:
};

#endif // World_H
