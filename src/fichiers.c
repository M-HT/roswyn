


#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "constantes.h"
#include "fichiers.h"



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
                    tileSet = 1;
                    break;
                case '2':
                    tileSet = 2;
                    break;
                case '3':
                    tileSet = 3;
                    break;
                case '4':
                    tileSet = 4;
                    break;
                case '5':
                    tileSet = 5;
                    break;
                case '6':
                    tileSet = 6;
                    break;
                case '7':
                    tileSet = 7;
                    break;
                case '8':
                    tileSet = 8;
                    break;
                case '9':
                    tileSet = 9;
                    break;
                case 'A':
                    tileSet = 10;
                    break;
                case 'B':
                    tileSet = 11;
                    break;
                case 'C':
                    tileSet = 12;
                    break;
                case 'D':
                    tileSet = 13;
                    break;
                case 'E':
                    tileSet = 14;
                    break;
                case 'F':
                    tileSet = 15;
                    break;
                case 'G':
                    tileSet = 16;
                    break;
                case 'H':
                    tileSet = 17;
                    break;
                case 'I':
                    tileSet = 18;
                    break;
                case 'J':
                    tileSet = 19;
                    break;
                case 'K':
                    tileSet = 20;
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
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
                case '5':
                    niveau[j][i] = 5;
                    break;
                case '6':
                    niveau[j][i] = 6;
                    break;
                case '7':
                    niveau[j][i] = 7;
                    break;
                case '8':
                    niveau[j][i] = 8;
                    break;
                case '9':
                    niveau[j][i] = 9;
                    break;
                case 'A':
                    niveau[j][i] = 10;
                    break;
                case 'B':
                    niveau[j][i] = 11;
                    break;
                case 'C':
                    niveau[j][i] = 12;
                    break;
                case 'D':
                    niveau[j][i] = 13;
                    break;
                case 'E':
                    niveau[j][i] = 14;
                    break;
                case 'F':
                    niveau[j][i] = 15;
                    break;
                case 'G':
                    niveau[j][i] = 16;
                    break;
                case 'H':
                    niveau[j][i] = 17;
                    break;
                case 'I':
                    niveau[j][i] = 18;
                    break;
                case 'J':
                    niveau[j][i] = 19;
                    break;
                case 'K':
                    niveau[j][i] = 20;
                    break;
                case 'L':
                    niveau[j][i] = 21;
                    break;
                case 'M':
                    niveau[j][i] = 22;
                    break;
                case 'N':
                    niveau[j][i] = 23;
                    break;
                case 'O':
                    niveau[j][i] = 24;
                    break;
                case 'P':
                    niveau[j][i] = 25;
                    break;
                case 'Q':
                    niveau[j][i] = 26;
                    break;
                case 'R':
                    niveau[j][i] = 27;
                    break;
                case 'S':
                    niveau[j][i] = 28;
                    break;
                case 'T':
                    niveau[j][i] = 29;
                    break;
                case 'U':
                    niveau[j][i] = 30;
                    break;
                case 'V':
                    niveau[j][i] = 31;
                    break;
                case 'W':
                    niveau[j][i] = 32;
                    break;
                case 'X':
                    niveau[j][i] = 33;
                    break;
                case 'Y':
                    niveau[j][i] = 34;
                    break;
                case 'Z':
                    niveau[j][i] = 35;
                    break;
                case 'a':
                    niveau[j][i] = 36;
                    break;
                case 'b':
                    niveau[j][i] = 37;
                    break;
                case 'c':
                    niveau[j][i] = 38;
                    break;
                case 'd':
                    niveau[j][i] = 39;
                    break;
                case 'e':
                    niveau[j][i] = 40;
                    break;
                case 'f':
                    niveau[j][i] = 41;
                    break;
                case 'g':
                    niveau[j][i] = 42;
                    break;
                case 'h':
                    niveau[j][i] = 43;
                    break;
                case 'i':
                    niveau[j][i] = 44;
                    break;
                case 'j':
                    niveau[j][i] = 45;
                    break;
                case 'k':
                    niveau[j][i] = 46;
                    break;
                case 'l':
                    niveau[j][i] = 47;
                    break;
                case 'm':
                    niveau[j][i] = 48;
                    break;
                case 'n':
                    niveau[j][i] = 49;
                    break;
                case 'o':
                    niveau[j][i] = 50;
                    break;
                case 'p':
                    niveau[j][i] = 51;
                    break;
                case 'q':
                    niveau[j][i] = 52;
                    break;
                case 'r':
                    niveau[j][i] = 53;
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
    int i = 0, j = 0, caractereLu = 0;
    int a = 0, b = 0, c = 0;

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

for (j = 1 ; j < 5 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) warpHaut = (a * 100) + (b * 10) + c;
            if (j == 2) warpBas = (a * 100) + (b * 10) + c;
            if (j == 3) warpGauche = (a * 100) + (b * 10) + c;
            if (j == 4) warpDroite = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

    //On lit ensuite les infos sur ennemi1
    //Est-il vivant sur cette map ?
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       ennemi1vivant = 0;
                    break;
                case '1':
                       ennemi1vivant = 1;
                    break;
            }

    //Combien a-t-il de PV ???
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemi1life = 0;
                    break;
                case '1':
                      ennemi1life = 1;
                    break;
                case '2':
                       ennemi1life = 2;
                    break;
                case '3':
                       ennemi1life = 3;
                    break;
                case '4':
                       ennemi1life = 4;
                    break;
                case '5':
                       ennemi1life = 5;
                    break;
                case '6':
                       ennemi1life = 6;
                    break;
                case '7':
                       ennemi1life = 7;
                    break;
                case '8':
                       ennemi1life = 8;
                    break;
                case '9':
                       ennemi1life = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionEnnemi1.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionEnnemi1.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }


    //Idem pour ennemi2
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       ennemi2vivant = 0;
                    break;
                case '1':
                       ennemi2vivant = 1;
                    break;
            }

    //Combien a-t-il de PV ???
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemi2life = 0;
                    break;
                case '1':
                      ennemi2life = 1;
                    break;
                case '2':
                       ennemi2life = 2;
                    break;
                case '3':
                       ennemi2life = 3;
                    break;
                case '4':
                       ennemi2life = 4;
                    break;
                case '5':
                       ennemi2life = 5;
                    break;
                case '6':
                       ennemi2life = 6;
                    break;
                case '7':
                       ennemi2life = 7;
                    break;
                case '8':
                       ennemi2life = 8;
                    break;
                case '9':
                       ennemi2life = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionEnnemi2.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionEnnemi2.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

      //Idem pour ennemi3
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       ennemi3vivant = 0;
                    break;
                case '1':
                       ennemi3vivant = 1;
                    break;
            }

    //Combien a-t-il de PV ???
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemi3life = 0;
                    break;
                case '1':
                      ennemi3life = 1;
                    break;
                case '2':
                       ennemi3life = 2;
                    break;
                case '3':
                       ennemi3life = 3;
                    break;
                case '4':
                       ennemi3life = 4;
                    break;
                case '5':
                       ennemi3life = 5;
                    break;
                case '6':
                       ennemi3life = 6;
                    break;
                case '7':
                       ennemi3life = 7;
                    break;
                case '8':
                       ennemi3life = 8;
                    break;
                case '9':
                       ennemi3life = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionEnnemi3.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionEnnemi3.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

      //Idem pour ennemi4
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       ennemi4vivant = 0;
                    break;
                case '1':
                       ennemi4vivant = 1;
                    break;
            }

    //Combien a-t-il de PV ???
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemi4life = 0;
                    break;
                case '1':
                      ennemi4life = 1;
                    break;
                case '2':
                       ennemi4life = 2;
                    break;
                case '3':
                       ennemi4life = 3;
                    break;
                case '4':
                       ennemi4life = 4;
                    break;
                case '5':
                       ennemi4life = 5;
                    break;
                case '6':
                       ennemi4life = 6;
                    break;
                case '7':
                       ennemi4life = 7;
                    break;
                case '8':
                       ennemi4life = 8;
                    break;
                case '9':
                       ennemi4life = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionEnnemi4.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionEnnemi4.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

      //Idem pour ennemi5
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       ennemi5vivant = 0;
                    break;
                case '1':
                       ennemi5vivant = 1;
                    break;
            }

    //Combien a-t-il de PV ???
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemi5life = 0;
                    break;
                case '1':
                      ennemi5life = 1;
                    break;
                case '2':
                       ennemi5life = 2;
                    break;
                case '3':
                       ennemi5life = 3;
                    break;
                case '4':
                       ennemi5life = 4;
                    break;
                case '5':
                       ennemi5life = 5;
                    break;
                case '6':
                       ennemi5life = 6;
                    break;
                case '7':
                       ennemi5life = 7;
                    break;
                case '8':
                       ennemi5life = 8;
                    break;
                case '9':
                       ennemi5life = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionEnnemi5.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionEnnemi5.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

       //PNJ 1
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       pnj1vivant = 0;
                    break;
                case '1':
                       pnj1vivant = 1;
                    break;
            }

    //Que fait-il (0 = rien)
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      pnj1action = 0;
                    break;
                case '1':
                      pnj1action = 1;
                    break;
                case '2':
                       pnj1action = 2;
                    break;
                case '3':
                       pnj1action = 3;
                    break;
                case '4':
                       pnj1action = 4;
                    break;
                case '5':
                       pnj1action = 5;
                    break;
                case '6':
                       pnj1action = 6;
                    break;
                case '7':
                       pnj1action = 7;
                    break;
                case '8':
                       pnj1action = 8;
                    break;
                case '9':
                       pnj1action = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionPnj1.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionPnj1.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }


      //PNJ 2
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       pnj2vivant = 0;
                    break;
                case '1':
                       pnj2vivant = 1;
                    break;
            }

    //Que fait-il (0 = rien)
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      pnj2action = 0;
                    break;
                case '1':
                      pnj2action = 1;
                    break;
                case '2':
                       pnj2action = 2;
                    break;
                case '3':
                       pnj2action = 3;
                    break;
                case '4':
                       pnj2action = 4;
                    break;
                case '5':
                       pnj2action = 5;
                    break;
                case '6':
                       pnj2action = 6;
                    break;
                case '7':
                       pnj2action = 7;
                    break;
                case '8':
                       pnj2action = 8;
                    break;
                case '9':
                       pnj2action = 9;
                    break;
                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionPnj2.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionPnj2.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

            //Boss
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       bossvivant = 0;
                    break;
                case '1':
                       bossvivant = 1;
                    break;
            }

    //PV
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      bosslife = 0;
                    break;
                case '1':
                      bosslife = 1;
                    break;
                case '2':
                       bosslife = 2;
                    break;
                case '3':
                       bosslife = 3;
                    break;
                case '4':
                       bosslife = 4;
                    break;
                case '5':
                       bosslife = 5;
                    break;
                case '6':
                       bosslife = 6;
                    break;
                case '7':
                       bosslife = 7;
                    break;
                case '8':
                       bosslife = 8;
                    break;
                case '9':
                       bosslife = 9;
                    break;
                           }

        //Que fait-il (numero du boss)
        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '1':
                      bossaction = 1;
                    break;
                case '2':
                       bossaction = 2;
                    break;
                case '3':
                       bossaction = 3;
                    break;
                case '4':
                       bossaction = 4;
                    break;
                case '5':
                       bossaction = 5;
                    break;
                case '6':
                       bossaction = 6;
                    break;
                case '7':
                       bossaction = 7;
                    break;
                case '8':
                       bossaction = 8;
                    break;
                case '9':
                       bossaction = 9;
                    break;

                           }

        //Ou est-il situe ??? (mm technique que precedemment)
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionBoss.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionBoss.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }


  //**************Gestion items laisses*************

        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      itemLaisse = 0;
                    break;
                case '1':
                      itemLaisse = 1;
                    break;
                case '2':
                       itemLaisse = 2;
                    break;
                case '3':
                       itemLaisse = 3;
                    break;

                           }

 //**************Gestion musique*************

        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      musique = 0;
                    break;
                case '1':
                      musique = 1;
                    break;
                case '2':
                       musique = 2;
                    break;
                case '3':
                       musique = 3;
                    break;
                case '4':
                       musique = 4;
                    break;
                case '5':
                       musique = 5;
                    break;
                case '6':
                       musique = 6;
                    break;
                case '7':
                       musique = 7;
                    break;
                case '8':
                       musique = 8;
                    break;
                case '9':
                       musique = 9;
                    break;
                           }


 //**************Gestion type d'ennemis affichés*************

        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      ennemiType = 0;
                    break;
                case '1':
                      ennemiType = 1;
                    break;
                case '2':
                       ennemiType = 2;
                    break;
                case '3':
                       ennemiType = 3;
                    break;
                case '4':
                       ennemiType = 4;
                    break;
                case '5':
                       ennemiType = 5;
                    break;
                case '6':
                       ennemiType = 6;
                    break;
                case '7':
                       ennemiType = 7;
                    break;
                case '8':
                       ennemiType = 8;
                    break;
                case '9':
                       ennemiType = 9;
                    break;
                           }


//***********************Gestion fireballs****************


        caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      nbfireballs = 0;
                    break;
                case '1':
                      nbfireballs = 1;
                    break;
                case '2':
                       nbfireballs = 2;
                    break;
                case '3':
                       nbfireballs = 3;
                    break;
                case '4':
                       nbfireballs = 4;
                    break;
                case '5':
                       nbfireballs = 5;
                    break;
                case '6':
                       nbfireballs = 6;
                    break;
                case '7':
                       nbfireballs = 7;
                    break;
                case '8':
                       nbfireballs = 8;
                    break;
                case '9':
                       nbfireballs = 9;
                    break;
                           }

        //Ou sont-elles situees ?
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionFireball1.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionFireball1.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }

    //gestion weather
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       weather = 0;
                    break;
                case '1':
                       weather = 1;
                    break;
                case '2':
                       weather = 2;
                    break;
            }

       //Gestion warpZone
    caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       warpZone = 0;
                    break;
                case '1':
                       warpZone = 1;
                    break;
            }


  //Valeur de wlevel
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            wlevel = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;



        //Ou est-elle situee ?
for (j = 1 ; j < 3 ; j++) {
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            if (j == 1) positionWarp.x = (a * 100) + (b * 10) + c;
            if (j == 2) positionWarp.y = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;
                }


    //Valeur de dialogue1
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            dialogue1 = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

 //Valeur de dialogue2
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            dialogue2 = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

 //Valeur de dialogue3
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            dialogue3 = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;


  //Valeur de lswitch
    for (i = 1 ; i < 4 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;
                       if (i == 3) c = 0;
                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;
                       if (i == 3) c = 1;
                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;
                       if (i == 3) c = 2;
                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;
                       if (i == 3) c = 3;
                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;
                       if (i == 3) c = 4;
                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;
                       if (i == 3) c = 5;
                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;
                       if (i == 3) c = 6;
                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;
                       if (i == 3) c = 7;
                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;
                       if (i == 3) c = 8;
                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;
                       if (i == 3) c = 9;
                    break;
                           } }
            lswitch = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

    //Valeur de coffre

       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      coffre = 0;
                    break;
                case '1':
                      coffre = 1;
                    break;
                case '2':
                       coffre = 2;
                    break;
                case '3':
                       coffre = 3;
                    break;
                case '4':
                       coffre = 4;
                    break;
                case '5':
                       coffre = 5;
                    break;
                case '6':
                       coffre = 6;
                    break;

                           }


    fclose(fichier);

    item1.itemExiste = 0;

    return 1;

    }



int InitCoffres ( )
 {

    FILE* fichier = NULL;
    int i = 0;

    fichier = fopen("coffres.lvl", "r+");
    if (fichier == NULL)
        return 0;

     //On ecrit 999 * 1 pour activer chaque coffre de chaque level

    for ( i = 0 ; i <= 999 ; i++ )
    { fprintf(fichier, "1"); }

    fclose(fichier);

return 0;

    }


int InitSwitchs ( )
 {

    FILE* fichier = NULL;
    int i = 0;

    fichier = fopen("switchs.lvl", "r+");
    if (fichier == NULL)
        return 0;

     //On ecrit 999 * 1 pour activer chaque coffre de chaque level

    for ( i = 0 ; i <= 999 ; i++ )
    { fprintf(fichier, "1"); }

    fclose(fichier);

return 0;

    }


int ValeurCoffre( int niveau )
{

    FILE* fichier = NULL;
    int caractereLu = 0;

    fichier = fopen("coffres.lvl", "r");
    if (fichier == NULL)
        return 0;

    //Puis on recherche le coffre correspondant au level
    while (niveau > 0)
    {
    caractereLu = fgetc(fichier);
    niveau--;
    }

    fseek(fichier, 0, SEEK_CUR);
    caractereLu = fgetc(fichier);
    if ( caractereLu == '0' ) { fclose(fichier); return 0; }
    else { fclose(fichier); return 1; }

}



int OuvreCoffre( int niveau )
{

    FILE* fichier = NULL;
    int caractereLu = 0;

    fichier = fopen("coffres.lvl", "r+");
    if (fichier == NULL)
        return 0;

    //Puis on recherche le coffre correspondant au level
    while (niveau > 0)
    {
    caractereLu = fgetc(fichier);
    niveau--;
    }

     fseek(fichier, 0, SEEK_CUR);
     fprintf(fichier, "0");


    fclose(fichier);
    return 1;

}


int ValeurSwitch ( int level )
{

    FILE* fichier = NULL;
    int caractereLu = 0;

    fichier = fopen("switchs.lvl", "r");
    if (fichier == NULL)
        return 0;

    //Puis on recherche le switch correspondant au level : lswitch
    while (level > 0)
    {
    caractereLu = fgetc(fichier);
    level--;
    }

    fseek(fichier, 0, SEEK_CUR);
    caractereLu = fgetc(fichier);
    if ( caractereLu == '0' ) { fclose(fichier); return 0; }
    else { fclose(fichier); return 1; }

}



int OuvreSwitch ( )
{

    FILE* fichier = NULL;
    int caractereLu = 0;

    fichier = fopen("switchs.lvl", "r+");
    if (fichier == NULL)
        return 0;

    //Puis on recherche le coffre correspondant au level
    while (lswitch > 0)
    {
    caractereLu = fgetc(fichier);
    lswitch--;
    }

     fseek(fichier, 0, SEEK_CUR);
     fprintf(fichier, "0");


    fclose(fichier);
    return 1;

}




