
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
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
  extern int dialogue1;
  extern int dialogue2;
  extern int dialogue3;
  extern int lswitch;
  extern int coffre;
  extern SDL_Rect PositionBaton;


  //Gestion du player
    extern SDL_Rect positionMario;
    extern int power; //Puissance de l'epee
    extern int boss;
    extern Input input;



  //Variables globales specifiques à jeu.c
    int tempsTiles = 0;
    int animTiles = 1; //Pour l'animation des tiles


  //Nouveaux tableaux de tiles pour la gestion des niveaux
    extern SDL_Surface *mapImages[], *mapImages2[];

    extern int tilesetPrecedent;
    extern SDL_Joystick *joystick;
    extern TTF_Font *police;
    extern SDL_Surface *ecran;

    extern Mix_Music *musiqueJouee;

    extern int orig_width, orig_height;

    extern void ClearKeys(void);

#if defined(GP2X)
    extern void Change_HW_Audio_Volume (int amount);
#endif

#if !defined(MAX_PATH)
    #if defined(_POSIX_PATH_MAX)
        #define MAX_PATH _POSIX_PATH_MAX
    #else
        #define MAX_PATH 256
    #endif
#endif

void FlipScreen(void)
{
    SDL_Flip(ecran);
}

void ClearScreen(void)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Flip(ecran);
}

void BlitSprite(SDL_Surface *src, SDL_Surface *dst, SDL_Rect *dstrect)
{
    SDL_Rect position2;

    position2.x = POSITION_HORIZONTAL(dstrect->x);
    position2.y = POSITION_VERTICAL(dstrect->y);

    SDL_BlitSurface(src, NULL, dst, &position2);
}


   int AfficheNiveau(SDL_Rect position, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int level )

    {
    //Variables de decor
    int i = 0, j = 0;

    SDL_Surface **mapImagesX;

    //Pour animer les tiles
        if (tempsTiles + 500 < SDL_GetTicks()) {
                tempsTiles = SDL_GetTicks();
                if (animTiles == 1) animTiles = 2;
                else if (animTiles == 2) animTiles = 1;
                }

    mapImagesX = (animTiles == 1)?mapImages:mapImages2;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = (i * TILE_WIDTH) + TILE_START_X;
                position.y = (j * TILE_HEIGHT) + TILE_START_Y;

                switch(carte[i][j])
                {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                    case 23:
                    case 24:
                    case 25:
                    case 26:
                    case 27:
                    case 28:
                    case 29:
                    case 30:
                    case 31:
                    case 32:
                    case 33:
                    case 34:
                    case 35:
                    case 36:
                    case 37:
                    case 38:
                    case 39:
                    case 40:
                    case 41:
                    case 42:
                    case 43:
                    case 44:
                    case 45:
                    case 47:
                    case 48:
                    case 49:
                    case 50:
                    case 51:
                    case 52:
                    case 53:
                        SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 6:
                    case 7:
                    case 8:
                    case 9:
                    case 10:
                        if ( tileSet == 8) {
                            if ( boss >= (carte[i][j] - 5) ) { SDL_BlitSurface(mapImagesX[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 11:
                    case 12:
                    case 13:
                        if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImagesX[carte[i][j] + 13], NULL, ecran, &position);
                            carte[i][j] = (carte[i][j] + 14); }
                            else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= (carte[i][j] - 5) ) { SDL_BlitSurface(mapImagesX[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 14:
                    case 15:
                    case 16:
                    case 17:
                    case 18:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImagesX[carte[i][j] + 13], NULL, ecran, &position);
                            carte[i][j] = (carte[i][j] + 14); }
                            else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 46:
                        if ( ValeurCoffre( level ) == 1 ) SDL_BlitSurface(mapImagesX[carte[i][j]-1], NULL, ecran, &position);
                        else SDL_BlitSurface(mapImagesX[carte[i][j]], NULL, ecran, &position);
                        break;

                }
            }
        }


    return 0;

    }




int DeplacePlayer ( int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] )
{
switch(deplacement)
                        {
                        case HAUT:
                            if (positionMario.y <= 1) break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] >= 46)  break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] >= 46)  break;
                            positionMario.y -= x; break;

                        case BAS:
                            if (positionMario.y >= orig_height - 80) break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionMario.y += x; break;


                        case DROITE:
                            if (positionMario.x >= orig_width - 40) break;
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] >= 46) break;
                            positionMario.x += x; break;


                        case GAUCHE:
                            if (positionMario.x <= 1) break;
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] >= 46) break;
                            positionMario.x -= x;  break;

                        }
  return 0;
  }



int DeplaceEnnemi ( int ennemi, int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] )
{
    SDL_Rect positionEnnemi = {0,0,0,0};

    if (ennemi == 1) positionEnnemi = positionEnnemi1;
    if (ennemi == 2) positionEnnemi = positionEnnemi2;
    if (ennemi == 3) positionEnnemi = positionEnnemi3;
    if (ennemi == 4) positionEnnemi = positionEnnemi4;
    if (ennemi == 5) positionEnnemi = positionEnnemi5;
    if (ennemi == 6) positionEnnemi = positionPnj1;


switch(deplacement)
                        {
                        case HAUT:
                            if (positionEnnemi.y <= 1) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            positionEnnemi.y -= x; break;

                        case BAS:
                            if (positionEnnemi.y >= orig_height - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= orig_width - 35) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x += x; break;


                        case GAUCHE:
                            if (positionEnnemi.x <= 1) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x -= x;  break;

                        }
    if (ennemi == 1) positionEnnemi1 = positionEnnemi;
    if (ennemi == 2) positionEnnemi2 = positionEnnemi;
    if (ennemi == 3) positionEnnemi3 = positionEnnemi;
    if (ennemi == 4) positionEnnemi4 = positionEnnemi;
    if (ennemi == 5) positionEnnemi5 = positionEnnemi;
    if (ennemi == 6) positionPnj1 = positionEnnemi;



  return 0;
  }


int DeplaceBoss (int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] )
{
    SDL_Rect positionEnnemi;

    positionEnnemi = positionBoss;

switch(deplacement)
                        {
                        case HAUT:
                            if (positionEnnemi.y <= 1) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            positionEnnemi.y -= x; break;

                        case BAS:
                            if (positionEnnemi.y >= orig_height - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC]     [(positionEnnemi.y) / TAILLE_BLOC + 3] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 3] [(positionEnnemi.y) / TAILLE_BLOC + 3] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC]     [(positionEnnemi.y) / TAILLE_BLOC + 3] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 3] [(positionEnnemi.y) / TAILLE_BLOC + 3] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= orig_width - 35) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 3] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 3] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 3] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 3] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x += x; break;


                        case GAUCHE:
                            if (positionEnnemi.x <= 1) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x -= x;  break;

                        }

    positionBoss = positionEnnemi;


  return 0;
  }



int DeplaceFireball (int fireball, int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] )
{

SDL_Rect positionEnnemi = {0,0,0,0};

    if ( fireball == 1) positionEnnemi = positionFireball1;
    else if ( fireball == 2) positionEnnemi = positionFireball2;
    else if ( fireball == 3) positionEnnemi = positionFireball3;
    else if ( fireball == 4) positionEnnemi = positionFireball4;


switch(deplacement)
                        {
                        case HAUT:
                            if (positionEnnemi.y <= 1) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            positionEnnemi.y -= x; break;

                        case BAS:
                            if (positionEnnemi.y >= orig_height - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= orig_width - 35) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x += x; break;


                        case GAUCHE:
                            if (positionEnnemi.x <= 1) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x -= x;  break;

                        }

    if ( fireball == 1) positionFireball1 = positionEnnemi;
    else if ( fireball == 2) positionFireball2 = positionEnnemi;
    else if ( fireball == 3) positionFireball3 = positionEnnemi;
    else if ( fireball == 4) positionFireball4 = positionEnnemi;



  return 0;
  }



int DeplaceBaton (int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] )
{

SDL_Rect positionEnnemi;
positionEnnemi = PositionBaton;

switch(deplacement)
                        {
                        case HAUT:
                            if (positionEnnemi.y <= 1) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] <= 20)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y - 2) / TAILLE_BLOC] >= 46)  break;
                            positionEnnemi.y -= x; break;

                        case BAS:
                            if (positionEnnemi.y >= orig_height - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= orig_width - 35) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x + 2) / TAILLE_BLOC + 1] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x += x; break;


                        case GAUCHE:
                            if (positionEnnemi.x <= 1) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC] >= 46) break;
                            if (carte[(positionEnnemi.x - 2) / TAILLE_BLOC] [positionEnnemi.y / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.x -= x;  break;

                        }

PositionBaton = positionEnnemi ;

  return 0;
  }



int laisseItem (int ennemi)
{
    srand(time(NULL));
    int itemX = 0;

    //1. On teste quel tpe d'items peuvent etre laisses et on en tire un au sort
    if ( itemLaisse == 1 ) {
        itemX = (rand() % (6 - 1 + 1)) + 1;

        if ( itemX == 2)
                 {  //on charge coeur
                    item1.itemExiste = 1;
                    item1.itemType = 1; // 1 = coeur, 2 = argent...
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;
                                    }

        if ( itemX == 4)
                 {  //on charge money
                    item1.itemExiste = 1;
                    item1.itemType = 2; // 1 = coeur, 2 = argent, 3 = potion, 4 = key
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;
                                    }

    } // Fin itemLaisse = 1******************************



   else if ( itemLaisse == 2 ) {
        itemX = (rand() % (6 - 1 + 1)) + 1;

        if ( itemX == 2)
                 {  //on charge coeur
                    item1.itemExiste = 1;
                    item1.itemType = 1; // 1 = coeur, 2 = argent...
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;
                                    }

        if ( itemX == 4)
                 {  //on charge money
                    item1.itemExiste = 1;
                    item1.itemType = 2; // 1 = coeur, 2 = argent, 3 = potion, 4 = key
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;
                                    }


        if ( itemX == 6)
                 {  //on charge potion
                    item1.itemExiste = 1;
                    item1.itemType = 3; // 1 = coeur, 2 = argent, 3 = potion, 4 = key
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;
                                    }

    } // Fin itemLaisse = 2***********************************


    else if ( itemLaisse == 3 ) {

                    item1.itemExiste = 1;
                    item1.itemType = 4; // 1 = coeur, 2 = argent...
                    if ( ennemi == 1) item1.positionItem = positionEnnemi1;
                    else if ( ennemi == 2) item1.positionItem = positionEnnemi2;
                    else if ( ennemi == 3) item1.positionItem = positionEnnemi3;
                    else if ( ennemi == 4) item1.positionItem = positionEnnemi4;
                    else if ( ennemi == 5) item1.positionItem = positionEnnemi5;



    } // Fin itemLaisse = 3******************************



    return 0;
}



int AfficheTexteItems (SDL_Surface *ecran, TTF_Font *police, char Chaine[50], SDL_Rect position)
{

    SDL_Surface *texte = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};


    //Affichage du texte : pour afficher le level en bas
        // sprintf(Chaine, "Level");
        texte = TTF_RenderText_Blended(police, Chaine, couleurBlanche);
        BlitSprite(texte, ecran, &position);


    //On libere la memoire sinon elle gonfle
        SDL_FreeSurface(texte);




return 0;

}

static void rtrim_eol(char *str)
{
    int i;
    i = strlen(str);
    while ((i > 0) && ((str[i - 1] == '\n') || (str[i - 1] == '\r')))
    {
        str[i - 1] = 0;
        i--;
    }
}

int AfficheDialogues (SDL_Surface *ecran, TTF_Font *police, int dialogue)
{

    //Fichier
    char nomFichier[25] = "";
    sprintf (nomFichier, "dialogues/%d.dialog", dialogue);
    int caractereLu = 0, nombreLignes = 0, i = 0, j = 0, continuer = 1;
    FILE* fichier = NULL;
    int tempoTouche = SDL_GetTicks();
    fichier = fopen ( nomFichier, "r");
    if (fichier == NULL)
        return 0;

    //On compte le nombre de lignes
    do
    {
    caractereLu = fgetc(fichier);
    if (caractereLu == '\n')
        nombreLignes++;
    } while(caractereLu != EOF);

    i = nombreLignes / 4;  // on affiche trois lignes à la fois. le fichier doit donc etre composé de séquences de trois lignes

    //Rembobinage fichier
    rewind ( fichier );

    //Variables
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Rect posD;
       posD.x = 1;
       posD.y = 0;

    SDL_Rect posT1;
       posT1.x = 20;
       posT1.y = 15;
    SDL_Rect posT2;
       posT2.x = 20;
       posT2.y = 40;
    SDL_Rect posT3;
       posT3.x = 20;
       posT3.y = 65;
    SDL_Rect posT4;
       posT4.x = 20;
       posT4.y = 90;

   char chaine1 [70];
   char chaine2 [70];
   char chaine3 [70];
   char chaine4 [70];

    for ( j = 0; j <= i; j++)
    {



   //On lit les trois lignes du fichier
   fgets(chaine1, 57, fichier);
   rtrim_eol(chaine1);
   fgets(chaine2, 57, fichier);
   rtrim_eol(chaine2);
   fgets(chaine3, 57, fichier);
   rtrim_eol(chaine3);
   fgets(chaine4, 57, fichier);
   rtrim_eol(chaine4);

   SDL_Surface *texte1 = NULL, *texte2 = NULL, *texte3 = NULL, *texte4 = NULL,*fond = NULL;
   fond = loadScreenImage("fond/dialog.bmp");
   BlitSprite(fond, ecran, &posD);

    texte1 = TTF_RenderText_Blended(police, chaine1, couleurBlanche);
    BlitSprite(texte1, ecran, &posT1);
    texte2 = TTF_RenderText_Blended(police, chaine2, couleurBlanche);
    BlitSprite(texte2, ecran, &posT2);
    texte3 = TTF_RenderText_Blended(police, chaine3, couleurBlanche);
    BlitSprite(texte3, ecran, &posT3);
    texte4 = TTF_RenderText_Blended(police, chaine4, couleurBlanche);
    BlitSprite(texte4, ecran, &posT4);

    //On affiche
    FlipScreen();

    //SDL_Delay (3000);

    //SDL_EnableKeyRepeat(0, 0);

    ClearKeys();

    while (continuer)
{
    SDL_Event event;

    SDL_Delay(10);
    while (SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                event.type=0;
                break;
            case SDL_KEYDOWN:
                if (tempoTouche + 1000 < SDL_GetTicks()) {
                    continuer = 0;
                    tempoTouche = SDL_GetTicks();
                    event.type=0; }
                else event.type=0;
                break;

            case SDL_JOYBUTTONDOWN:
#if defined(GP2X)
                switch(event.jbutton.button)
                {
                case GP2X_BUTTON_SELECT:
                    continuer = 0;
                    event.type=0;
                    break;
                case GP2X_BUTTON_A:
                case GP2X_BUTTON_B:
                case GP2X_BUTTON_X:
                case GP2X_BUTTON_Y:
                    if (tempoTouche + 1000 < SDL_GetTicks()) {
                        continuer = 0;
                        tempoTouche = SDL_GetTicks();
                        event.type=0; }
                    else event.type=0;
                    break;
                case GP2X_BUTTON_VOLUP:
                    Change_HW_Audio_Volume(4);
                    break;
                case GP2X_BUTTON_VOLDOWN:
                    Change_HW_Audio_Volume(-4);
                    break;

                }
#else
                if ( event.jbutton.button == 0 )
                {
                    if (tempoTouche + 1000 < SDL_GetTicks()) {
                    continuer = 0;
                    tempoTouche = SDL_GetTicks();
                    event.type=0; }
                    else event.type=0;
                }
#endif
                break;
        }

    }


    //On libere la memoire sinon elle gonfle
        SDL_FreeSurface(texte1);
        SDL_FreeSurface(texte2);
        SDL_FreeSurface(texte3);
        SDL_FreeSurface(texte4);
        SDL_FreeSurface(fond);


    }

    fclose(fichier);
    //SDL_EnableKeyRepeat(10, 10);
    return 0 ;
}


int title ( SDL_Surface *ecran, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{

unsigned int frameLimit = SDL_GetTicks() + 16;
int continuer = 1;
int timer = SDL_GetTicks();

SDL_Surface *titre = NULL;
titre = loadFullScreenImage("fond/title.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);
#if defined(PANDORA)
    SDL_Color textcolor = {255, 255, 255};
    SDL_Rect pos2;
       pos2.x = 0;
       pos2.y = 1;
    SDL_Surface *text2 = NULL;
    text2 = TTF_RenderText_Blended(police, "Entry for the Alive & Kicking Coding Competition 2013/2014.", textcolor);
    BlitSprite(text2, ecran, &pos2);
#endif
//On affiche
    FlipScreen();

    ClearKeys();


    while (continuer)
{

    /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();




        if ( timer + 500 < SDL_GetTicks() )
        {

                    if (input.quit || input.escape)
                    {
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        return 0;
                    }

                    if (input.un)
                    {

                        input.enter = input.un = input.escape = 0;
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        continuer = 0;

                    }

                    if (input.deux)
                    {

                        input.enter = input.deux = input.escape = 0;
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        loadSavedGame(coeur, potion, coeurmax, money, level, power, boss, key, baton);
                        continuer = 0;
                    }

                       if (input.trois)
                    {

                        input.enter = input.trois = input.escape = 0;
                        input.timer = SDL_GetTicks();
                        continuer = credits( ecran );
                        if (continuer)
                        {
                            SDL_BlitSurface(titre, NULL, ecran, &pos);
#if defined(PANDORA)
                            BlitSprite(text2, ecran, &pos2);
#endif

                        //On affiche
                            FlipScreen();
                        }
                        else
                        {
#if defined(PANDORA)
                            SDL_FreeSurface(text2);
#endif
                            SDL_FreeSurface(titre);
                        }
                    }

            input.timer = SDL_GetTicks();

        }

        delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;

    }

    ClearScreen();
    return 1;
}


void game_over ( SDL_Surface *ecran, int *coeur, int *continuer, int *potion, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{
int continuer2 = 1;
SDL_Event event;

SDL_Surface *titre = NULL;
titre = loadFullScreenImage("fond/gameover.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);

//On affiche
    FlipScreen();

    ClearKeys();

    while (continuer2)
{
    SDL_Delay(10);

    while (SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                *continuer = 0;
                continuer2 = 0;
                break;
            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {
                        case SDLK_KP1:
                        case SDLK_1:
                        loadSavedGame(coeur, potion, coeurmax, money, level, power, boss, key, baton);
                        continuer2 = 0;
                        break;

                        case SDLK_KP2:
                        case SDLK_2:
                        *continuer = 0;
                        continuer2 = 0;
                        break;

                        case SDLK_KP3:
                        case SDLK_3:
                        *coeur = 5;
                        continuer2 = 0;
                        break;


                        default:
                        break;


                        }
            break;
#if defined(GP2X)
            case SDL_JOYBUTTONDOWN:
                switch(event.jbutton.button)
                {
                case GP2X_BUTTON_A:
                    loadSavedGame(coeur, potion, coeurmax, money, level, power, boss, key, baton);
                    continuer2 = 0;
                    break;

                case GP2X_BUTTON_Y:
                    *continuer = 0;
                    continuer2 = 0;
                    break;

                case GP2X_BUTTON_B:
                    *coeur = 5;
                    continuer2 = 0;
                    break;

                case GP2X_BUTTON_SELECT:
                    *continuer = 0;
                    continuer2 = 0;
                    break;

                case GP2X_BUTTON_VOLUP:
                    Change_HW_Audio_Volume(4);
                    break;

                case GP2X_BUTTON_VOLDOWN:
                    Change_HW_Audio_Volume(-4);
                    break;

                }
            break;
#endif
        }

    }

SDL_FreeSurface( titre );

    ClearScreen();
}


int credits ( SDL_Surface *ecran )
{

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int timer = SDL_GetTicks();
    SDL_Surface *titre = NULL;
    titre = loadFullScreenImage("fond/credits.jpg");

    SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

    SDL_BlitSurface(titre, NULL, ecran, &pos);

    FlipScreen();

    ClearKeys();

    while (1)
    {

        /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();

        if ( timer + 500 < SDL_GetTicks() )
        {
            if (input.quit || input.enter || input.escape)
                {
                    input.enter = input.pause = input.escape = 0;
                    input.timer = SDL_GetTicks();
                    SDL_FreeSurface(titre);
                    ClearScreen();
                    return (input.quit)?0:1;
                }

        }

        delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;
    }


}


int shop ( SDL_Surface *ecran, TTF_Font *police, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{
int continuer2 = 1;
SDL_Event event;
FILE* fichier = NULL;


SDL_Surface *shop = NULL;
shop = loadScreenImage("fond/shop.jpg");

SDL_Rect pos;
       pos.x = 1;
       pos.y = 0;

BlitSprite(shop, ecran, &pos);

//On affiche
    FlipScreen();

    ClearKeys();

    while (continuer2)
{
    SDL_Delay(10);

    while (SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                SDL_FreeSurface( shop );
                return 0;

            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {
                        case SDLK_KP1:
                        case SDLK_1:
#if defined(GP2X)
                    shop_1:
#endif
                        if (*money >= 30) { *money -= 30; *coeur=*coeurmax; AfficheDialogues (ecran, police, 988); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_KP2:
                        case SDLK_2:
#if defined(GP2X)
                    shop_2:
#endif
                        fichier = fopen("save.lvl", "w+");
                        if (*level <= 9) fprintf(fichier, "00%d", *level);
                        else if (*level <= 99) fprintf(fichier, "0%d", *level);
                        else if (*level <= 999) fprintf(fichier, "%d", *level);
                        if (*coeur <= 9) fprintf(fichier, "0%d", *coeur);
                        else if (*coeur <= 99) fprintf(fichier, "%d", *coeur);
                        if (*coeurmax <= 9) fprintf(fichier, "0%d", *coeurmax);
                        else if (*coeurmax <= 99) fprintf(fichier, "%d", *coeurmax);
                        fprintf(fichier, "%d", *potion);
                        fprintf(fichier, "%d", *power);
                        fprintf(fichier, "%d", *boss);
                        if (*money <= 9) fprintf(fichier, "00%d", *money);
                        else if (*money <= 99) fprintf(fichier, "0%d", *money);
                        else if (*money <= 999) fprintf(fichier, "%d", *money);
                        fprintf(fichier, "%d", *key);
                        fprintf(fichier, "%d", *baton);
                        fclose(fichier);

                        fichier = fopen("savecoffres.lvl", "w+");
                        writeCoffres(fichier);
                        fclose(fichier);

                        fichier = fopen("saveswitchs.lvl", "w+");
                        writeSwitchs(fichier);
                        fclose(fichier);

                        continuer2 = 0;
                        break;

                        case SDLK_KP3:
                        case SDLK_3:
#if defined(GP2X)
                    shop_3:
#endif
                        if (*money >= 100) { *money -= 100; *potion+= 1; AfficheDialogues (ecran, police, 986); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_ESCAPE:
                        case SDLK_SPACE:
#if defined(PANDORA)
                        case SDLK_HOME:
                        case SDLK_END:
                        case SDLK_PAGEDOWN:
                        case SDLK_PAGEUP:
#endif
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                        continuer2 = 0;
                        break;

                        default:
                            break;



                        }
            break;

            case SDL_JOYBUTTONDOWN:
#if defined(GP2X)
                switch(event.jbutton.button)
                {
                case GP2X_BUTTON_A:
                    goto shop_1;

                case GP2X_BUTTON_Y:
                    goto shop_2;

                case GP2X_BUTTON_B:
                    goto shop_3;

                case GP2X_BUTTON_X:
                    continuer2 = 0;
                    break;

                case GP2X_BUTTON_SELECT:
                    SDL_FreeSurface( shop );
                    return 0;

                case GP2X_BUTTON_VOLUP:
                    Change_HW_Audio_Volume(4);
                    break;

                case GP2X_BUTTON_VOLDOWN:
                    Change_HW_Audio_Volume(-4);
                    break;

                }
#else
                if ( event.jbutton.button == 0 )
                {
                continuer2 = 0;
                }
#endif
                break;
        }
    }

SDL_FreeSurface( shop );

    return 1;
}


void fin ( SDL_Surface *ecran, int *continuer )
{
int continuer2 = 1;
SDL_Event event;

SDL_Surface *titre = NULL;
titre = loadFullScreenImage("fond/fin.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);

//On affiche
    FlipScreen();

    ClearKeys();

    while (continuer2)
{
    SDL_Delay(10);

    while (SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                *continuer = 0;
                continuer2 = 0;
                break;
            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {

                        case SDLK_ESCAPE:
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                        case SDLK_SPACE:
#if defined(PANDORA)
                        case SDLK_HOME:
                        case SDLK_END:
                        case SDLK_PAGEDOWN:
                        case SDLK_PAGEUP:
#endif
                        *continuer = 0;
                        continuer2 = 0;
                        break;


                        default:
                        break;


                        }
            break;
#if defined(GP2X)
            case SDL_JOYBUTTONDOWN:
                switch(event.jbutton.button)
                {
                case GP2X_BUTTON_A:
                case GP2X_BUTTON_Y:
                case GP2X_BUTTON_B:
                case GP2X_BUTTON_X:
                case GP2X_BUTTON_SELECT:
                    *continuer = 0;
                    continuer2 = 0;
                    break;
                case GP2X_BUTTON_VOLUP:
                    Change_HW_Audio_Volume(4);
                    break;
                case GP2X_BUTTON_VOLDOWN:
                    Change_HW_Audio_Volume(-4);
                    break;
                }
            break;
#endif
        }

    }

SDL_FreeSurface( titre );

    ClearScreen();
}

void loadSavedGame(int *coeur, int *potion, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton)
{
FILE* fichier = NULL;

    fichier = fopen("save.lvl", "r");

    *level    = readNumber(fichier, 3);
    *coeur    = readNumber(fichier, 2);
    *coeurmax = readNumber(fichier, 2);
    *potion   = readNumber(fichier, 1);
    *power    = readNumber(fichier, 1);
    *boss     = readNumber(fichier, 1);
    *money    = readNumber(fichier, 3);
    *key      = readNumber(fichier, 1);
    *baton    = readNumber(fichier, 1);

    fclose(fichier);

    fichier = fopen("savecoffres.lvl", "r");
    readCoffres(fichier);
    fclose(fichier);

    fichier = fopen("saveswitchs.lvl", "r");
    readSwitchs(fichier);
    fclose(fichier);
}


#ifdef GP2X


static void ResizeImage_32(SDL_Surface *srcimage, SDL_Surface *dstimage)
{
    unsigned int dwidth, dheight, xdiff, ydiff, xpos, ypos, xstart, srcpitch, dstpitch;
    uint32_t *src, *dst, *linesrc, *linedst, alphavalue;

    src = (uint32_t *) srcimage->pixels;
    dst = (uint32_t *) dstimage->pixels;

    xstart = (srcimage->w > dstimage->w)?(65536 - ((dstimage->w << 16) / srcimage->w)):0;
    ypos = (srcimage->h > dstimage->h)?(65536 - ((dstimage->h << 16) / srcimage->h)):0;

    xdiff = (srcimage->w << 16) / dstimage->w;
    ydiff = (srcimage->h << 16) / dstimage->h;

    srcpitch = srcimage->pitch;
    dstpitch = dstimage->pitch;

    alphavalue = srcimage->format->Amask;

#define NEXT_SRC_LINE ((uint32_t *) (((uintptr_t)linesrc) + srcpitch))
#define COPY_PIXEL(dstpix, a) { dstpix = (a) | alphavalue; }
#define INTERPOLATE_2_PIXELS_1_1(dstpix, a, b) { dstpix = (((((a) & 0xff00ff) + ((b) & 0xff00ff)) >> 1) & 0xff00ff) | (((((a) & 0xff00ff00) >> 1) + (((b) & 0xff00ff00) >> 1)) & 0xff00ff00) | alphavalue; }
#define INTERPOLATE_4_PIXELS_1_1_1_1(dstpix, a, b, c, d) { dstpix = (((((a) & 0xff00ff) + ((b) & 0xff00ff) + ((c) & 0xff00ff) + ((d) & 0xff00ff)) >> 2) & 0xff00ff) | (((((a) & 0xff00ff00) >> 2) + (((b) & 0xff00ff00) >> 2) + (((c) & 0xff00ff00) >> 2) + (((d) & 0xff00ff00) >> 2)) & 0xff00ff00) | alphavalue; }

    for (dheight = dstimage->h; dheight != 0; dheight--)
    {
        linesrc = src;
        linedst = dst;
        xpos = xstart;

        switch ((ypos >> 14) & 3)
        {
            case 3:
                linesrc = NEXT_SRC_LINE;
            case 0:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            COPY_PIXEL(*linedst, linesrc[0])
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[0], linesrc[1])
                            break;
                        case 3:
                            COPY_PIXEL(*linedst, linesrc[1])
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16);
                    xpos &= 0xffff;

                    linedst ++;
                }
                break;
            case 1:
            case 2:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[0], NEXT_SRC_LINE[0])
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_4_PIXELS_1_1_1_1(*linedst, linesrc[0], linesrc[1], NEXT_SRC_LINE[0], NEXT_SRC_LINE[1])
                            break;
                        case 3:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[1], NEXT_SRC_LINE[1])
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16);
                    xpos &= 0xffff;

                    linedst ++;
                }
                break;
        }


        ypos += ydiff;
        src = (uint32_t *) (((uintptr_t)src) + (ypos >> 16) * srcpitch);
        ypos &= 0xffff;

        dst = (uint32_t *) (((uintptr_t)dst) + dstpitch);
    }

#undef NEXT_SRC_LINE
#undef COPY_PIXEL
#undef INTERPOLATE_2_PIXELS_1_1
#undef INTERPOLATE_4_PIXELS_1_1_1_1
}

static void ResizeImage_24(SDL_Surface *srcimage, SDL_Surface *dstimage)
{
    unsigned int dwidth, dheight, xdiff, ydiff, xpos, ypos, xstart, srcpitch, dstpitch;
    uint8_t *src, *dst, *linesrc, *linedst;

    src = (uint8_t *) srcimage->pixels;
    dst = (uint8_t *) dstimage->pixels;

    xstart = (srcimage->w > dstimage->w)?(65536 - ((dstimage->w << 16) / srcimage->w)):0;
    ypos = (srcimage->h > dstimage->h)?(65536 - ((dstimage->h << 16) / srcimage->h)):0;

    xdiff = (srcimage->w << 16) / dstimage->w;
    ydiff = (srcimage->h << 16) / dstimage->h;

    srcpitch = srcimage->pitch;
    dstpitch = dstimage->pitch;

#define NEXT_SRC_LINE (linesrc + srcpitch)
#define COPY_PIXEL(x, a) { x[0] = (a)[0]; x[1] = (a)[1]; x[2] = (a)[2]; }
#define INTERPOLATE_2_PIXELS_1_1(x, a, b) { x[0] = (((uint32_t)((a)[0])) + ((uint32_t)((b)[0]))) >> 1; x[1] = (((uint32_t)((a)[1])) + ((uint32_t)((b)[1]))) >> 1; x[2] = (((uint32_t)((a)[2])) + ((uint32_t)((b)[2]))) >> 1; }
#define INTERPOLATE_4_PIXELS_1_1_1_1(x, a, b, c, d) { x[0] = (((uint32_t)((a)[0])) + ((uint32_t)((b)[0])) + ((uint32_t)((c)[0])) + ((uint32_t)((d)[0]))) >> 2; x[1] = (((uint32_t)((a)[1])) + ((uint32_t)((b)[1])) + ((uint32_t)((c)[1])) + ((uint32_t)((d)[1]))) >> 2; x[2] = (((uint32_t)((a)[2])) + ((uint32_t)((b)[2])) + ((uint32_t)((c)[2])) + ((uint32_t)((d)[2]))) >> 2; }

    for (dheight = dstimage->h; dheight != 0; dheight--)
    {
        linesrc = src;
        linedst = dst;
        xpos = xstart;

        switch ((ypos >> 14) & 3)
        {
            case 3:
                linesrc = NEXT_SRC_LINE;
            case 0:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            COPY_PIXEL(linedst, linesrc)
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_2_PIXELS_1_1(linedst, linesrc, linesrc + 3)
                            break;
                        case 3:
                            COPY_PIXEL(linedst, linesrc + 3)
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16) * 3;
                    xpos &= 0xffff;

                    linedst += 3;
                }
                break;
            case 1:
            case 2:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            INTERPOLATE_2_PIXELS_1_1(linedst, linesrc, NEXT_SRC_LINE)
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_4_PIXELS_1_1_1_1(linedst, linesrc, linesrc + 3, NEXT_SRC_LINE, NEXT_SRC_LINE + 3)
                            break;
                        case 3:
                            INTERPOLATE_2_PIXELS_1_1(linedst, linesrc + 3, NEXT_SRC_LINE + 3)
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16) * 3;
                    xpos &= 0xffff;

                    linedst += 3;
                }
                break;
        }


        ypos += ydiff;
        src += (ypos >> 16) * srcpitch;
        ypos &= 0xffff;

        dst += dstpitch;
    }

#undef NEXT_SRC_LINE
#undef COPY_PIXEL
#undef INTERPOLATE_2_PIXELS_1_1
#undef INTERPOLATE_4_PIXELS_1_1_1_1
}

static void ResizeTranspImage_32(SDL_Surface *srcimage, SDL_Surface *dstimage, uint32_t srckey)
{
    unsigned int dwidth, dheight, xdiff, ydiff, xpos, ypos, xstart, srcpitch, dstpitch;
    uint32_t *src, *dst, *linesrc, *linedst, alphavalue;

    src = (uint32_t *) srcimage->pixels;
    dst = (uint32_t *) dstimage->pixels;

    xstart = (srcimage->w > dstimage->w)?(65536 - ((dstimage->w << 16) / srcimage->w)):0;
    ypos = (srcimage->h > dstimage->h)?(65536 - ((dstimage->h << 16) / srcimage->h)):0;

    xdiff = (srcimage->w << 16) / dstimage->w;
    ydiff = (srcimage->h << 16) / dstimage->h;

    srcpitch = srcimage->pitch;
    dstpitch = dstimage->pitch;

    alphavalue = srcimage->format->Amask;

#define NEXT_SRC_LINE ((uint32_t *) (((uintptr_t)linesrc) + srcpitch))
#define COPY_PIXEL(dstpix, a) { dstpix = (a); }

#define INTERPOLATE_2_PIXELS_1_1(dstpix, a, b) { \
        if ((a) == (b)) { \
            dstpix = (a); \
        } else if ((a) == srckey) { \
            dstpix = (((b) & 0xfefefefe & ~alphavalue) >> 1) | ((b) & alphavalue); \
        } else if ((b) == srckey) { \
            dstpix = (((a) & 0xfefefefe & ~alphavalue) >> 1) | ((a) & alphavalue); \
        } else { \
            dstpix = dstpix = (((((a) & 0xff00ff) + ((b) & 0xff00ff)) >> 1) & 0xff00ff) | (((((a) & 0xff00ff00) >> 1) + (((b) & 0xff00ff00) >> 1)) & 0xff00ff00); \
        } \
    }

#define INTERPOLATE_4_PIXELS_1_1_1_1(dstpix, a, b, c, d) { \
        register unsigned int c0, c2, tmppix; \
        if ((a) == srckey) { \
            c0 = c2 = 0; \
            tmppix = 1; \
        } else { \
            c0 = (a) & 0xff00ff; c2 = ((a) & 0xff00ff00) >> 2; \
            tmppix = 0; \
        } \
        if ((b) == srckey) { \
            tmppix ++; \
        } else { \
            c0 += (b) & 0xff00ff; c2 += ((b) & 0xff00ff00) >> 2; \
        } \
        if ((c) == srckey) { \
            tmppix ++; \
        } else { \
            c0 += (c) & 0xff00ff; c2 += ((c) & 0xff00ff00) >> 2; \
        } \
        if ((d) == srckey) { \
            tmppix ++; \
        } else { \
            c0 += (d) & 0xff00ff; c2 += ((d) & 0xff00ff00) >> 2; \
        } \
        switch(tmppix) { \
            case 1: \
                c0 += alphavalue & 0xff00ff; c2 += (alphavalue & 0xff00ff00) >> 2; \
            case 0: \
                dstpix = ((c0 >> 2) & 0xff00ff) | (c2 & 0xff00ff00); \
                break; \
            case 2: \
                tmppix = ((c0 >> 1) & 0xff00ff) | ((c2 << 1) & 0xff00ff00); \
                dstpix = (((tmppix) & 0xfefefefe & ~alphavalue) >> 1) | ((tmppix) & alphavalue); \
                break; \
            case 3: \
                tmppix = c0 | (c2 << 2); \
                dstpix = (((tmppix) & 0xfcfcfcfc & ~alphavalue) >> 2) | ((tmppix) & alphavalue); \
                break; \
            case 4: \
                dstpix = srckey; \
                break; \
        } \
    }

    for (dheight = dstimage->h; dheight != 0; dheight--)
    {
        linesrc = src;
        linedst = dst;
        xpos = xstart;

        switch ((ypos >> 14) & 3)
        {
            case 3:
                linesrc = NEXT_SRC_LINE;
            case 0:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            COPY_PIXEL(*linedst, linesrc[0])
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[0], linesrc[1])
                            break;
                        case 3:
                            COPY_PIXEL(*linedst, linesrc[1])
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16);
                    xpos &= 0xffff;

                    linedst ++;
                }
                break;
            case 1:
            case 2:
                for (dwidth = dstimage->w; dwidth != 0; dwidth--)
                {
                    switch ((xpos >> 14) & 3)
                    {
                        case 0:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[0], NEXT_SRC_LINE[0])
                            break;
                        case 1:
                        case 2:
                            INTERPOLATE_4_PIXELS_1_1_1_1(*linedst, linesrc[0], linesrc[1], NEXT_SRC_LINE[0], NEXT_SRC_LINE[1])
                            break;
                        case 3:
                            INTERPOLATE_2_PIXELS_1_1(*linedst, linesrc[1], NEXT_SRC_LINE[1])
                            break;
                    }

                    xpos += xdiff;
                    linesrc += (xpos >> 16);
                    xpos &= 0xffff;

                    linedst ++;
                }
                break;
        }


        ypos += ydiff;
        src = (uint32_t *) (((uintptr_t)src) + (ypos >> 16) * srcpitch);
        ypos &= 0xffff;

        dst = (uint32_t *) (((uintptr_t)dst) + dstpitch);
    }

#undef NEXT_SRC_LINE
#undef COPY_PIXEL
#undef INTERPOLATE_2_PIXELS_1_1
#undef INTERPOLATE_4_PIXELS_1_1_1_1
}

static SDL_Surface *ResizeImage(SDL_Surface *srcimage, int width, int height, int transp)
{
    SDL_Surface *dstimage;

    if ((srcimage->format->BitsPerPixel != 32) && (transp || (srcimage->format->BitsPerPixel != 24)))
    {
        return NULL;
    }

    dstimage = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, srcimage->format->BitsPerPixel, srcimage->format->Rmask, srcimage->format->Gmask, srcimage->format->Bmask, srcimage->format->Amask);
    if (dstimage == NULL)
    {
        return NULL;
    }

    SDL_LockSurface(srcimage);
    SDL_LockSurface(dstimage);

    if (transp)
    {
        ResizeTranspImage_32(srcimage, dstimage, SDL_MapRGBA(srcimage->format, TRANS_R, TRANS_G, TRANS_B, SDL_ALPHA_TRANSPARENT));
    }
    else if (srcimage->format->BitsPerPixel == 32)
    {
        ResizeImage_32(srcimage, dstimage);
    }
    else
    {
        ResizeImage_24(srcimage, dstimage);
    }

    SDL_UnlockSurface(dstimage);
    SDL_UnlockSurface(srcimage);

    return dstimage;
}



static SDL_Surface *loadAndResizeImage(char *name, int width, int height, int transp)
{
	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image, *temp2;

    if (temp == NULL)
    {
        char newname[MAX_PATH], *name2;
        strncpy(newname, name, MAX_PATH);
        newname[MAX_PATH-1] = 0;
        name2 = rindex(newname, '/');
        name2 = (name2 == NULL)?newname:(name2+1);
        for (; *name2 != 0; name2++)
        {
            *name2 = tolower(*name2);
        }

        temp = IMG_Load(newname);
        if (temp == NULL)
        {
            name2 = rindex(newname, '/');
            name2 = (name2 == NULL)?newname:(name2+1);
            for (; *name2 != 0; name2++)
            {
                *name2 = toupper(*name2);
            }

            temp = IMG_Load(newname);
        }
    }

	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);

		return NULL;
	}

    if (width == 0) width = ((temp->w * TILE_WIDTH) + (TAILLE_BLOC - 1)) / TAILLE_BLOC;
    if (height == 0) height = ((temp->h * TILE_HEIGHT) + (TAILLE_BLOC - 1)) / TAILLE_BLOC;


    if ((width != temp->w) || (height != temp->h))
    {
        temp2 = ResizeImage(temp, width, height, transp);
        SDL_FreeSurface(temp);
    }
    else
    {
        temp2 = temp;
    }

    if (temp2 != NULL)
    {
        if (transp)
        {

#if defined(GP2X)
            #define COLORKEYGP2X 0xf81f
            #define NCOLORKEYGP2X 0xf83f

            image = SDL_CreateRGBSurface(SDL_HWSURFACE, temp2->w, temp2->h, 16, 0xf800, 0x07e0, 0x001f, 0);
            if (image != NULL)
            {
                int y;
                uint32_t srccolorkey = SDL_MapRGBA(temp2->format, TRANS_R, TRANS_G, TRANS_B, SDL_ALPHA_TRANSPARENT);

                /* Gestion de la transparence*/
                SDL_SetColorKey(image, SDL_SRCCOLORKEY, COLORKEYGP2X);

                /* Convertit l'image au format de l'écran (screen) */
                SDL_LockSurface(temp2);
                SDL_LockSurface(image);
                for (y = 0; y < temp2->h; y++)
                {
                    int x;
                    uint32_t *src = (uint32_t *)(y * temp2->pitch + (uintptr_t)temp2->pixels);
                    uint16_t *dst = (uint16_t *)(y * image->pitch + (uintptr_t)image->pixels);
                    for (x = 0; x < temp2->w; x++)
                    {
                        if (src[x] == srccolorkey)
                        {
                            dst[x] = COLORKEYGP2X;
                        }
                        else
                        {
                            int colr = (src[x] >>  3) & 0x1f;
                            int colg = (src[x] >> 10) & 0x3f;
                            int colb = (src[x] >> 19) & 0x1f;
                            int col16 = (colr << 11) | (colg << 5) | colb;
                            dst[x] = (col16 == COLORKEYGP2X)?NCOLORKEYGP2X:col16;
                        }
                    }
                }
                SDL_UnlockSurface(image);
                SDL_UnlockSurface(temp2);
            }

            #undef COLORKEYGP2X
            #undef NCOLORKEYGP2X
#else
            /* Gestion de la transparence*/
            SDL_SetColorKey(temp2, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp2->format, TRANS_R, TRANS_G, TRANS_B));

            /* Convertit l'image au format de l'écran (screen) */
            image = SDL_DisplayFormat(temp2);
#endif
        }
        else
        {
            /* Convertit l'image au format de l'écran (screen) */
            image = SDL_DisplayFormat(temp2);
        }
        SDL_FreeSurface(temp2);
    }
    else
    {
        image = NULL;
    }

    if (image == NULL)
    {
		printf("Failed to convert image %s to native format\n", name);

		return NULL;
    }

	/* Retourne l'image au format de l'écran pour accélérer son blit */

	return image;

}

#endif

/* Nouvelles fonctions avril 2010 - mise à niveau */

/* Charge les images pour un blit plus rapide */
SDL_Surface *loadImage(char *name)
{
#ifdef GP2X
    return loadAndResizeImage(name, 0, 0, 1);
#else
	/* Charge les images avec SDL Image */

	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;

    if (temp == NULL)
    {
        char newname[MAX_PATH], *name2;
        strncpy(newname, name, MAX_PATH);
        newname[MAX_PATH-1] = 0;
        name2 = rindex(newname, '/');
        name2 = (name2 == NULL)?newname:(name2+1);
        for (; *name2 != 0; name2++)
        {
            *name2 = tolower(*name2);
        }

        temp = IMG_Load(newname);
        if (temp == NULL)
        {
            name2 = rindex(newname, '/');
            name2 = (name2 == NULL)?newname:(name2+1);
            for (; *name2 != 0; name2++)
            {
                *name2 = toupper(*name2);
            }

            temp = IMG_Load(newname);
        }
    }

	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);

		return NULL;
	}

	/* Gestion de la transparence*/
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, TRANS_R, TRANS_G, TRANS_B));


	/* Convertit l'image au format de l'écran (screen) */

	image = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);

		return NULL;
	}

	/* Retourne l'image au format de l'écran pour accélérer son blit */

	return image;

#endif
}

SDL_Surface *loadFullScreenImage(char *name)
{
#ifdef GP2X
    return loadAndResizeImage(name, 320, 240, 0);
#else
    return loadImage(name);
#endif
}

SDL_Surface *loadScreenImage(char *name)
{
#ifdef GP2X
    return loadAndResizeImage(name, 0, 0, 0);
#else
    return loadImage(name);
#endif
}

static SDL_Surface *loadTileImage(char *name)
{
#ifdef GP2X
    return loadAndResizeImage(name, TILE_WIDTH, TILE_HEIGHT, 0);
#else
    return loadImage(name);
#endif
}


void loadTileset()
{

    //Pour choisir le chip graphique de tiles suivant le dossier : forest, dungeon...
   char loadAdress[50] = "tiles/";
   char adressSave[50] = "";
   char adressSave2[50] = "";

   if (tileSet == 1) strcat(loadAdress, "forest");
   else if (tileSet == 2) strcat(loadAdress, "dungeon");
   else if (tileSet == 3) strcat(loadAdress, "cave");
   else if (tileSet == 4) strcat(loadAdress, "villageA");
   else if (tileSet == 5) strcat(loadAdress, "villageB");
   else if (tileSet == 6) strcat(loadAdress, "shopA");
   else if (tileSet == 7) strcat(loadAdress, "shopB");
   else if (tileSet == 8) strcat(loadAdress, "dragon");
   else if (tileSet == 9) strcat(loadAdress, "dungeonB");
   else if (tileSet == 10) strcat(loadAdress, "forestB");
   else if (tileSet == 11) strcat(loadAdress, "swamps");
   else if (tileSet == 12) strcat(loadAdress, "snow");
   else if (tileSet == 13) strcat(loadAdress, "snowB");
   else if (tileSet == 14) strcat(loadAdress, "desert");
   else { tileSet = 1; strcat(loadAdress, "forest"); }

   //on copie une sauvegarde de loadAdress dans adressSave2 pour le tileset 2
    strcpy(adressSave2, loadAdress);
    strcat(loadAdress, "1/");

   //on copie une sauvegarde de loadAdress dans adressSave
   strcpy(adressSave, loadAdress);

    //Chargement des tiles du 1er tileset
    //Non traversables : <= 20 pour le test de deplacement
    mapImages[0] = loadTileImage(strcat(loadAdress, "B1.bmp"));
    //on remet loadAdress a sa valeur initiale :
    strcpy(loadAdress, adressSave);
    mapImages[1] = loadTileImage(strcat(loadAdress, "B2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[2] = loadTileImage(strcat(loadAdress, "B3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[3] = loadTileImage(strcat(loadAdress, "B4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[4] = loadTileImage(strcat(loadAdress, "B5.bmp")); strcpy(loadAdress, adressSave);
    mapImages[5] = loadTileImage(strcat(loadAdress, "B6.bmp")); strcpy(loadAdress, adressSave);
    mapImages[6] = loadTileImage(strcat(loadAdress, "B7.bmp")); strcpy(loadAdress, adressSave);
    mapImages[7] = loadTileImage(strcat(loadAdress, "B8.bmp")); strcpy(loadAdress, adressSave);
    mapImages[8] = loadTileImage(strcat(loadAdress, "B9.bmp")); strcpy(loadAdress, adressSave);
    mapImages[9] = loadTileImage(strcat(loadAdress, "B10.bmp")); strcpy(loadAdress, adressSave);
    mapImages[10] = loadTileImage(strcat(loadAdress, "B11.bmp")); strcpy(loadAdress, adressSave);
    mapImages[11] = loadTileImage(strcat(loadAdress, "B12.bmp")); strcpy(loadAdress, adressSave);
    mapImages[12] = loadTileImage(strcat(loadAdress, "B13.bmp")); strcpy(loadAdress, adressSave);
    mapImages[13] = loadTileImage(strcat(loadAdress, "B14.bmp")); strcpy(loadAdress, adressSave);
    mapImages[14] = loadTileImage(strcat(loadAdress, "B15.bmp")); strcpy(loadAdress, adressSave);
    mapImages[15] = loadTileImage(strcat(loadAdress, "B16.bmp")); strcpy(loadAdress, adressSave);
    mapImages[16] = loadTileImage(strcat(loadAdress, "B17.bmp")); strcpy(loadAdress, adressSave);
    mapImages[17] = loadTileImage(strcat(loadAdress, "B18.bmp")); strcpy(loadAdress, adressSave);
    mapImages[18] = loadTileImage(strcat(loadAdress, "B19.bmp")); strcpy(loadAdress, adressSave);
    mapImages[19] = loadTileImage(strcat(loadAdress, "B20.bmp")); strcpy(loadAdress, adressSave);

    //Traversables :
    mapImages[20] = loadTileImage(strcat(loadAdress, "T1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[21] = loadTileImage(strcat(loadAdress, "T2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[22] = loadTileImage(strcat(loadAdress, "T3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[23] = loadTileImage(strcat(loadAdress, "T4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[24] = loadTileImage(strcat(loadAdress, "T5.bmp")); strcpy(loadAdress, adressSave);
    mapImages[25] = loadTileImage(strcat(loadAdress, "T6.bmp")); strcpy(loadAdress, adressSave);
    mapImages[26] = loadTileImage(strcat(loadAdress, "T7.bmp")); strcpy(loadAdress, adressSave);
    mapImages[27] = loadTileImage(strcat(loadAdress, "T8.bmp")); strcpy(loadAdress, adressSave);
    mapImages[28] = loadTileImage(strcat(loadAdress, "T9.bmp")); strcpy(loadAdress, adressSave);
    mapImages[29] = loadTileImage(strcat(loadAdress, "T10.bmp")); strcpy(loadAdress, adressSave);
    mapImages[30] = loadTileImage(strcat(loadAdress, "T11.bmp")); strcpy(loadAdress, adressSave);
    mapImages[31] = loadTileImage(strcat(loadAdress, "T12.bmp")); strcpy(loadAdress, adressSave);
    mapImages[32] = loadTileImage(strcat(loadAdress, "T13.bmp")); strcpy(loadAdress, adressSave);
    mapImages[33] = loadTileImage(strcat(loadAdress, "T14.bmp")); strcpy(loadAdress, adressSave);
    mapImages[34] = loadTileImage(strcat(loadAdress, "T15.bmp")); strcpy(loadAdress, adressSave);
    mapImages[35] = loadTileImage(strcat(loadAdress, "T16.bmp")); strcpy(loadAdress, adressSave);
    mapImages[36] = loadTileImage(strcat(loadAdress, "T17.bmp")); strcpy(loadAdress, adressSave);
    mapImages[37] = loadTileImage(strcat(loadAdress, "T18.bmp")); strcpy(loadAdress, adressSave);
    mapImages[38] = loadTileImage(strcat(loadAdress, "T19.bmp")); strcpy(loadAdress, adressSave);
    mapImages[39] = loadTileImage(strcat(loadAdress, "T20.bmp")); strcpy(loadAdress, adressSave);
    mapImages[40] = loadTileImage(strcat(loadAdress, "T21.bmp")); strcpy(loadAdress, adressSave);
    mapImages[41] = loadTileImage(strcat(loadAdress, "T22.bmp")); strcpy(loadAdress, adressSave);
    mapImages[42] = loadTileImage(strcat(loadAdress, "T23.bmp")); strcpy(loadAdress, adressSave);
    mapImages[43] = loadTileImage(strcat(loadAdress, "T24.bmp")); strcpy(loadAdress, adressSave);
    mapImages[44] = loadTileImage(strcat(loadAdress, "T25.bmp")); strcpy(loadAdress, adressSave);

    //5 tiles speciales (coffres etc.. : 46 à 50) :
    mapImages[45] = loadTileImage(strcat(loadAdress, "S1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[46] = loadTileImage(strcat(loadAdress, "S2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[47] = loadTileImage(strcat(loadAdress, "S3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[48] = loadTileImage(strcat(loadAdress, "S4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[49] = loadTileImage(strcat(loadAdress, "S5.bmp")); strcpy(loadAdress, adressSave);

    //3 tiles tueuses:
    mapImages[50] = loadTileImage(strcat(loadAdress, "H1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[51] = loadTileImage(strcat(loadAdress, "H2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[52] = loadTileImage(strcat(loadAdress, "H3.bmp"));

    //---------------------------------------------------------

    strcpy(loadAdress, adressSave2);
    strcat(loadAdress, "2/");

   //on copie une sauvegarde de loadAdress dans adressSave
   strcpy(adressSave, loadAdress);

    //Chargement des tiles du 2eme tileset
    //Non traversables : <= 20 pour le test de deplacement
    mapImages2[0] = loadTileImage(strcat(loadAdress, "B1.bmp"));
    //on remet loadAdress a sa valeur initiale :
    strcpy(loadAdress, adressSave);
    mapImages2[1] = loadTileImage(strcat(loadAdress, "B2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[2] = loadTileImage(strcat(loadAdress, "B3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[3] = loadTileImage(strcat(loadAdress, "B4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[4] = loadTileImage(strcat(loadAdress, "B5.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[5] = loadTileImage(strcat(loadAdress, "B6.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[6] = loadTileImage(strcat(loadAdress, "B7.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[7] = loadTileImage(strcat(loadAdress, "B8.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[8] = loadTileImage(strcat(loadAdress, "B9.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[9] = loadTileImage(strcat(loadAdress, "B10.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[10] = loadTileImage(strcat(loadAdress, "B11.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[11] = loadTileImage(strcat(loadAdress, "B12.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[12] = loadTileImage(strcat(loadAdress, "B13.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[13] = loadTileImage(strcat(loadAdress, "B14.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[14] = loadTileImage(strcat(loadAdress, "B15.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[15] = loadTileImage(strcat(loadAdress, "B16.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[16] = loadTileImage(strcat(loadAdress, "B17.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[17] = loadTileImage(strcat(loadAdress, "B18.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[18] = loadTileImage(strcat(loadAdress, "B19.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[19] = loadTileImage(strcat(loadAdress, "B20.bmp")); strcpy(loadAdress, adressSave);

    //Traversables :
    mapImages2[20] = loadTileImage(strcat(loadAdress, "T1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[21] = loadTileImage(strcat(loadAdress, "T2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[22] = loadTileImage(strcat(loadAdress, "T3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[23] = loadTileImage(strcat(loadAdress, "T4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[24] = loadTileImage(strcat(loadAdress, "T5.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[25] = loadTileImage(strcat(loadAdress, "T6.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[26] = loadTileImage(strcat(loadAdress, "T7.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[27] = loadTileImage(strcat(loadAdress, "T8.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[28] = loadTileImage(strcat(loadAdress, "T9.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[29] = loadTileImage(strcat(loadAdress, "T10.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[30] = loadTileImage(strcat(loadAdress, "T11.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[31] = loadTileImage(strcat(loadAdress, "T12.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[32] = loadTileImage(strcat(loadAdress, "T13.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[33] = loadTileImage(strcat(loadAdress, "T14.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[34] = loadTileImage(strcat(loadAdress, "T15.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[35] = loadTileImage(strcat(loadAdress, "T16.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[36] = loadTileImage(strcat(loadAdress, "T17.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[37] = loadTileImage(strcat(loadAdress, "T18.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[38] = loadTileImage(strcat(loadAdress, "T19.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[39] = loadTileImage(strcat(loadAdress, "T20.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[40] = loadTileImage(strcat(loadAdress, "T21.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[41] = loadTileImage(strcat(loadAdress, "T22.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[42] = loadTileImage(strcat(loadAdress, "T23.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[43] = loadTileImage(strcat(loadAdress, "T24.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[44] = loadTileImage(strcat(loadAdress, "T25.bmp")); strcpy(loadAdress, adressSave);

    //5 tiles speciales (coffres etc.. : 46 à 50) :
    mapImages2[45] = loadTileImage(strcat(loadAdress, "S1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[46] = loadTileImage(strcat(loadAdress, "S2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[47] = loadTileImage(strcat(loadAdress, "S3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[48] = loadTileImage(strcat(loadAdress, "S4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[49] = loadTileImage(strcat(loadAdress, "S5.bmp")); strcpy(loadAdress, adressSave);

    //3 tiles tueuses:
    mapImages2[50] = loadTileImage(strcat(loadAdress, "H1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[51] = loadTileImage(strcat(loadAdress, "H2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[52] = loadTileImage(strcat(loadAdress, "H3.bmp"));

}


void freeTileset()
{
    int i;

    for (i=0 ; i < 53 ; i++ )
    {

       SDL_FreeSurface(mapImages[i]);
       SDL_FreeSurface(mapImages2[i]);

    }

}


int pauseGame(void)
{

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int timer = SDL_GetTicks();
    char text[70];

    sprintf(text, "** PAUSE **");
    drawString(text, 165, 200, police);
    FlipScreen();
    pauseSong();

    ClearKeys();

    while (1)
    {



        /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();

        if ( timer + 500 < SDL_GetTicks() )
        {
            if (input.quit || input.enter || input.escape)
                {
                    input.enter = input.pause = input.escape = 0;
                    input.timer = SDL_GetTicks();
                    if (!input.quit) pauseSong();
                    return (input.quit)?0:1;
                }

        }

        delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;
    }


}


void delay(unsigned int frameLimit)
{

    /* Gestion des 60 fps */

	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}


void drawString(char *text, int x, int y, TTF_Font *font)
{
	SDL_Rect dest;
	SDL_Surface *surface;
	SDL_Color foregroundColor;

	/* White text */

	foregroundColor.r = 255;
	foregroundColor.g = 255;
	foregroundColor.b = 255;


	/* Use SDL_TTF to generate a string image, this returns an SDL_Surface */

	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);


	if (surface == NULL)
	{
		printf("Couldn't create String %s: %s\n", text, SDL_GetError());

		return;
	}

	/* Blit the entire surface to the screen */

	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	BlitSprite(surface, ecran, &dest);

	/* Free the generated string image */

	SDL_FreeSurface(surface);
}


void getInput()
{
	SDL_Event event;

	/* Loop through waiting messages and process them */

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			/*
			** Closing the Window or pressing Escape will exit the program
			** The arrow keys will scroll the map around
			*/

            case SDL_QUIT:
                input.quit = 1;
                return;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{

					case SDLK_DELETE:
						input.erase = 1;
					break;

					case SDLK_LEFT:
						input.left = 1;
					break;

					case SDLK_RIGHT:
						input.right = 1;
					break;

					case SDLK_DOWN:
						input.down = 1;
					break;

					case SDLK_UP:
						input.up = 1;
					break;

					case SDLK_KP1:
                    case SDLK_1:
                        input.un = 1;
					break;

					case SDLK_KP2:
                    case SDLK_2:
                        input.deux = 1;
					break;

					case SDLK_KP3:
                    case SDLK_3:
                        input.trois = 1;
					break;


					case SDLK_RETURN:
                    case SDLK_KP_ENTER:
						input.enter = 1;
					break;

                    case SDLK_ESCAPE:
                        input.escape = 1;
                        break;

					default:
					break;
				}
			break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
					case SDLK_DELETE:
						input.erase = 0;
					break;

					case SDLK_LEFT:
						input.left = 0;
					break;

					case SDLK_RIGHT:
						input.right = 0;
					break;

					case SDLK_DOWN:
						input.down = 0;
					break;

					case SDLK_UP:
						input.up = 0;
					break;

					case SDLK_KP1:
                    case SDLK_1:
                        input.un = 0;
					break;

					case SDLK_KP2:
                    case SDLK_2:
                        input.deux = 0;
					break;

					case SDLK_KP3:
                    case SDLK_3:
                        input.trois = 0;
					break;

					case SDLK_RETURN:
                    case SDLK_KP_ENTER:
						input.enter = 0;
					break;

                    case SDLK_ESCAPE:
                        input.escape = 0;
                        break;

					default:
					break;
				}
			break;

#if defined(GP2X)
			case SDL_JOYBUTTONDOWN:
				switch (event.jbutton.button)
				{

					case GP2X_BUTTON_LEFT:
					case GP2X_BUTTON_UPLEFT:
					case GP2X_BUTTON_DOWNLEFT:
						input.left = 1;
					break;

					case GP2X_BUTTON_RIGHT:
					case GP2X_BUTTON_UPRIGHT:
					case GP2X_BUTTON_DOWNRIGHT:
						input.right = 1;
					break;

					case GP2X_BUTTON_DOWN:
						input.down = 1;
					break;

					case GP2X_BUTTON_UP:
						input.up = 1;
					break;

					case GP2X_BUTTON_A:
						input.un = 1;
					break;

					case GP2X_BUTTON_Y:
						input.deux = 1;
					break;

					case GP2X_BUTTON_B:
						input.trois = 1;
					break;


					case GP2X_BUTTON_X:
						input.enter = 1;
					break;

					case GP2X_BUTTON_SELECT:
						input.quit = 1;
					break;

					case GP2X_BUTTON_VOLUP:
						Change_HW_Audio_Volume(4);
					break;

					case GP2X_BUTTON_VOLDOWN:
						Change_HW_Audio_Volume(-4);
					break;

					default:
					break;
				}
			break;

			case SDL_JOYBUTTONUP:
				switch (event.jbutton.button)
				{
					case GP2X_BUTTON_LEFT:
					case GP2X_BUTTON_UPLEFT:
					case GP2X_BUTTON_DOWNLEFT:
						input.left = 0;
					break;

					case GP2X_BUTTON_RIGHT:
					case GP2X_BUTTON_UPRIGHT:
					case GP2X_BUTTON_DOWNRIGHT:
						input.right = 0;
					break;

					case GP2X_BUTTON_DOWN:
						input.down = 0;
					break;

					case GP2X_BUTTON_UP:
						input.up = 0;
					break;

					case GP2X_BUTTON_A:
						input.un = 0;
					break;

					case GP2X_BUTTON_Y:
						input.deux = 0;
					break;

					case GP2X_BUTTON_B:
						input.trois = 0;
					break;

					case GP2X_BUTTON_X:
						input.enter = 0;
					break;

					default:
					break;
				}
			break;
#endif



	}
}
}

void getJoystick()
{
	SDL_Event event;

	/* Loop through waiting messages and process them */

	while (SDL_PollEvent(&event))
	{


			if ( event.type == SDL_QUIT )
            {
                input.quit = 1;
                return;
            }

			else if ( event.type == SDL_KEYDOWN )
			{
				switch (event.key.keysym.sym)
				{

					case SDLK_DELETE:
						input.erase = 1;
					break;

					case SDLK_KP1:
                    case SDLK_1:
                        input.un = 1;
					break;

					case SDLK_KP2:
                    case SDLK_2:
                        input.deux = 1;
					break;

					case SDLK_KP3:
                    case SDLK_3:
                        input.trois = 1;
					break;


					case SDLK_RETURN:
                    case SDLK_KP_ENTER:
						input.enter = 1;
					break;

                    case SDLK_ESCAPE:
                        input.escape = 1;
                        break;

					default:
					break;

				}
			}

            else if ( event.type == SDL_JOYBUTTONDOWN )
            {

                if ( event.jbutton.button <= 10 )
                    input.enter = 1;

            }

            else if ( event.type == SDL_JOYBUTTONUP )
            {
                 if ( event.jbutton.button <= 10 )
                    input.enter = 0;

            }

            /* D-PAD */
            else if ( event.type == SDL_JOYHATMOTION )
            {
                    if ( event.jhat.value == SDL_HAT_LEFTUP
                        || event.jhat.value == SDL_HAT_LEFT
                        || event.jhat.value == SDL_HAT_LEFTDOWN
                        )
                        input.left = 1;
                    else input.left = 0;


                    if ( event.jhat.value == SDL_HAT_RIGHTUP
                        || event.jhat.value == SDL_HAT_RIGHT
                        || event.jhat.value == SDL_HAT_RIGHTDOWN
                        )
                        input.right = 1;
                    else input.right = 0;


                    if ( event.jhat.value == SDL_HAT_DOWN )
                        input.down= 1;
                    else input.down = 0;

                    if ( event.jhat.value == SDL_HAT_UP )
                        input.up = 1;
                    else input.up = 0;
            }

	}

}


void loadSong( int songnum )
{
    char ch1[30] = "sons/musique";
    char ch2[10] = "";
#ifdef GP2X
    sprintf (ch2, "%d.oga", songnum);
#else
    sprintf (ch2, "%d.mp3", songnum);
#endif

 /* On libère la chanson précédente s'il y en a une */
 freeMusic();

 /* On charge la nouvelle chanson */
 musiqueJouee = Mix_LoadMUS( strcat(ch1, ch2) );
 if (musiqueJouee == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

 /* On active la répétition de la musique à l'infini et on la joue */
 Mix_PlayMusic(musiqueJouee, -1);
}


void pauseSong (void)
{

  if (Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();

}


void freeMusic(void)
{

 /* On libère la chanson */
 if ( musiqueJouee != NULL )
 {
    Mix_HaltMusic();
    Mix_FreeMusic(musiqueJouee);
    musiqueJouee = NULL;
 }

}

