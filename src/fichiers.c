


#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "fichiers.h"
#include "jeu.h"



  //Variables globales
  // Rappel declaration variables globales
  extern int ennemi1vivant, ennemi1life;
  extern SDL_Rect positionEnnemi1;
  extern int ennemi2vivant, ennemi2life;
  extern SDL_Rect positionEnnemi2;
  extern int ennemi3vivant, ennemi3life;
  extern SDL_Rect positionEnnemi3;
  extern int ennemi4vivant, ennemi4life;
  extern SDL_Rect positionEnnemi4;
  extern int ennemi5vivant, ennemi5life;
  extern SDL_Rect positionEnnemi5;
  extern int pnj1vivant, pnj1action;
  extern SDL_Rect positionPnj1;
  extern int pnj2vivant, pnj2action;
  extern SDL_Rect positionPnj2;
  extern int bossvivant, bossaction, bosslife;
  extern SDL_Rect positionBoss;
  extern int nbfireballs;
  extern int initFball;
  extern SDL_Rect positionFireball1;
  extern SDL_Rect positionFireball2;
  extern SDL_Rect positionFireball3;
  extern SDL_Rect positionFireball4;
  extern int warpHaut, warpBas, warpDroite, warpGauche;
  extern int tileSet;
  extern int itemLaisse;
  extern int musique, musiquedavant;
  extern int ennemiType;
  extern int weather;
  extern int warpZone;
  extern int wlevel;
  extern SDL_Rect positionWarp;
  extern Item item1;
  extern SDL_Rect positionMario;
  extern int dialogue1;
  extern int dialogue2;
  extern int dialogue3;
  extern int lswitch;
  extern int coffre;
  extern SDL_Rect PositionBaton;
  extern int tilesetPrecedent;

   //Gestion du player
    extern SDL_Rect positionMario;
    extern int power; //Puissance de l'epee
    extern int boss;


static int coffreSize, switchSize;
static char *coffreData, *switchData;

int readNumber(FILE *fichier, int length)
{
    int i, caractereLu, result;

    result = 0;
    for (i = 0; i < length; i++)
    {
        if (i != 0) result *= 10;
        caractereLu = fgetc(fichier);
        switch (caractereLu)
        {
            case '0':
                result += 0;
                break;
            case '1':
                result += 1;
                break;
            case '2':
                result += 2;
                break;
            case '3':
                result += 3;
                break;
            case '4':
                result += 4;
                break;
            case '5':
                result += 5;
                break;
            case '6':
                result += 6;
                break;
            case '7':
                result += 7;
                break;
            case '8':
                result += 8;
                break;
            case '9':
                result += 9;
                break;
        }
    }

    return result;
}

int readSmallInteger(FILE *fichier, int maxvalue)
{
    int caractereLu, result;

    result = 0;
    caractereLu = fgetc(fichier);
    switch (caractereLu)
    {
        case '0':
            if (maxvalue >= 0) result = 0;
            break;
        case '1':
            if (maxvalue >= 1) result = 1;
            break;
        case '2':
            if (maxvalue >= 2) result = 2;
            break;
        case '3':
            if (maxvalue >= 3) result = 3;
            break;
        case '4':
            if (maxvalue >= 4) result = 4;
            break;
        case '5':
            if (maxvalue >= 5) result = 5;
            break;
        case '6':
            if (maxvalue >= 6) result = 6;
            break;
        case '7':
            if (maxvalue >= 7) result = 7;
            break;
        case '8':
            if (maxvalue >= 8) result = 8;
            break;
        case '9':
            if (maxvalue >= 9) result = 9;
            break;
    }

    return result;
}


int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int level)
{
    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    int i = 0, j = 0, caractereLu = 0;

    fichier = fopen("niveaux.lvl", "r");
    if (fichier == NULL)
        return 0;


    //Puis on recherche le numero de la ligne de level
    while (level > 0)
    {
    caractereLu = fgetc(fichier);
    if (caractereLu == '\n')
        level--;
    }

    //Le premier caractere code le tileset

    caractereLu = fgetc(fichier);
     switch (caractereLu)
            {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    tileSet = 1 + caractereLu - '1';
                    break;
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                    tileSet = 10 + caractereLu - 'A';
                    break;
            }


    //Lecture des tiles de la carte

    fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    niveau[j][i] = ligneFichier[(i * NB_BLOCS_LARGEUR) + j] - '0';
                    break;
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                case 'G':
                case 'H':
                case 'I':
                case 'J':
                case 'K':
                case 'L':
                case 'M':
                case 'N':
                case 'O':
                case 'P':
                case 'Q':
                case 'R':
                case 'S':
                case 'T':
                case 'U':
                case 'V':
                case 'W':
                case 'X':
                case 'Y':
                case 'Z':
                    niveau[j][i] = 10 + ligneFichier[(i * NB_BLOCS_LARGEUR) + j] - 'A';
                    break;
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                case 'g':
                case 'h':
                case 'i':
                case 'j':
                case 'k':
                case 'l':
                case 'm':
                case 'n':
                case 'o':
                case 'p':
                case 'q':
                case 'r':
                    niveau[j][i] = 36 + ligneFichier[(i * NB_BLOCS_LARGEUR) + j] - 'a';
                    break;
            }
        }
    }

    fclose(fichier);

    if ( tileSet != tilesetPrecedent )
    {
        tilesetPrecedent = tileSet;
        freeTileset();
        loadTileset();
    }

    return 1;
}







int chargerDataNiveau(int level)
{
    musiquedavant = musique;
    initFball = 1;

    FILE* fichier = NULL;
    int caractereLu = 0;

    warpHaut = 0;
    warpBas = 0;
    warpGauche = 0;
    warpDroite = 0;
    ennemi1life = 0;
    ennemi1vivant = 0;

    fichier = fopen("data.lvl", "r");
    if (fichier == NULL)
        return 0;

    //Puis on recherche le numero de la ligne de level
    while (level > 0)
    {
    caractereLu = fgetc(fichier);
    if (caractereLu == '\n')
        level--;
    }

    warpHaut = readNumber(fichier, 3);
    warpBas = readNumber(fichier, 3);
    warpGauche = readNumber(fichier, 3);
    warpDroite = readNumber(fichier, 3);

    //On lit ensuite les infos sur ennemi1
    //Est-il vivant sur cette map ?
    ennemi1vivant = readSmallInteger(fichier, 1);

    //Combien a-t-il de PV ???
    ennemi1life = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionEnnemi1.x = readNumber(fichier, 3);
    positionEnnemi1.y = readNumber(fichier, 3);


    //Idem pour ennemi2
    ennemi2vivant = readSmallInteger(fichier, 1);

    //Combien a-t-il de PV ???
    ennemi2life = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionEnnemi2.x = readNumber(fichier, 3);
    positionEnnemi2.y = readNumber(fichier, 3);

      //Idem pour ennemi3
    ennemi3vivant = readSmallInteger(fichier, 1);

    //Combien a-t-il de PV ???
    ennemi3life = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionEnnemi3.x = readNumber(fichier, 3);
    positionEnnemi3.y = readNumber(fichier, 3);

      //Idem pour ennemi4
    ennemi4vivant = readSmallInteger(fichier, 1);

    //Combien a-t-il de PV ???
    ennemi4life = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionEnnemi4.x = readNumber(fichier, 3);
    positionEnnemi4.y = readNumber(fichier, 3);

      //Idem pour ennemi5
    ennemi5vivant = readSmallInteger(fichier, 1);

    //Combien a-t-il de PV ???
    ennemi5life = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionEnnemi5.x = readNumber(fichier, 3);
    positionEnnemi5.y = readNumber(fichier, 3);

       //PNJ 1
    pnj1vivant = readSmallInteger(fichier, 1);

    //Que fait-il (0 = rien)
    pnj1action = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionPnj1.x = readNumber(fichier, 3);
    positionPnj1.y = readNumber(fichier, 3);


      //PNJ 2
    pnj2vivant = readSmallInteger(fichier, 1);

    //Que fait-il (0 = rien)
    pnj2action = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionPnj2.x = readNumber(fichier, 3);
    positionPnj2.y = readNumber(fichier, 3);

            //Boss
    bossvivant = readSmallInteger(fichier, 1);

    //PV
    bosslife = readNumber(fichier, 1);

    //Que fait-il (numero du boss)
    bossaction = readNumber(fichier, 1);

    //Ou est-il situe ??? (mm technique que precedemment)
    positionBoss.x = readNumber(fichier, 3);
    positionBoss.y = readNumber(fichier, 3);


  //**************Gestion items laisses*************

    itemLaisse = readSmallInteger(fichier, 3);

 //**************Gestion musique*************

    musique = readNumber(fichier, 1);


 //**************Gestion type d'ennemis affichés*************

    ennemiType = readNumber(fichier, 1);


//***********************Gestion fireballs****************


    nbfireballs = readNumber(fichier, 1);

    //Ou sont-elles situees ?
    positionFireball1.x = readNumber(fichier, 3);
    positionFireball1.y = readNumber(fichier, 3);

    //gestion weather
    weather = readSmallInteger(fichier, 2);

       //Gestion warpZone
    warpZone = readSmallInteger(fichier, 1);


  //Valeur de wlevel
    wlevel = readNumber(fichier, 3);



    //Ou est-elle situee ?
    positionWarp.x = readNumber(fichier, 3);
    positionWarp.y = readNumber(fichier, 3);


    //Valeur de dialogue1
    dialogue1 = readNumber(fichier, 3);

 //Valeur de dialogue2
    dialogue2 = readNumber(fichier, 3);

 //Valeur de dialogue3
    dialogue3 = readNumber(fichier, 3);


  //Valeur de lswitch
    lswitch = readNumber(fichier, 3);

    //Valeur de coffre

    coffre = readSmallInteger(fichier, 6);


    fclose(fichier);

    item1.itemExiste = 0;

    return 1;

    }



int readCoffres(FILE *fichier)
{
    return (fread(coffreData, 1, coffreSize, fichier) == coffreSize)?1:0;
}

int writeCoffres(FILE *fichier)
{
    return (fwrite(coffreData, 1, coffreSize, fichier) == coffreSize)?1:0;
}

int readSwitchs(FILE *fichier)
{
    return (fread(switchData, 1, switchSize, fichier) == switchSize)?1:0;
}

int writeSwitchs(FILE *fichier)
{
    return (fwrite(switchData, 1, switchSize, fichier) == switchSize)?1:0;
}

int InitCoffres ( )
{

    FILE* fichier;
    int i;

    fichier = fopen("coffres.lvl", "r");
    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END);
        coffreSize = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);
        if (coffreSize < 1024) coffreSize = 1024;
    }
    else
    {
        coffreSize = 1024;
    }

    coffreData = (char *) malloc(coffreSize);
    if (coffreData == NULL)
    {
        if (fichier != NULL) fclose(fichier);
        return 0;
    }

    if (fichier != NULL)
    {
        readCoffres(fichier);
    }

     //On ecrit 999 * 1 pour activer chaque coffre de chaque level

    for ( i = 0 ; i <= 999 ; i++ )
    { coffreData[i] = '1'; }

    return 1;
}


int InitSwitchs ( )
{

    FILE* fichier;
    int i;

    fichier = fopen("switchs.lvl", "r");
    if (fichier != NULL)
    {
        fseek(fichier, 0, SEEK_END);
        switchSize = ftell(fichier);
        fseek(fichier, 0, SEEK_SET);
        if (switchSize < 1024) switchSize = 1024;
    }
    else
    {
        switchSize = 1024;
    }

    switchData = (char *) malloc(switchSize);
    if (switchData == NULL)
    {
        if (fichier != NULL) fclose(fichier);
        return 0;
    }

    if (fichier != NULL)
    {
        readSwitchs(fichier);

        fclose(fichier);
    }

     //On ecrit 999 * 1 pour activer chaque coffre de chaque level

    for ( i = 0 ; i <= 999 ; i++ )
    { switchData[i] = '1'; }

    return 1;
}


int ValeurCoffre( int niveau )
{
    return (coffreData[niveau] == '0')?0:1;
}



int OuvreCoffre( int niveau )
{
    coffreData[niveau] = '0';

    return 1;
}


int ValeurSwitch ( int level )
{
    return (switchData[level] == '0')?0:1;
}



int OuvreSwitch ( )
{
    switchData[lswitch] = '0';
    // bug ???
    lswitch = 0;

    return 1;
}




