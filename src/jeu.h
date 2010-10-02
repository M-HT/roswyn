
#ifndef DEF_JEU
#define DEF_JEU

    void FlipScreen(void);
    void ClearScreen(void);
    void BlitSprite(SDL_Surface *src, SDL_Surface *dst, SDL_Rect *dstrect);

    int AfficheNiveau(SDL_Rect position, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR], int level );
    int DeplacePlayer ( int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] );
    int DeplaceEnnemi ( int ennemi, int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] );
    int DeplaceBoss (int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] );
    int DeplaceFireball (int fireball, int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] );
    int DeplaceBaton (int deplacement, int x, SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] );
    int laisseItem (int ennemi);
    int AfficheTexteItems (SDL_Surface *ecran, TTF_Font *police, char Chaine[12], SDL_Rect position);
    int AfficheDialogues (SDL_Surface *ecran, TTF_Font *police, int dialogue);
    int title ( SDL_Surface *ecran, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton );
    void game_over ( SDL_Surface *ecran, int *coeur, int *continuer, int *potion, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton );
    int credits ( SDL_Surface *ecran );
    int shop ( SDL_Surface *ecran, TTF_Font *police, int *potion, int *coeur, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton );
    void fin ( SDL_Surface *ecran, int *continuer );
    void loadSavedGame(int *coeur, int *potion, int *coeurmax, int *money, int *level, int *power, int *boss, int *key, int *baton);
    SDL_Surface *loadImage(char *name);
    SDL_Surface *loadFullScreenImage(char *name);
    SDL_Surface *loadScreenImage(char *name);
    void loadTileset(void);
    void freeTileset(void);
    int pauseGame(void);
    void delay(unsigned int frameLimit);
    void getInput(void);
    void getJoystick(void);
    void drawString(char *text, int x, int y, TTF_Font *font);
    void freeMusic(void);
    void pauseSong (void);
    void loadSong( int songnum );




#endif

