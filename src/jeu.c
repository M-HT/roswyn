
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <fmod.h>
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

    extern FSOUND_STREAM *musiqueJouee;





   int AfficheNiveau(SDL_Rect position, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int level )

    {
    //Variables de decor
    int i = 0, j = 0;


    //Pour animer les tiles
        if (tempsTiles + 500 < SDL_GetTicks()) {
                tempsTiles = SDL_GetTicks();
                if (animTiles == 1) animTiles = 2;
                else if (animTiles == 2) animTiles = 1;
                }

if (animTiles == 1)
{
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case 1:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 2:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 3:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 4:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 5:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 6:
                        if ( tileSet == 8) {
                            if ( boss >= 1 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 7:
                        if ( tileSet == 8) {
                            if ( boss >= 2 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 8:
                        if ( tileSet == 8) {
                            if ( boss >= 3 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 9:
                        if ( tileSet == 8) {
                            if ( boss >= 4 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 10:
                        if ( tileSet == 8) {
                            if ( boss >= 5 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 11:
                        if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[24], NULL, ecran, &position);
                            carte[i][j] = 25; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 6 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 12:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[25], NULL, ecran, &position);
                            carte[i][j] = 26; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 7 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 13:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[26], NULL, ecran, &position);
                            carte[i][j] = 27; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 8 ) { SDL_BlitSurface(mapImages[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 14:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[27], NULL, ecran, &position);
                            carte[i][j] = 28; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 15:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[28], NULL, ecran, &position);
                            carte[i][j] = 29; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 16:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[29], NULL, ecran, &position);
                            carte[i][j] = 30; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 17:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[30], NULL, ecran, &position);
                            carte[i][j] = 31; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 18:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages[31], NULL, ecran, &position);
                            carte[i][j] = 32; }
                            else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 19:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 20:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 21:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 22:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 23:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 24:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 25:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 26:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 27:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 28:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 29:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 30:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 31:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 32:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 33:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 34:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 35:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 36:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 37:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 38:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 39:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 40:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 41:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 42:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 43:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 44:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 45:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 46:
                        if ( ValeurCoffre( level ) == 1 ) SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        else SDL_BlitSurface(mapImages[carte[i][j]], NULL, ecran, &position);
                        break;
                    case 47:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 48:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 49:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 50:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 51:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 52:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 53:
                        SDL_BlitSurface(mapImages[carte[i][j]-1], NULL, ecran, &position);
                        break;

                }
            }
        }

}

else if ( animTiles == 2 )
{
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case 1:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 2:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 3:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 4:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 5:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 6:
                        if ( tileSet == 8) {
                            if ( boss >= 1 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 7:
                        if ( tileSet == 8) {
                            if ( boss >= 2 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 8:
                        if ( tileSet == 8) {
                            if ( boss >= 3 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 9:
                        if ( tileSet == 8) {
                            if ( boss >= 4 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 10:
                        if ( tileSet == 8) {
                            if ( boss >= 5 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 11:
                        if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[24], NULL, ecran, &position);
                            carte[i][j] = 25; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 6 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 12:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[25], NULL, ecran, &position);
                            carte[i][j] = 26; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 7 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 13:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[26], NULL, ecran, &position);
                            carte[i][j] = 27; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else if ( tileSet == 8) {
                            if ( boss >= 8 ) { SDL_BlitSurface(mapImages2[20], NULL, ecran, &position);
                            carte[i][j] = 21; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 14:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[27], NULL, ecran, &position);
                            carte[i][j] = 28; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 15:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[28], NULL, ecran, &position);
                            carte[i][j] = 29; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 16:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[29], NULL, ecran, &position);
                            carte[i][j] = 30; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 17:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[30], NULL, ecran, &position);
                            carte[i][j] = 31; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 18:
                         if ( tileSet == 2 || tileSet == 9 ) {
                            if ( ValeurSwitch ( level ) == 0 ) { SDL_BlitSurface(mapImages2[31], NULL, ecran, &position);
                            carte[i][j] = 32; }
                            else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position); }
                        else SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 19:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 20:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 21:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 22:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 23:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 24:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 25:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 26:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 27:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 28:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 29:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 30:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 31:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 32:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 33:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 34:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 35:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 36:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 37:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 38:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 39:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 40:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 41:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 42:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 43:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 44:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 45:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 46:
                        if ( ValeurCoffre( level ) == 1 ) SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        else SDL_BlitSurface(mapImages2[carte[i][j]], NULL, ecran, &position);
                        break;
                    case 47:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 48:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 49:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 50:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 51:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 52:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;
                    case 53:
                        SDL_BlitSurface(mapImages2[carte[i][j]-1], NULL, ecran, &position);
                        break;

                }
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
                            if (positionMario.y >= ecran->h - 80) break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionMario.y += x; break;


                        case DROITE:
                            if (positionMario.x >= ecran->w - 40) break;
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
    SDL_Rect positionEnnemi;

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
                            if (positionEnnemi.y >= ecran->h - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= ecran->w - 35) break;
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
                            if (positionEnnemi.y >= ecran->h - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC]     [(positionEnnemi.y) / TAILLE_BLOC + 3] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 3] [(positionEnnemi.y) / TAILLE_BLOC + 3] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC]     [(positionEnnemi.y) / TAILLE_BLOC + 3] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 3] [(positionEnnemi.y) / TAILLE_BLOC + 3] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= ecran->w - 35) break;
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

SDL_Rect positionEnnemi;

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
                            if (positionEnnemi.y >= ecran->h - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= ecran->w - 35) break;
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
                            if (positionEnnemi.y >= ecran->h - 80) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] <= 20) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            if (carte[positionEnnemi.x / TAILLE_BLOC + 1] [(positionEnnemi.y + 2) / TAILLE_BLOC + 1] >= 46) break;
                            positionEnnemi.y += x; break;


                        case DROITE:
                            if (positionEnnemi.x >= ecran->w - 35) break;
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
        SDL_BlitSurface(texte, NULL, ecran, &position);


    //On libere la memoire sinon elle gonfle
        SDL_FreeSurface(texte);




return 0;

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
   fgets(chaine1, 55, fichier);
   chaine1[strlen(chaine1) - 1] = '\0';
   fgets(chaine2, 55, fichier);
   chaine2[strlen(chaine2) - 1] = '\0';
   fgets(chaine3, 55, fichier);
   chaine3[strlen(chaine3) - 1] = '\0';
   fgets(chaine4, 55, fichier);
   chaine4[strlen(chaine4) - 1] = '\0';

   SDL_Surface *texte1 = NULL, *texte2 = NULL, *texte3 = NULL, *texte4 = NULL,*fond = NULL;
   fond = loadImage("fond/dialog.bmp");
   SDL_BlitSurface(fond, NULL, ecran, &posD);

    texte1 = TTF_RenderText_Blended(police, chaine1, couleurBlanche);
    SDL_BlitSurface(texte1, NULL, ecran, &posT1);
    texte2 = TTF_RenderText_Blended(police, chaine2, couleurBlanche);
    SDL_BlitSurface(texte2, NULL, ecran, &posT2);
    texte3 = TTF_RenderText_Blended(police, chaine3, couleurBlanche);
    SDL_BlitSurface(texte3, NULL, ecran, &posT3);
    texte4 = TTF_RenderText_Blended(police, chaine4, couleurBlanche);
    SDL_BlitSurface(texte4, NULL, ecran, &posT4);

    //On affiche
    SDL_Flip(ecran);

    //SDL_Delay (3000);

    SDL_EnableKeyRepeat(0, 0);

    while (continuer)
{
    SDL_Event event;

    SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                if (tempoTouche + 1000 < SDL_GetTicks()) {
                    continuer = 0;
                    tempoTouche = SDL_GetTicks();
                    event.type=0; }
                else event.type=0;
                break;

            case SDL_JOYBUTTONDOWN:
                    if ( event.jbutton.button == 0 )
                    {
                    if (tempoTouche + 1000 < SDL_GetTicks()) {
                    continuer = 0;
                    tempoTouche = SDL_GetTicks();
                    event.type=0; }
                    else event.type=0;
                    break;
                    }
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
    SDL_EnableKeyRepeat(10, 10);
    return 0 ;
}


void title ( SDL_Surface *ecran, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{

unsigned int frameLimit = SDL_GetTicks() + 16;
int continuer = 1;
FILE* fichier = NULL;
FILE* fSrc = NULL;
FILE* fDest = NULL;
int timer = SDL_GetTicks();
char buffer[512];
int NbLus;
int a = 0, b = 0, c = 0, i = 0, caractereLu = 0;


SDL_Surface *titre = NULL;
titre = loadImage("fond/title.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);

//On affiche
    SDL_Flip(ecran);


    while (continuer)
{

    /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();




    if ( timer + 500 < SDL_GetTicks() )
    {

                    if (input.un)
                    {

                        input.enter = input.un = 0;
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        continuer = 0;

                    }

                    if (input.deux)
                    {

                        input.enter = input.deux = 0;
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        fichier = fopen("save.lvl", "r");
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
            *level = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

        for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeur = (a * 10) + b;
            a = 0; b = 0; c = 0;

             for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeurmax = (a * 10) + b;
            a = 0; b = 0; c = 0;
                             caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *potion = 0;
                    break;
                case '1':
                      *potion = 1;
                    break;
                case '2':
                       *potion = 2;
                    break;
                case '3':
                       *potion = 3;
                    break;
                case '4':
                       *potion = 4;
                    break;
                case '5':
                       *potion = 5;
                    break;
                case '6':
                       *potion = 6;
                    break;
                case '7':
                       *potion = 7;
                    break;
                case '8':
                       *potion = 8;
                    break;
                case '9':
                       *potion = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *power = 0;
                    break;
                case '1':
                      *power = 1;
                    break;
                case '2':
                       *power = 2;
                    break;
                case '3':
                       *power = 3;
                    break;
                case '4':
                       *power = 4;
                    break;
                case '5':
                       *power = 5;
                    break;
                case '6':
                       *power = 6;
                    break;
                case '7':
                       *power = 7;
                    break;
                case '8':
                       *power = 8;
                    break;
                case '9':
                       *power = 9;
                    break;
                           }

                                 caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *boss = 0;
                    break;
                case '1':
                      *boss = 1;
                    break;
                case '2':
                       *boss = 2;
                    break;
                case '3':
                       *boss = 3;
                    break;
                case '4':
                       *boss = 4;
                    break;
                case '5':
                       *boss = 5;
                    break;
                case '6':
                       *boss = 6;
                    break;
                case '7':
                       *boss = 7;
                    break;
                case '8':
                       *boss = 8;
                    break;
                case '9':
                       *boss = 9;
                    break;
                           }

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
            *money = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

                                caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *key = 0;
                    break;
                case '1':
                      *key = 1;
                    break;
                case '2':
                       *key = 2;
                    break;
                case '3':
                       *key = 3;
                    break;
                case '4':
                       *key = 4;
                    break;
                case '5':
                       *key = 5;
                    break;
                case '6':
                       *key = 6;
                    break;
                case '7':
                       *key = 7;
                    break;
                case '8':
                       *key = 8;
                    break;
                case '9':
                       *key = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *baton = 0;
                    break;
                case '1':
                      *baton = 1;
                    break;
                case '2':
                       *baton = 2;
                    break;
                case '3':
                       *baton = 3;
                    break;
                case '4':
                       *baton = 4;
                    break;
                case '5':
                       *baton = 5;
                    break;
                case '6':
                       *baton = 6;
                    break;
                case '7':
                       *baton = 7;
                    break;
                case '8':
                       *baton = 8;
                    break;
                case '9':
                       *baton = 9;
                    break;
                           }
                        fclose(fichier);
                        fSrc = fopen("savecoffres.lvl", "r");
                        fDest = fopen("coffres.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        fSrc = fopen("saveswitchs.lvl", "r");
                        fDest = fopen("switchs.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        continuer = 0;
                    }

                       if (input.trois)
                    {

                        input.enter = input.trois = 0;
                        input.timer = SDL_GetTicks();
                        SDL_FreeSurface(titre);
                        continuer = 0;
                        credits( ecran, potion, coeur, coeurmax, money, level, power, boss, key, baton );
                    }

        input.timer = SDL_GetTicks();

        }

        delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;

    }

SDL_FreeSurface(titre);


}


void game_over ( SDL_Surface *ecran, int *coeur, int *continuer, int *potion, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{
int continuer2 = 1;
SDL_Event event;
FILE* fichier = NULL;
FILE* fSrc = NULL;
FILE* fDest = NULL;
char buffer[512];
int NbLus;
int a = 0, b = 0, c = 0, i = 0, caractereLu = 0;

SDL_Surface *titre = NULL;
titre = loadImage("fond/gameover.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);

//On affiche
    SDL_Flip(ecran);


    while (continuer2)
{


    SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {
                        case SDLK_KP1:
                        fichier = fopen("save.lvl", "r");
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
            *level = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

        for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeur = (a * 10) + b;
            a = 0; b = 0; c = 0;

             for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeurmax = (a * 10) + b;
            a = 0; b = 0; c = 0;
                             caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *potion = 0;
                    break;
                case '1':
                      *potion = 1;
                    break;
                case '2':
                       *potion = 2;
                    break;
                case '3':
                       *potion = 3;
                    break;
                case '4':
                       *potion = 4;
                    break;
                case '5':
                       *potion = 5;
                    break;
                case '6':
                       *potion = 6;
                    break;
                case '7':
                       *potion = 7;
                    break;
                case '8':
                       *potion = 8;
                    break;
                case '9':
                       *potion = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *power = 0;
                    break;
                case '1':
                      *power = 1;
                    break;
                case '2':
                       *power = 2;
                    break;
                case '3':
                       *power = 3;
                    break;
                case '4':
                       *power = 4;
                    break;
                case '5':
                       *power = 5;
                    break;
                case '6':
                       *power = 6;
                    break;
                case '7':
                       *power = 7;
                    break;
                case '8':
                       *power = 8;
                    break;
                case '9':
                       *power = 9;
                    break;
                           }

                                 caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *boss = 0;
                    break;
                case '1':
                      *boss = 1;
                    break;
                case '2':
                       *boss = 2;
                    break;
                case '3':
                       *boss = 3;
                    break;
                case '4':
                       *boss = 4;
                    break;
                case '5':
                       *boss = 5;
                    break;
                case '6':
                       *boss = 6;
                    break;
                case '7':
                       *boss = 7;
                    break;
                case '8':
                       *boss = 8;
                    break;
                case '9':
                       *boss = 9;
                    break;
                           }

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
            *money = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

                                caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *key = 0;
                    break;
                case '1':
                      *key = 1;
                    break;
                case '2':
                       *key = 2;
                    break;
                case '3':
                       *key = 3;
                    break;
                case '4':
                       *key = 4;
                    break;
                case '5':
                       *key = 5;
                    break;
                case '6':
                       *key = 6;
                    break;
                case '7':
                       *key = 7;
                    break;
                case '8':
                       *key = 8;
                    break;
                case '9':
                       *key = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *baton = 0;
                    break;
                case '1':
                      *baton = 1;
                    break;
                case '2':
                       *baton = 2;
                    break;
                case '3':
                       *baton = 3;
                    break;
                case '4':
                       *baton = 4;
                    break;
                case '5':
                       *baton = 5;
                    break;
                case '6':
                       *baton = 6;
                    break;
                case '7':
                       *baton = 7;
                    break;
                case '8':
                       *baton = 8;
                    break;
                case '9':
                       *baton = 9;
                    break;
                           }
                        fclose(fichier);
                        fSrc = fopen("savecoffres.lvl", "r");
                        fDest = fopen("coffres.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        fSrc = fopen("saveswitchs.lvl", "r");
                        fDest = fopen("switchs.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        continuer2 = 0;
                        break;

                        case SDLK_1:
                        fichier = fopen("save.lvl", "r");
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
            *level = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

        for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeur = (a * 10) + b;
            a = 0; b = 0; c = 0;

             for (i = 1 ; i < 3 ; i++) {
       caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                       if (i == 1) a = 0;
                       if (i == 2) b = 0;

                    break;
                case '1':
                       if (i == 1) a = 1;
                       if (i == 2) b = 1;

                    break;
                case '2':
                       if (i == 1) a = 2;
                       if (i == 2) b = 2;

                    break;
                case '3':
                       if (i == 1) a = 3;
                       if (i == 2) b = 3;

                    break;
                case '4':
                       if (i == 1) a = 4;
                       if (i == 2) b = 4;

                    break;
                case '5':
                       if (i == 1) a = 5;
                       if (i == 2) b = 5;

                    break;
                case '6':
                       if (i == 1) a = 6;
                       if (i == 2) b = 6;

                    break;
                case '7':
                       if (i == 1) a = 7;
                       if (i == 2) b = 7;

                    break;
                case '8':
                       if (i == 1) a = 8;
                       if (i == 2) b = 8;

                    break;
                case '9':
                       if (i == 1) a = 9;
                       if (i == 2) b = 9;

                    break;
                           } }
            *coeurmax = (a * 10) + b;
            a = 0; b = 0; c = 0;
                             caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *potion = 0;
                    break;
                case '1':
                      *potion = 1;
                    break;
                case '2':
                       *potion = 2;
                    break;
                case '3':
                       *potion = 3;
                    break;
                case '4':
                       *potion = 4;
                    break;
                case '5':
                       *potion = 5;
                    break;
                case '6':
                       *potion = 6;
                    break;
                case '7':
                       *potion = 7;
                    break;
                case '8':
                       *potion = 8;
                    break;
                case '9':
                       *potion = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *power = 0;
                    break;
                case '1':
                      *power = 1;
                    break;
                case '2':
                       *power = 2;
                    break;
                case '3':
                       *power = 3;
                    break;
                case '4':
                       *power = 4;
                    break;
                case '5':
                       *power = 5;
                    break;
                case '6':
                       *power = 6;
                    break;
                case '7':
                       *power = 7;
                    break;
                case '8':
                       *power = 8;
                    break;
                case '9':
                       *power = 9;
                    break;
                           }

                                 caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *boss = 0;
                    break;
                case '1':
                      *boss = 1;
                    break;
                case '2':
                       *boss = 2;
                    break;
                case '3':
                       *boss = 3;
                    break;
                case '4':
                       *boss = 4;
                    break;
                case '5':
                       *boss = 5;
                    break;
                case '6':
                       *boss = 6;
                    break;
                case '7':
                       *boss = 7;
                    break;
                case '8':
                       *boss = 8;
                    break;
                case '9':
                       *boss = 9;
                    break;
                           }

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
            *money = (a * 100) + (b * 10) + c;
            a = 0; b = 0; c = 0;

                                caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *key = 0;
                    break;
                case '1':
                      *key = 1;
                    break;
                case '2':
                       *key = 2;
                    break;
                case '3':
                       *key = 3;
                    break;
                case '4':
                       *key = 4;
                    break;
                case '5':
                       *key = 5;
                    break;
                case '6':
                       *key = 6;
                    break;
                case '7':
                       *key = 7;
                    break;
                case '8':
                       *key = 8;
                    break;
                case '9':
                       *key = 9;
                    break;
                           }

                               caractereLu = fgetc(fichier);
       switch (caractereLu)
            {
                case '0':
                      *baton = 0;
                    break;
                case '1':
                      *baton = 1;
                    break;
                case '2':
                       *baton = 2;
                    break;
                case '3':
                       *baton = 3;
                    break;
                case '4':
                       *baton = 4;
                    break;
                case '5':
                       *baton = 5;
                    break;
                case '6':
                       *baton = 6;
                    break;
                case '7':
                       *baton = 7;
                    break;
                case '8':
                       *baton = 8;
                    break;
                case '9':
                       *baton = 9;
                    break;
                           }
                        fclose(fichier);
                        fSrc = fopen("savecoffres.lvl", "r");
                        fDest = fopen("coffres.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        fSrc = fopen("saveswitchs.lvl", "r");
                        fDest = fopen("switchs.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        continuer2 = 0;
                        break;

                        case SDLK_KP2:
                        *continuer = 0;
                        continuer2 = 0;
                        break;

                        case SDLK_2:
                        *continuer = 0;
                        continuer2 = 0;
                        break;

                        case SDLK_KP3:
                        *coeur = 5;
                        continuer2 = 0;
                        break;

                        case SDLK_3:
                        *coeur = 5;
                        continuer2 = 0;
                        break;


                        default:
                        break;


                        }
            break;
        }


    }

SDL_FreeSurface( titre );


}


void credits ( SDL_Surface *ecran, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go = 1;
    int timer = SDL_GetTicks();
    SDL_Surface *titre = NULL;
    titre = loadImage("fond/credits.jpg");

    SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

    SDL_BlitSurface(titre, NULL, ecran, &pos);

    SDL_Flip(ecran);

    while (go)
    {

        /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();

        if ( timer + 500 < SDL_GetTicks() )
        {
            if (input.enter)
                {
                    input.enter = input.pause = 0;
                    input.timer = SDL_GetTicks();
                    go = 0;
                    SDL_FreeSurface(titre);
                    title( ecran, potion, coeur, coeurmax, money, level, power, boss, key, baton );
                }

        }

        delay(frameLimit);

		frameLimit = SDL_GetTicks() + 16;
    }


}


void shop ( SDL_Surface *ecran, TTF_Font *police, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton )
{
int continuer2 = 1;
SDL_Event event;
FILE* fichier = NULL;
FILE* fSrc = NULL;
FILE* fDest = NULL;
char buffer[512];
int NbLus;


SDL_Surface *shop = NULL;
shop = loadImage("fond/shop.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(shop, NULL, ecran, &pos);

//On affiche
    SDL_Flip(ecran);


    while (continuer2)
{


    SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {
                        case SDLK_KP1:
                        if (*money >= 30) { *money -= 30; *coeur=*coeurmax; AfficheDialogues (ecran, police, 988); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_1:
                        if (*money >= 30) { *money -= 30; *coeur=*coeurmax; AfficheDialogues (ecran, police, 988); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_KP2:
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
                        fSrc = fopen("coffres.lvl", "r");
                        fDest = fopen("savecoffres.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        fSrc = fopen("switchs.lvl", "r");
                        fDest = fopen("saveswitchs.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        continuer2 = 0;
                        break;

                        case SDLK_2:
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
                        fSrc = fopen("coffres.lvl", "r");
                        fDest = fopen("savecoffres.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        fSrc = fopen("switchs.lvl", "r");
                        fDest = fopen("saveswitchs.lvl", "w+");
                        while ((NbLus = fread(buffer, 1, 512, fSrc)) != 0)
                        fwrite(buffer, 1, NbLus, fDest);
                        fclose(fDest);
                        fclose(fSrc);
                        continuer2 = 0;
                        break;

                        case SDLK_KP3:
                        if (*money >= 100) { *money -= 100; *potion+= 1; AfficheDialogues (ecran, police, 986); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_3:
                        if (*money >= 100) { *money -= 100; *potion+= 1; AfficheDialogues (ecran, police, 986); }
                        else AfficheDialogues (ecran, police, 987);
                        continuer2 = 0;
                        break;

                        case SDLK_SPACE:
                        continuer2 = 0;
                        break;

                        case SDLK_RETURN:
                        continuer2 = 0;
                        break;

                        default:
                            break;



                        }
            break;

            case SDL_JOYBUTTONDOWN:
                    if ( event.jbutton.button == 0 )
                    {
                    continuer2 = 0;
                    break;
                    }
        }


    }

SDL_FreeSurface( shop );


}


void fin ( SDL_Surface *ecran, int *continuer )
{
int continuer2 = 1;
SDL_Event event;

SDL_Surface *titre = NULL;
titre = loadImage("fond/fin.jpg");

SDL_Rect pos;
       pos.x = 0;
       pos.y = 0;

SDL_BlitSurface(titre, NULL, ecran, &pos);

//On affiche
    SDL_Flip(ecran);


    while (continuer2)
{


    SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                 switch(event.key.keysym.sym)
                        {

                        case SDLK_ESCAPE:
                        *continuer = 0;
                        continuer2 = 0;
                        break;

                        case SDLK_RETURN:
                        *continuer = 0;
                        continuer2 = 0;
                        break;

                        case SDLK_SPACE:
                        *continuer = 0;
                        continuer2 = 0;
                        break;


                        default:
                        break;


                        }
            break;
        }


    }

SDL_FreeSurface( titre );


}


/* Nouvelles fonctions avril 2010 - mise à niveau */

/* Charge les images pour un blit plus rapide */
SDL_Surface *loadImage(char *name)
{
	/* Charge les images avec SDL Image */

	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;

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
    mapImages[0] = loadImage(strcat(loadAdress, "B1.bmp"));
    //on remet loadAdress a sa valeur initiale :
    strcpy(loadAdress, adressSave);
    mapImages[1] = loadImage(strcat(loadAdress, "B2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[2] = loadImage(strcat(loadAdress, "B3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[3] = loadImage(strcat(loadAdress, "B4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[4] = loadImage(strcat(loadAdress, "B5.bmp")); strcpy(loadAdress, adressSave);
    mapImages[5] = loadImage(strcat(loadAdress, "B6.bmp")); strcpy(loadAdress, adressSave);
    mapImages[6] = loadImage(strcat(loadAdress, "B7.bmp")); strcpy(loadAdress, adressSave);
    mapImages[7] = loadImage(strcat(loadAdress, "B8.bmp")); strcpy(loadAdress, adressSave);
    mapImages[8] = loadImage(strcat(loadAdress, "B9.bmp")); strcpy(loadAdress, adressSave);
    mapImages[9] = loadImage(strcat(loadAdress, "B10.bmp")); strcpy(loadAdress, adressSave);
    mapImages[10] = loadImage(strcat(loadAdress, "B11.bmp")); strcpy(loadAdress, adressSave);
    mapImages[11] = loadImage(strcat(loadAdress, "B12.bmp")); strcpy(loadAdress, adressSave);
    mapImages[12] = loadImage(strcat(loadAdress, "B13.bmp")); strcpy(loadAdress, adressSave);
    mapImages[13] = loadImage(strcat(loadAdress, "B14.bmp")); strcpy(loadAdress, adressSave);
    mapImages[14] = loadImage(strcat(loadAdress, "B15.bmp")); strcpy(loadAdress, adressSave);
    mapImages[15] = loadImage(strcat(loadAdress, "B16.bmp")); strcpy(loadAdress, adressSave);
    mapImages[16] = loadImage(strcat(loadAdress, "B17.bmp")); strcpy(loadAdress, adressSave);
    mapImages[17] = loadImage(strcat(loadAdress, "B18.bmp")); strcpy(loadAdress, adressSave);
    mapImages[18] = loadImage(strcat(loadAdress, "B19.bmp")); strcpy(loadAdress, adressSave);
    mapImages[19] = loadImage(strcat(loadAdress, "B20.bmp")); strcpy(loadAdress, adressSave);

    //Traversables :
    mapImages[20] = loadImage(strcat(loadAdress, "T1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[21] = loadImage(strcat(loadAdress, "T2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[22] = loadImage(strcat(loadAdress, "T3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[23] = loadImage(strcat(loadAdress, "T4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[24] = loadImage(strcat(loadAdress, "T5.bmp")); strcpy(loadAdress, adressSave);
    mapImages[25] = loadImage(strcat(loadAdress, "T6.bmp")); strcpy(loadAdress, adressSave);
    mapImages[26] = loadImage(strcat(loadAdress, "T7.bmp")); strcpy(loadAdress, adressSave);
    mapImages[27] = loadImage(strcat(loadAdress, "T8.bmp")); strcpy(loadAdress, adressSave);
    mapImages[28] = loadImage(strcat(loadAdress, "T9.bmp")); strcpy(loadAdress, adressSave);
    mapImages[29] = loadImage(strcat(loadAdress, "T10.bmp")); strcpy(loadAdress, adressSave);
    mapImages[30] = loadImage(strcat(loadAdress, "T11.bmp")); strcpy(loadAdress, adressSave);
    mapImages[31] = loadImage(strcat(loadAdress, "T12.bmp")); strcpy(loadAdress, adressSave);
    mapImages[32] = loadImage(strcat(loadAdress, "T13.bmp")); strcpy(loadAdress, adressSave);
    mapImages[33] = loadImage(strcat(loadAdress, "T14.bmp")); strcpy(loadAdress, adressSave);
    mapImages[34] = loadImage(strcat(loadAdress, "T15.bmp")); strcpy(loadAdress, adressSave);
    mapImages[35] = loadImage(strcat(loadAdress, "T16.bmp")); strcpy(loadAdress, adressSave);
    mapImages[36] = loadImage(strcat(loadAdress, "T17.bmp")); strcpy(loadAdress, adressSave);
    mapImages[37] = loadImage(strcat(loadAdress, "T18.bmp")); strcpy(loadAdress, adressSave);
    mapImages[38] = loadImage(strcat(loadAdress, "T19.bmp")); strcpy(loadAdress, adressSave);
    mapImages[39] = loadImage(strcat(loadAdress, "T20.bmp")); strcpy(loadAdress, adressSave);
    mapImages[40] = loadImage(strcat(loadAdress, "T21.bmp")); strcpy(loadAdress, adressSave);
    mapImages[41] = loadImage(strcat(loadAdress, "T22.bmp")); strcpy(loadAdress, adressSave);
    mapImages[42] = loadImage(strcat(loadAdress, "T23.bmp")); strcpy(loadAdress, adressSave);
    mapImages[43] = loadImage(strcat(loadAdress, "T24.bmp")); strcpy(loadAdress, adressSave);
    mapImages[44] = loadImage(strcat(loadAdress, "T25.bmp")); strcpy(loadAdress, adressSave);

    //5 tiles speciales (coffres etc.. : 46 à 50) :
    mapImages[45] = loadImage(strcat(loadAdress, "S1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[46] = loadImage(strcat(loadAdress, "S2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[47] = loadImage(strcat(loadAdress, "S3.bmp")); strcpy(loadAdress, adressSave);
    mapImages[48] = loadImage(strcat(loadAdress, "S4.bmp")); strcpy(loadAdress, adressSave);
    mapImages[49] = loadImage(strcat(loadAdress, "S5.bmp")); strcpy(loadAdress, adressSave);

    //3 tiles tueuses:
    mapImages[50] = loadImage(strcat(loadAdress, "H1.bmp")); strcpy(loadAdress, adressSave);
    mapImages[51] = loadImage(strcat(loadAdress, "H2.bmp")); strcpy(loadAdress, adressSave);
    mapImages[52] = loadImage(strcat(loadAdress, "H3.bmp"));

    //---------------------------------------------------------

    strcpy(loadAdress, adressSave2);
    strcat(loadAdress, "2/");

   //on copie une sauvegarde de loadAdress dans adressSave
   strcpy(adressSave, loadAdress);

    //Chargement des tiles du 2eme tileset
    //Non traversables : <= 20 pour le test de deplacement
    mapImages2[0] = loadImage(strcat(loadAdress, "B1.bmp"));
    //on remet loadAdress a sa valeur initiale :
    strcpy(loadAdress, adressSave);
    mapImages2[1] = loadImage(strcat(loadAdress, "B2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[2] = loadImage(strcat(loadAdress, "B3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[3] = loadImage(strcat(loadAdress, "B4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[4] = loadImage(strcat(loadAdress, "B5.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[5] = loadImage(strcat(loadAdress, "B6.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[6] = loadImage(strcat(loadAdress, "B7.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[7] = loadImage(strcat(loadAdress, "B8.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[8] = loadImage(strcat(loadAdress, "B9.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[9] = loadImage(strcat(loadAdress, "B10.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[10] = loadImage(strcat(loadAdress, "B11.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[11] = loadImage(strcat(loadAdress, "B12.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[12] = loadImage(strcat(loadAdress, "B13.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[13] = loadImage(strcat(loadAdress, "B14.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[14] = loadImage(strcat(loadAdress, "B15.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[15] = loadImage(strcat(loadAdress, "B16.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[16] = loadImage(strcat(loadAdress, "B17.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[17] = loadImage(strcat(loadAdress, "B18.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[18] = loadImage(strcat(loadAdress, "B19.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[19] = loadImage(strcat(loadAdress, "B20.bmp")); strcpy(loadAdress, adressSave);

    //Traversables :
    mapImages2[20] = loadImage(strcat(loadAdress, "T1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[21] = loadImage(strcat(loadAdress, "T2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[22] = loadImage(strcat(loadAdress, "T3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[23] = loadImage(strcat(loadAdress, "T4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[24] = loadImage(strcat(loadAdress, "T5.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[25] = loadImage(strcat(loadAdress, "T6.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[26] = loadImage(strcat(loadAdress, "T7.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[27] = loadImage(strcat(loadAdress, "T8.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[28] = loadImage(strcat(loadAdress, "T9.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[29] = loadImage(strcat(loadAdress, "T10.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[30] = loadImage(strcat(loadAdress, "T11.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[31] = loadImage(strcat(loadAdress, "T12.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[32] = loadImage(strcat(loadAdress, "T13.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[33] = loadImage(strcat(loadAdress, "T14.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[34] = loadImage(strcat(loadAdress, "T15.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[35] = loadImage(strcat(loadAdress, "T16.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[36] = loadImage(strcat(loadAdress, "T17.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[37] = loadImage(strcat(loadAdress, "T18.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[38] = loadImage(strcat(loadAdress, "T19.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[39] = loadImage(strcat(loadAdress, "T20.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[40] = loadImage(strcat(loadAdress, "T21.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[41] = loadImage(strcat(loadAdress, "T22.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[42] = loadImage(strcat(loadAdress, "T23.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[43] = loadImage(strcat(loadAdress, "T24.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[44] = loadImage(strcat(loadAdress, "T25.bmp")); strcpy(loadAdress, adressSave);

    //5 tiles speciales (coffres etc.. : 46 à 50) :
    mapImages2[45] = loadImage(strcat(loadAdress, "S1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[46] = loadImage(strcat(loadAdress, "S2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[47] = loadImage(strcat(loadAdress, "S3.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[48] = loadImage(strcat(loadAdress, "S4.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[49] = loadImage(strcat(loadAdress, "S5.bmp")); strcpy(loadAdress, adressSave);

    //3 tiles tueuses:
    mapImages2[50] = loadImage(strcat(loadAdress, "H1.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[51] = loadImage(strcat(loadAdress, "H2.bmp")); strcpy(loadAdress, adressSave);
    mapImages2[52] = loadImage(strcat(loadAdress, "H3.bmp"));

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


void pause(void)
{

    unsigned int frameLimit = SDL_GetTicks() + 16;
    int go = 1;
    int timer = SDL_GetTicks();
    char text[70];

    sprintf(text, "** PAUSE **");
    drawString(text, 165, 200, police);
    SDL_Flip( ecran );
    pauseSong();

    while (go)
    {



        /* Keymapping des touches concernées et gestion du joystick */
        if ( joystick != NULL ) getJoystick();
        else getInput();

        if ( timer + 500 < SDL_GetTicks() )
        {
            if (input.enter)
                {
                    input.enter = input.pause = 0;
                    input.timer = SDL_GetTicks();
                    pauseSong();
                    go = 0;
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

	SDL_BlitSurface(surface, NULL, ecran, &dest);

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
						input.enter = 1;
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
						input.enter = 0;
					break;

					default:
					break;
				}
			break;




	}
}
}

void getJoystick()
{
	SDL_Event event;

	/* Loop through waiting messages and process them */

	while (SDL_PollEvent(&event))
	{


			if ( event.type == SDL_KEYDOWN )
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
						input.enter = 1;
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


void loadSong( char filename[200] )
{

 /* On libère la chanson précédente s'il y en a une */
 if ( musiqueJouee != NULL )
    FSOUND_Stream_Close(musiqueJouee);

 /* On charge la nouvelle chanson */
 musiqueJouee = FSOUND_Stream_Open( filename , FSOUND_LOOP_NORMAL, 0, 0);
 if (musiqueJouee == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

 /* On active la répétition de la musique à l'infini et on la joue */
 FSOUND_Stream_SetLoopCount(musiqueJouee, -1);
 FSOUND_Stream_Play(1, musiqueJouee);

}


void pauseSong (void)
{

  if (FSOUND_GetPaused(1))
    FSOUND_SetPaused(1, 0);
  else
    FSOUND_SetPaused(1, 1);

}


void freeMusic(void)
{

 /* On libère la chanson */
 if ( musiqueJouee != NULL )
    FSOUND_Stream_Close(musiqueJouee);

}

