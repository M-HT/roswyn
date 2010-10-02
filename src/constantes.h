
#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_BLOC         35 // Taille d'un bloc (carré) en pixels
    #define TAILLE_MARIO        34 // Taille de Mario en pixels
    #define NB_BLOCS_LARGEUR    12
    #define NB_BLOCS_HAUTEUR    12
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     (TAILLE_BLOC * NB_BLOCS_HAUTEUR) + 40

    #define TRANS_R 255
    #define TRANS_G 0
    #define TRANS_B 255

#ifdef GP2X
    #define TILE_WIDTH 26
    #define TILE_HEIGHT 18
    #define TILE_START_X 4
    #define TILE_START_Y 2

    #define TEXT_SIZE 10

    #define POSITION_HORIZONTAL(x) ((((x) * TILE_WIDTH) / TAILLE_BLOC) + TILE_START_X)
    #define POSITION_VERTICAL(y) ((((y) * TILE_HEIGHT) / TAILLE_BLOC) + TILE_START_Y)
#else
    #define TILE_WIDTH TAILLE_BLOC
    #define TILE_HEIGHT TAILLE_BLOC
    #define TILE_START_X 0
    #define TILE_START_Y 0

    #define TEXT_SIZE 14

    #define POSITION_HORIZONTAL(x) (x)
    #define POSITION_VERTICAL(y) (y)
#endif

    enum {HAUT, BAS, GAUCHE, DROITE, HAUT2, BAS2, GAUCHE2, DROITE2, EPEEBAS, EPEEHAUT, EPEEDROITE, EPEEGAUCHE, EPEEBAS2, EPEEHAUT2, EPEEDROITE2, EPEEGAUCHE2 };

    typedef struct Item Item;
    struct Item
    {
        int itemExiste; //bool : 0= non, 1= oui
        int itemType; // 0= rien, 1 = coeur
        SDL_Rect positionItem;
    };


    typedef struct Input
    {
	int left, right, up, down, jump, attack, enter, erase, pause, timer, un, deux, trois, escape, quit;
    } Input;



#endif
