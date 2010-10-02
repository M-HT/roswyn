
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "constantes.h"
#include "fichiers.h"
#include "jeu.h"



//Variables globales (nombreuses) pour la gestion des persos et des ennemis
//****ennemi1****
    int ennemi1vivant = 0, ennemi1life = 0; // var ennemi1 vivant ?
    SDL_Rect positionEnnemi1;
//****ennemi2****
    int ennemi2vivant = 0, ennemi2life = 0; // var ennemi1 vivant ?
    SDL_Rect positionEnnemi2;
//****ennemi3****
    int ennemi3vivant = 0, ennemi3life = 0; // var ennemi1 vivant ?
    SDL_Rect positionEnnemi3;
//****ennemi4****
    int ennemi4vivant = 0, ennemi4life = 0; // var ennemi1 vivant ?
    SDL_Rect positionEnnemi4;
//****ennemi5****
    int ennemi5vivant = 0, ennemi5life = 0; // var ennemi1 vivant ?
    SDL_Rect positionEnnemi5;
//****PNJ1****
    int pnj1vivant = 0, pnj1action = 0;
    SDL_Rect positionPnj1;
//****PNJ2****
    int pnj2vivant = 0, pnj2action = 0;
    SDL_Rect positionPnj2;
//****Boss****
    int bossvivant = 0, bossaction = 0, bosslife = 0;
    SDL_Rect positionBoss;
    int nbfireballs = 0;
    int initFball = 1;
    SDL_Rect positionFireball1;
    SDL_Rect positionFireball2;
    SDL_Rect positionFireball3;
    SDL_Rect positionFireball4;
//****gestion des levels****
    int warpHaut = 0, warpBas = 0, warpDroite = 0, warpGauche = 0;
    int tileSet = 1; //numero du tileset
    int itemLaisse = 1; //types d'objets laisses (0 = rien)
    int musique = 0, musiquedavant = 0;
    int ennemiType = 1;
    int weather = 0;
    int warpZone = 0;
    int wlevel = 1;
    SDL_Rect positionWarp;
    int dialogue1 = 0;
    int dialogue2 = 0;
    int dialogue3 = 0;
    int lswitch = 0; //pour ouvrir un switch dans un level
    int coffre = 1;
    SDL_Rect PositionBaton; //pour le baton de feu
//****Structure pour les items laisses*****
    Item item1 = { 0, 0 };

//Gestion du player
    SDL_Rect positionMario;
    int power = 1; //Puissance de l'epee
    int boss = 0; //Pour savoir quel boss on a tué : 1 = boss 1, 2 = boss 1 + 2, etc.

//Nouveaux tableaux de tiles pour la gestion des niveaux
    SDL_Surface *mapImages[54], *mapImages2[54];
    int tilesetPrecedent;
    Input input;
    SDL_Joystick *joystick = NULL;
    TTF_Font *police = NULL;
    SDL_Surface *ecran = NULL;

    Mix_Music *musiqueJouee = NULL;

    int orig_width = LARGEUR_FENETRE, orig_height = HAUTEUR_FENETRE;


SDL_Rect position;
SDL_Rect positionPluie;
int carte  [NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR]; // Carte du level 12 *12
int level = 1;
SDL_Surface *ennemi1Actuel, *ennemi2Actuel, *ennemi3Actuel, *ennemi4Actuel, *ennemi5Actuel;
SDL_Surface *pnj1Actuel, *pnj2Actuel;
SDL_Surface *fireballActuel, *tempsActuel, *marioActuel;

void DrawScreen1(void)
{
    AfficheNiveau(position, ecran, carte, level);
    if (ennemi1vivant == 1) { BlitSprite(ennemi1Actuel, ecran, &positionEnnemi1); }
    if (ennemi2vivant == 1) { BlitSprite(ennemi2Actuel, ecran, &positionEnnemi2); }
    if (ennemi3vivant == 1) { BlitSprite(ennemi3Actuel, ecran, &positionEnnemi3); }
    if (ennemi4vivant == 1) { BlitSprite(ennemi4Actuel, ecran, &positionEnnemi4); }
    if (ennemi5vivant == 1) { BlitSprite(ennemi5Actuel, ecran, &positionEnnemi5); }
    if (pnj1vivant == 1) { BlitSprite(pnj1Actuel, ecran, &positionPnj1); }
    if (pnj2vivant == 1) { BlitSprite(pnj2Actuel, ecran, &positionPnj2); }
    if (nbfireballs >= 1) { BlitSprite(fireballActuel, ecran, &positionFireball1); }
    if (nbfireballs >= 2) { BlitSprite(fireballActuel, ecran, &positionFireball2); }
    if (nbfireballs >= 3) { BlitSprite(fireballActuel, ecran, &positionFireball3); }
    if (nbfireballs >= 4) { BlitSprite(fireballActuel, ecran, &positionFireball4); }
    if ( weather >= 1 ) BlitSprite(tempsActuel, ecran, &positionPluie);
    BlitSprite(marioActuel, ecran, &positionMario); /* On place mario à sa nouvelle position */
    FlipScreen(); /* On met à jour l'affichage */
}


int main(int argc, char *argv[])
{
//23 dec 09 : on initialise les joysticks
    SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO );

    srand(time(NULL));
    SDL_Surface *mario[16] = {NULL}, *fond = NULL, *coeurRouge = NULL;
    SDL_Event event;
    Uint8 *keystate = SDL_GetKeyState(NULL);
    int continuer = 1, i = 0, j = 0;
    int baton = 0, baton_used = 0, direction_baton = 0;
    SDL_Rect savePositionBaton;
    SDL_Surface *baton_img = NULL;
    int animMario = 1;
    int animMarioEpee = 1;
    int tempsAnim = SDL_GetTicks();  //ennemi1freeze = 1 = pas de mouvement, ennemi1freeze2 = 1 = pas de blessure.
    int tempsSante = SDL_GetTicks();
    tilesetPrecedent = 0;

    memset(&input, 0, sizeof(input));

    //Pour avoir 60 fps
    int fpstime = SDL_GetTicks() + 16;
    int fps = 1; //active/desactive la gestion de 60fps

    //Pour la gestion des touches
    int keytime = SDL_GetTicks();


    //Ennemi 1
    int tempsennemi1 = SDL_GetTicks();
    int ennemi1freeze = 0, ennemi1freeze2 = 0;
    int animEnnemi1 = 1;
    SDL_Surface *ennemi1[8] = {NULL}; //tableau d'anims
    //Ennemi 2
    int tempsennemi2 = SDL_GetTicks();
    int tempsBougeEnnemi2 = SDL_GetTicks();
    int ennemi2freeze = 0, ennemi2freeze2 = 0;
    int animEnnemi2 = 1;
    SDL_Surface *ennemi2[8] = {NULL};
    //Ennemi 3
    int tempsennemi3 = SDL_GetTicks();
    int tempsBougeEnnemi3 = SDL_GetTicks();
    int ennemi3freeze = 0, ennemi3freeze2 = 0;
    int animEnnemi3 = 1;
    SDL_Surface *ennemi3[8] = {NULL};
    //Ennemi 4
    int tempsennemi4 = SDL_GetTicks();
    int tempsBougeEnnemi4 = SDL_GetTicks();
    int ennemi4freeze = 0, ennemi4freeze2 = 0;
    int animEnnemi4 = 1;
    SDL_Surface *ennemi4[8] = {NULL};
    //Ennemi 5
    int tempsennemi5 = SDL_GetTicks();
    int tempsBougeEnnemi5 = SDL_GetTicks();
    int ennemi5freeze = 0, ennemi5freeze2 = 0;
    int animEnnemi5 = 1;
    SDL_Surface *ennemi5[8] = {NULL};
    //BOSS
    int tempsboss = SDL_GetTicks();
    int tempsBougeBoss = SDL_GetTicks();
    int bossfreeze = 0, bossfreeze2 = 0;
    int animBoss = 1;
    int initDeplBoss = 1;
    int collision = 0;
    SDL_Rect savePositionBoss;
    SDL_Surface *bossPic[2] = {NULL}, *bossActuel = NULL;
    //Boule de feu 1
    int animfireball1 = 1;
    int deplFire1X = 1;
    int deplFire1Y = 1;
    int deplFire2X = 1;
    int deplFire2Y = 1;
    int deplFire3X = 1;
    int deplFire3Y = 1;
    int deplFire4X = 1;
    int deplFire4Y = 1;
    SDL_Rect savePositionFireball1;
    SDL_Rect savePositionFireball2;
    SDL_Rect savePositionFireball3;
    SDL_Rect savePositionFireball4;
    SDL_Surface *fireball[2] = {NULL};

    //PNJ1 & 2
    int tempsBougePnj1 = SDL_GetTicks();
   // int tempsBougePnj2 = SDL_GetTicks();
    int animPnj1 = 1;
    SDL_Surface *pnj1[8] = {NULL};
   // int animPnj2 = 1;
    SDL_Surface *pnj2 = NULL;

    int x, y; // pour tester la collision
    int coeur = 5; // nombre de coeurs de vie avant la mort
    int coeurmax = 5;
    int money = 0;
    int key = 0;
    int potion = 0;
    int tempsCoeur = SDL_GetTicks();      //tempo entre deux coups pour ne pas mourir trop vite
    int invincibilite = 0;   //et donc invincibilite temporaire
    int delai = 1;
    int bossArrive = 1;
    int saveWarpHaut = 0, saveWarpBas = 0, saveWarpDroite = 0, saveWarpGauche = 0;
    int open = 0;


    // Génération du nombre aléatoire
    const int MAX = 4, MIN = 1;
    int direction = 0, direction2 = 0, direction3 = 0, direction4 = 0;
    srand(time(NULL));
   // ensuite, utiliser : direction = (rand() % (MAX - MIN + 1)) + MIN;

    //Initialisation des coffres (fichier coffres.lvl)
    InitCoffres();

    //Initialisation des switchs (fichier switchs.lvl)
    InitSwitchs();

    /* Initialisation de FMOD */
#ifdef GP2X
    //Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024);
#else
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
#endif
    Mix_AllocateChannels(16);
#if SDL_VERSIONNUM(SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL) >= SDL_VERSIONNUM(1, 2, 10)
    #ifdef GP2X
        Mix_Init(MIX_INIT_OGG);
    #else
        Mix_Init(MIX_INIT_MP3);
    #endif
#endif

    //Pour le son
    //Epee quand on frappe
    Mix_Chunk *sword = NULL, *ah = NULL, *hurt = NULL, *ehit = NULL, *ekill = NULL, *LowHealth = NULL, *item_sound = NULL, *fanfare = NULL;
    Mix_Chunk *dragonstart = NULL, *dragonhit = NULL, *dragondies = NULL, *rain = NULL, *potion_sound = NULL, *destroy = NULL;
    int epee = 1, epee2 = 1;

    /* Chargement des sons */
    sword        = Mix_LoadWAV("sons/sword.wav");
    ah           = Mix_LoadWAV("sons/ah.wav");
    hurt         = Mix_LoadWAV("sons/hurt.wav");
    ehit         = Mix_LoadWAV("sons/ehit.wav");
    ekill        = Mix_LoadWAV("sons/ekill.wav");
    LowHealth    = Mix_LoadWAV("sons/LowHealth.wav");
    item_sound   = Mix_LoadWAV("sons/item.wav");
    fanfare      = Mix_LoadWAV("sons/fanfare.wav");
    dragonstart  = Mix_LoadWAV("sons/dragonstart.wav");
    dragonhit    = Mix_LoadWAV("sons/dragonhit.wav");
    dragondies   = Mix_LoadWAV("sons/dragondies.wav");
    rain         = Mix_LoadWAV("sons/rain2.wav");
    potion_sound = Mix_LoadWAV("sons/potion.wav");
    destroy      = Mix_LoadWAV("sons/destroy.wav");

     //Musiques
    loadSong(0);


    // Gestion du texte

//    SDL_Color couleurBlanche = {255, 255, 255};
    TTF_Init();
    /* Chargement de la police */
    police = TTF_OpenFont("police.ttf", TEXT_SIZE);


    SDL_WM_SetIcon(IMG_Load("B20.bmp"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode

    //23 dec 09 : Pour le joystick
     //Stocke le numéro du joystick
    if ( SDL_NumJoysticks() > 0 )
    {
        SDL_JoystickEventState(SDL_ENABLE);
        joystick = SDL_JoystickOpen(0);

    }
    printf("----> %d boutons\n", SDL_JoystickNumButtons(joystick));
    printf("----> %d axes\n", SDL_JoystickNumAxes(joystick));
    printf("----> %d trackballs\n", SDL_JoystickNumBalls(joystick));
    printf("----> %d chapeaux\n", SDL_JoystickNumHats(joystick));


    //Gestion du profil et du plein ecran
    int video = 2;   //Mode video : 1 = plein ecran, 2 = fenetre
    int profil = 1;  // Profil : 1 = normal, 2 = netbooks
    int KR = 10;

#ifdef GP2X
    KR = 10;
    ecran = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN | SDL_NOFRAME );
    //ecran = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE );
#elif defined(PANDORA)
    KR = 10;
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN | SDL_NOFRAME );
#else
    if (profil == 1) {  KR = 10;
     if ( video == 1) {
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
     else if ( video == 2) {
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); }
    }
    else if (profil == 2) {  KR = 1;
     if ( video == 1) {
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
     else if ( video == 2) {
        ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF ); }
    }
#endif

    SDL_WM_SetCaption("Roswyn and The Dragons by Jeremie F. BELLANGER", NULL);


     //On charge mario, i.e. le joueur
        mario[BAS] = loadImage("sprites1/player_bas1.png");
        mario[BAS2] = loadImage("sprites1/player_bas2.png");
        mario[GAUCHE] = loadImage("sprites1/player_gauche1.png");
        mario[GAUCHE2] = loadImage("sprites1/player_gauche2.png");
        mario[HAUT] = loadImage("sprites1/player_haut1.png");
        mario[HAUT2] = loadImage("sprites1/player_haut2.png");
        mario[DROITE] = loadImage("sprites1/player_droite1.png");
        mario[DROITE2] = loadImage("sprites1/player_droite2.png");
        mario[EPEEBAS] = loadImage("sprites1/player_bas_epee.png");
        mario[EPEEHAUT] = loadImage("sprites1/player_haut_epee.png");
        mario[EPEEDROITE] = loadImage("sprites1/player_droite_epee.png");
        mario[EPEEGAUCHE] = loadImage("sprites1/player_gauche_epee.png");
        mario[EPEEBAS2] = loadImage("sprites1/player_bas_epee2.png");
        mario[EPEEHAUT2] = loadImage("sprites1/player_haut_epee2.png");
        mario[EPEEDROITE2] = loadImage("sprites1/player_droite_epee2.png");
        mario[EPEEGAUCHE2] = loadImage("sprites1/player_gauche_epee2.png");
        marioActuel = mario[BAS];

        //Pour le baton de feu (bouboule de fire ! ouch !)
        baton_img = loadImage("objets/fireballC2.png");

    /* On centre mario à l'écran */
        positionMario.x = orig_width / 2 - 35 / 2;
        positionMario.y = orig_height / 2 - 35 / 2;


            //Chargement des items
        SDL_Surface *item[4] = { NULL };
        item[0] = loadImage("objets/coeur.png");
        item[1] = loadImage("objets/money.png");
        item[2] = loadImage("objets/vie2.png");
        item[3] = loadImage("objets/key1.png");
        //Affichage puissance epee + baton de feu
        SDL_Surface *puiss_epee[3] = { NULL }, *puiss_epeeActuel = NULL, *firestick = NULL;
        SDL_Rect positionPuiss_epee;
        positionPuiss_epee.x = 151;
        positionPuiss_epee.y = 430;
        puiss_epee[0] = loadImage("objets/epee1.png");
        puiss_epee[1] = loadImage("objets/epee2.png");
        puiss_epee[2] = loadImage("objets/epee3.png");
        puiss_epeeActuel = puiss_epee[0];
        firestick = loadImage("objets/baton.png");



            //Chargement de la pluie, orage
        SDL_Surface *temps[4] = {NULL}, *orage = NULL;
        temps[0] = loadImage("tiles/temps/pluie1.png");
        temps[1] = loadImage("tiles/temps/pluie2.png");
        temps[2] = loadImage("tiles/temps/pluie3.png");
        temps[3] = loadImage("tiles/temps/pluie4.png");
        tempsActuel = temps[0];
        orage = loadImage("tiles/temps/orage.png");
        positionPluie.x = 0;
        positionPluie.y = 0;
        int tempsPluie = SDL_GetTicks();
        int tempsMusiquePluie = SDL_GetTicks() - 6000;
        int animPluie = 1;



             //Chargement des donnes des ennemis
        //Ennemi1
        ennemi1freeze = ennemi1freeze2 = 0;
        ennemi1[BAS] = loadImage("sprites1/monster1_bas1.png");
        ennemi1[BAS2] = loadImage("sprites1/monster1_bas2.png");
        ennemi1[GAUCHE] = loadImage("sprites1/monster1_gauche1.png");
        ennemi1[GAUCHE2] = loadImage("sprites1/monster1_gauche2.png");
        ennemi1[HAUT] = loadImage("sprites1/monster1_haut1.png");
        ennemi1[HAUT2] = loadImage("sprites1/monster1_haut2.png");
        ennemi1[DROITE] = loadImage("sprites1/monster1_droite1.png");
        ennemi1[DROITE2] = loadImage("sprites1/monster1_droite2.png");
        ennemi1Actuel = ennemi1[BAS];
        //Ennemi2
        ennemi2freeze = ennemi2freeze2 = 0;
        ennemi2[BAS] = loadImage("sprites1/monster2_bas1.png");
        ennemi2[BAS2] = loadImage("sprites1/monster2_bas2.png");
        ennemi2[GAUCHE] = loadImage("sprites1/monster2_gauche1.png");
        ennemi2[GAUCHE2] = loadImage("sprites1/monster2_gauche2.png");
        ennemi2[HAUT] = loadImage("sprites1/monster2_haut1.png");
        ennemi2[HAUT2] = loadImage("sprites1/monster2_haut2.png");
        ennemi2[DROITE] = loadImage("sprites1/monster2_droite1.png");
        ennemi2[DROITE2] = loadImage("sprites1/monster2_droite2.png");
        ennemi2Actuel = ennemi2[BAS];
        //Ennemi3
        ennemi3freeze = ennemi3freeze2 = 0;
        ennemi3[BAS] = loadImage("sprites1/monster3_bas1.png");
        ennemi3[BAS2] = loadImage("sprites1/monster3_bas2.png");
        ennemi3[GAUCHE] = loadImage("sprites1/monster3_gauche1.png");
        ennemi3[GAUCHE2] = loadImage("sprites1/monster3_gauche2.png");
        ennemi3[HAUT] = loadImage("sprites1/monster3_haut1.png");
        ennemi3[HAUT2] = loadImage("sprites1/monster3_haut2.png");
        ennemi3[DROITE] = loadImage("sprites1/monster3_droite1.png");
        ennemi3[DROITE2] = loadImage("sprites1/monster3_droite2.png");
        ennemi3Actuel = ennemi3[BAS];
        //Ennemi4
        ennemi4freeze = ennemi4freeze2 = 0;
        ennemi4[BAS] = loadImage("sprites1/monster4_bas1.png");
        ennemi4[BAS2] = loadImage("sprites1/monster4_bas2.png");
        ennemi4[GAUCHE] = loadImage("sprites1/monster4_gauche1.png");
        ennemi4[GAUCHE2] = loadImage("sprites1/monster4_gauche2.png");
        ennemi4[HAUT] = loadImage("sprites1/monster4_haut1.png");
        ennemi4[HAUT2] = loadImage("sprites1/monster4_haut2.png");
        ennemi4[DROITE] = loadImage("sprites1/monster4_droite1.png");
        ennemi4[DROITE2] = loadImage("sprites1/monster4_droite2.png");
        ennemi4Actuel = ennemi4[BAS];
        //Ennemi5
        ennemi5freeze = ennemi5freeze2 = 0;
        ennemi5[BAS] = loadImage("sprites1/monster5_bas1.png");
        ennemi5[BAS2] = loadImage("sprites1/monster5_bas2.png");
        ennemi5[GAUCHE] = loadImage("sprites1/monster5_gauche1.png");
        ennemi5[GAUCHE2] = loadImage("sprites1/monster5_gauche2.png");
        ennemi5[HAUT] = loadImage("sprites1/monster5_haut1.png");
        ennemi5[HAUT2] = loadImage("sprites1/monster5_haut2.png");
        ennemi5[DROITE] = loadImage("sprites1/monster5_droite1.png");
        ennemi5[DROITE2] = loadImage("sprites1/monster5_droite2.png");
        ennemi5Actuel = ennemi5[BAS];
        //BOSS
        bossPic[HAUT] = loadImage("sprites1/boss1A.png");
        bossPic[BAS] = loadImage("sprites1/boss1B.png");
        bossActuel = bossPic[BAS];
        //Fireball Boule de feu
        fireball[HAUT] = loadImage("objets/fireballA1.png");
        fireball[BAS] = loadImage("objets/fireballA2.png");
        fireballActuel = fireball[BAS];
        //PNJ1
        pnj1[BAS] = loadImage("sprites1/pnj1_bas1.png");
        pnj1[BAS2] = loadImage("sprites1/pnj1_bas2.png");
        pnj1[GAUCHE] = loadImage("sprites1/pnj1_gauche1.png");
        pnj1[GAUCHE2] = loadImage("sprites1/pnj1_gauche2.png");
        pnj1[HAUT] = loadImage("sprites1/pnj1_haut1.png");
        pnj1[HAUT2] = loadImage("sprites1/pnj1_haut2.png");
        pnj1[DROITE] = loadImage("sprites1/pnj1_droite1.png");
        pnj1[DROITE2] = loadImage("sprites1/pnj1_droite2.png");
        pnj1Actuel = pnj1[BAS];
        //PNJ2
        pnj2 = loadImage("sprites1/pnj2static.png");
        pnj2Actuel = pnj2;

    //On enlève la souris (bye bye, mickey ! ;)
    SDL_ShowCursor(SDL_DISABLE);

    //Ecran titre
    continuer = title ( ecran, &potion, &coeur, &coeurmax, &money, &level, &power, &boss, &key, &baton );

    // Chargement du niveau
    if (!chargerNiveau(carte, level))
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
    //Chargement des warps et ennemis :
    chargerDataNiveau(level);


    // Affichage du fond (vie, etc...)
    fond = loadScreenImage("fond/barre_vie.png");
    coeurRouge = loadImage("fond/coeur.png");
    SDL_Rect positionCoeur;
    SDL_Rect positionFond;
        positionFond.x = 0;
        positionFond.y = TAILLE_BLOC * NB_BLOCS_HAUTEUR + 1;


        //A placer avent la boucle principale pour permettre de maintenir une touche enfoncee
        SDL_EnableKeyRepeat(KR, KR); //(duree avant declenchement, delai en ms)


    //Boucle principale du programme pour deplacer Mario
    while (continuer)
        {

            //Gestion des changements de musique

            if ( musiquedavant != musique) {
                loadSong(musique);
                musiquedavant = musique; }


            //On change la variable animMario qui definit la frame du perso (1 ou 2) en fonction du temps
            // animMario = 1 et 2 /mouvement; = 3 /Mode attaque

            if (tempsAnim + 150 < SDL_GetTicks()) {
                tempsAnim = SDL_GetTicks();
                if ( animMarioEpee == 1) animMarioEpee = 2;
                else if (animMarioEpee == 2) animMarioEpee = 1;
                if (animEnnemi1 == 1) animEnnemi1 = 2;
                else if (animEnnemi1 == 2) animEnnemi1 = 1;
                if (animEnnemi2 == 1) animEnnemi2 = 2;
                else if (animEnnemi2 == 2) animEnnemi2 = 1;
                if (animEnnemi3 == 1) animEnnemi3 = 2;
                else if (animEnnemi3 == 2) animEnnemi3 = 1;
                if (animEnnemi4 == 1) animEnnemi4 = 2;
                else if (animEnnemi4 == 2) animEnnemi4 = 1;
                if (animEnnemi5 == 1) animEnnemi5 = 2;
                else if (animEnnemi5 == 2) animEnnemi5 = 1;
                if (animfireball1 == 1) animfireball1 = 2;
                else if (animfireball1 == 2) animfireball1 = 1;
                if (animPnj1 == 1) animPnj1 = 2;
                else if (animPnj1 == 2) animPnj1 = 1;


                if (animMario == 1) animMario = 2;
                else if (animMario == 2) animMario = 1;
                else if (animMario == 3) { animMario = 1;
                    if (marioActuel == mario[EPEEBAS]) marioActuel = mario[BAS];
                    if (marioActuel == mario[EPEEDROITE]) marioActuel = mario[DROITE];
                    if (marioActuel == mario[EPEEGAUCHE]) marioActuel = mario[GAUCHE];
                    if (marioActuel == mario[EPEEHAUT]) marioActuel = mario[HAUT];
                    if (marioActuel == mario[EPEEBAS2]) marioActuel = mario[BAS2];
                    if (marioActuel == mario[EPEEDROITE2]) marioActuel = mario[DROITE2];
                    if (marioActuel == mario[EPEEGAUCHE2]) marioActuel = mario[GAUCHE2];
                    if (marioActuel == mario[EPEEHAUT2]) marioActuel = mario[HAUT2];
                    } }

                //Idem mais en plus lent pour le boss
                if (tempsBougeBoss + 200 < SDL_GetTicks()) {
                tempsBougeBoss = SDL_GetTicks();
                if (animBoss == 1) animBoss = 2;
                else if (animBoss == 2) animBoss = 1; }


                //Pour animer la pluie
        if (tempsPluie + 200 < SDL_GetTicks()) {
                tempsPluie = SDL_GetTicks();
                if ( animPluie == 1 ) { tempsActuel = temps[1]; animPluie = 2; }
                else if ( animPluie == 2 ) { tempsActuel = temps[2]; animPluie = 3; }
                else if ( animPluie == 3 ) { tempsActuel = temps[3]; animPluie = 4; }
                else if ( animPluie == 4 ) { tempsActuel = temps[0]; animPluie = 1; }
                }


        //On teste la valeur de tempsCoeur pour temporiser entre deux coups, sinon c'est la folie (mort en 1/4 de sec)
            if (tempsCoeur + 300 < SDL_GetTicks()) invincibilite = 0; //A partir du moment ou on est touche tempscoeur enregistre le temps puis on compte pour enlever l'invincibilite

        //On teste tempsennemi1 qui le bloque si il est touche (ennemi1freeze) et l'empeche d'etre blesse (ennemi1freeze2)
            if (tempsennemi1 + 300 < SDL_GetTicks()) ennemi1freeze = ennemi1freeze2 = 0;
            if (tempsennemi2 + 300 < SDL_GetTicks()) ennemi2freeze = ennemi2freeze2 = 0;
            if (tempsennemi3 + 300 < SDL_GetTicks()) ennemi3freeze = ennemi3freeze2 = 0;
            if (tempsennemi4 + 300 < SDL_GetTicks()) ennemi4freeze = ennemi4freeze2 = 0;
            if (tempsennemi5 + 300 < SDL_GetTicks()) ennemi5freeze = ennemi5freeze2 = 0;
            if (tempsboss + 300 < SDL_GetTicks()) bossfreeze = bossfreeze2 = 0;


            int arrow_pressed, space_pressed, space_keydown;

            arrow_pressed = space_pressed = space_keydown = 0;

            if(SDL_PollEvent(&event))

            /* On teste l'input du joueur */
            switch(event.type)
                {
                    case SDL_QUIT: /* Si c'est un évènement de type "Quitter" */
                    continuer = 0;
                    break;

                    // Gestion du clavier pour deplacer
                    case SDL_KEYDOWN:

                    switch(event.key.keysym.sym)
                        {
                        case SDLK_UP: // Flèche haut anim complete : on teste les 2 tiles contre lesquels se trouve le perso et on met a jour l'animation selon la valeur d' animMario
                            arrow_pressed = 1;
                            if (keystate[SDLK_SPACE]) space_pressed = 1;
                            break;

                        case SDLK_DOWN: // Flèche bas anim idem
                            arrow_pressed = 2;
                            if (keystate[SDLK_SPACE]) space_pressed = 1;
                            break;

                        case SDLK_RIGHT: // Flèche droite anim idem
                            arrow_pressed = 3;
                            if (keystate[SDLK_SPACE]) space_pressed = 1;
                            break;

                        case SDLK_LEFT: // Flèche gauche anim idem
                            arrow_pressed = 4;
                            if (keystate[SDLK_SPACE]) space_pressed = 1;
                            break;

                        //Attaque avec spacebar pendant la duree tempsAnim, on met animMario à 3
                        case SDLK_SPACE:
                            space_keydown = 1;
                            break;

                        case SDLK_RETURN:
                            if (input.timer + 500 < SDL_GetTicks())
                            {

                            input.timer = SDL_GetTicks();
                            input.pause = 1;

                            }

                            break;


                        case SDLK_ESCAPE: /* Si c'est un évènement de type "Quitter" */
                            continuer = 0;
                            break;

#if !defined(GP2X) && !defined(PANDORA)
                        case SDLK_F1: // Gestion du mode video : plein ecran ou fenetre
                            if ( video == 1 ) video = 2 ;
                            else video = 1 ;

                            if (profil == 1) {  KR = 10;
                                if ( video == 1) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
                                else if ( video == 2) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); }
                            }
                            else if (profil == 2) {  KR = 1;
                                if ( video == 1) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
                                else if ( video == 2) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF ); }
                                }
                            break;


                        case SDLK_F2: // Gestion du mode video : plein ecran ou fenetre
                            if ( profil == 1 ) profil = 2 ;
                            else profil = 1 ;

                            if (profil == 1) {  KR = 10;
                                if ( video == 1) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
                                else if ( video == 2) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF ); }
                            }
                            else if (profil == 2) {  KR = 1;
                                if ( video == 1) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN ); }
                                else if ( video == 2) {
                                ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF ); }
                                }
                            break;
#endif

                        default:
                            break;

                            } //Fin de SDL_KEYDOWN

                        case SDL_KEYUP:

                            switch(event.key.keysym.sym)
                            {
                                case SDLK_F3: // Gestion du mode 60fps - à desactiver sur les petites configs

                                if (keytime + 500 < SDL_GetTicks())
                                {
                                    if ( fps == 1 )
                                        {
                                            fps = 0;
                                            AfficheDialogues (ecran, police, 985);
                                        }
                                    else
                                        {
                                            fps = 1;
                                            AfficheDialogues (ecran, police, 984);
                                        }
                                    keytime = SDL_GetTicks();
                                }
                                break;


                        default:
                            break;

                            }

                //23dec09 : gestion du joystick (en parallèle du clavier)
                if ( SDL_NumJoysticks() > 0 )
                    { case SDL_JOYBUTTONDOWN:
                    if ( event.jbutton.button == 0 ) /* Touche A équivalent de SPACEBAR */
                    {
                        space_keydown = 1;
                    }
                    break;

                    case SDL_JOYHATMOTION:  /* Handle Hat Motion */
                        switch ( event.jhat.value )
                        {
                        case SDL_HAT_UP : // Flèche haut anim complete : on teste les 2 tiles contre lesquels se trouve le perso et on met a jour l'animation selon la valeur d' animMario
                        case SDL_HAT_RIGHTUP :
                        case SDL_HAT_LEFTUP :
                            arrow_pressed = 1;
                            if (SDL_JoystickGetButton (joystick, 0)) space_pressed = 1;
                            break;

                        case SDL_HAT_DOWN: // Flèche bas anim idem
                        case SDL_HAT_RIGHTDOWN :
                        case SDL_HAT_LEFTDOWN :
                            arrow_pressed = 2;
                            if (SDL_JoystickGetButton (joystick, 0)) space_pressed = 1;
                            break;

                        case SDL_HAT_RIGHT: // Flèche droite anim idem
                            arrow_pressed = 3;
                            if (SDL_JoystickGetButton (joystick, 0)) space_pressed = 1;
                            break;

                        case SDL_HAT_LEFT: // Flèche gauche anim idem
                            arrow_pressed = 4;
                            if (SDL_JoystickGetButton (joystick, 0)) space_pressed = 1;
                            break;

                    }

                }
                }

            switch(arrow_pressed)
            {
                case 1: // SDLK_UP
                    if (space_pressed) {
                        if ( animMarioEpee == 1) { marioActuel = mario[EPEEHAUT]; }
                        else { marioActuel = mario[EPEEHAUT2]; }
                        animMario = 3;
                        if (positionMario.y <= 1) {
                        // on warpe si warpGauche == le nombre d'un level, sinon 0
                        if (warpHaut != 0) { level = warpHaut; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.y = 380; baton_used = 0; }
                         break; }
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] <= 20)  break;
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] <= 20)  break;
                        //Gestion des tiles HIT
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        //Gestion des cases speciales (coffres...)
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] >= 46)  break;
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] >= 46)  break;

                        else positionMario.y -= 2; break;
                            }

                    else if (positionMario.y <= 1) {
                        // on warpe si warpHaut == le nombre d'un level, sinon 0
                        if (warpHaut != 0) { level = warpHaut; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.y = 380; baton_used = 0; }
                        if (animMario == 1) { marioActuel = mario[HAUT]; } else  marioActuel = mario[HAUT2];  break;  }

                    if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] <= 20) { if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2]; break; }
                    if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] <= 20) { if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2]; break; }
                    //Gestion des tiles HIT
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] >= 51)
                            {   if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] >= 51)
                            {   if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                    //Gestion des cases speciales (coffres...)
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] >= 46) { if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2]; break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] >= 46)  { if (animMario == 1) marioActuel = mario[HAUT]; else marioActuel = mario[HAUT2]; break; }

                    else positionMario.y -= 2;
                    if (animMario == 1) { marioActuel = mario[HAUT]; } else { marioActuel = mario[HAUT2]; }
                    break;

                case 2: // SDLK_DOWN
                    if (space_pressed) {
                        if ( animMarioEpee == 1) { marioActuel = mario[EPEEBAS]; }
                        else { marioActuel = mario[EPEEBAS2]; }
                        animMario = 3;
                        if (positionMario.y >= orig_height - 80) {
                        // on warpe si warpGauche == le nombre d'un level, sinon 0
                        if (warpBas != 0) { level = warpBas; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.y = 0; baton_used = 0; }
                         break; }
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20)  break;
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20)  break;
                        //Gestion des tiles HIT
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        //Gestion des cases speciales (coffres...)
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46)  break;
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46)  break;

                        else positionMario.y += 2; break;
                            }

                    else if (positionMario.y >= orig_height - 80) {
                         // on warpe si warpHaut == le nombre d'un level, sinon 0
                        if (warpBas != 0) { level = warpBas; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.y = 0; baton_used = 0; }
                        if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2]; break; }

                    if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) { if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2]; break; }
                    if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] <= 20) { if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2]; break; }
                    //Gestion des tiles HIT
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                    //Gestion des cases speciales (coffres...)
                        if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46)  { if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2]; break; }
                        if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] >= 46)  { if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2]; break; }

                    else positionMario.y += 2;
                    if (animMario == 1) { marioActuel = mario[BAS]; } else marioActuel = mario[BAS2];
                    break;

                case 3: // SDLK_RIGHT
                    if (space_pressed) {
                        if ( animMarioEpee == 1) { marioActuel = mario[EPEEDROITE]; }
                        else { marioActuel = mario[EPEEDROITE2]; }
                        animMario = 3;
                        if (positionMario.x >= orig_width - 40) {
                        // on warpe si warpGauche == le nombre d'un level, sinon 0
                        if (warpDroite != 0) { level = warpDroite; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.x = 0; baton_used = 0;
                          } break; }
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] <= 20)  break;
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] <= 20)  break;
                        //Gestion des tiles HIT
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        //Gestion des cases speciales (coffres...)
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] >= 46)  break;
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] >= 46)  break;

                        else positionMario.x += 2; break;
                            }

                    else if (positionMario.x >= orig_width - 40) {
                    // on warpe si warpDroite == le nombre d'un level, sinon 0
                        if (warpDroite != 0) { level = warpDroite; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.x = 0; baton_used = 0; }
                        if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2]; break; }

                    if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] <= 20) { if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2]; break; }
                    if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] <= 20) { if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2]; break; }
                    //Gestion des tiles HIT
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                    //Gestion des cases speciales (coffres...)
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] >= 46)  { if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2]; break; }
                            if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] >= 46)  { if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2]; break; }

                    else positionMario.x += 2;
                    if (animMario == 1) { marioActuel = mario[DROITE]; } else marioActuel = mario[DROITE2];
                    break;

                case 4: // SDLK_LEFT
                    if (space_pressed) {
                        if ( animMarioEpee == 1) { marioActuel = mario[EPEEGAUCHE]; }
                        else { marioActuel = mario[EPEEGAUCHE2]; }
                        animMario = 3;
                        if (positionMario.x <= 1) {
                        // on warpe si warpGauche == le nombre d'un level, sinon 0
                        if (warpGauche != 0) { level = warpGauche; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.x = 380; baton_used = 0;
                          } break; }
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] <= 20)  break;
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] <= 20)  break;
                        //Gestion des tiles HIT
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] >= 51)
                            { if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        //Gestion des cases speciales (coffres...)
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] >= 46)  break;
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] >= 46)  break;

                        else positionMario.x -= 2; break;
                            }

                    else if (positionMario.x <= 1) {
                        // on warpe si warpGauche == le nombre d'un level, sinon 0
                        if (warpGauche != 0) { level = warpGauche; chargerNiveau(carte, level); chargerDataNiveau (level); positionMario.x = 380; baton_used = 0; }
                        if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2]; break; }
                    if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] <= 20) { if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2]; break; }
                    if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] <= 20) { if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2]; break; }
                    //Gestion des tiles HIT
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                        if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] >= 51)
                            {   if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2];
                                if (invincibilite == 0) {
                            coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); } break; }
                    //Gestion des cases speciales (coffres...)
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] >= 46)  { if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2]; break; }
                            if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] >= 46)  { if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2]; break; }

                    else positionMario.x -= 2;
                    if (animMario == 1) { marioActuel = mario[GAUCHE]; } else marioActuel = mario[GAUCHE2];
                    break;

                default:
                    break;
            }
            switch (space_keydown)
            {
                case 1: // SDLK_SPACE
                    if (marioActuel == mario[BAS]) { marioActuel = mario[EPEEBAS]; animMario = 3; }
                    if (marioActuel == mario[HAUT]) { marioActuel = mario[EPEEHAUT]; animMario = 3; }
                    if (marioActuel == mario[DROITE]) { marioActuel = mario[EPEEDROITE]; animMario = 3; }
                    if (marioActuel == mario[GAUCHE]) { marioActuel = mario[EPEEGAUCHE]; animMario = 3; }
                    if (marioActuel == mario[BAS2]) { marioActuel = mario[EPEEBAS2]; animMario = 3; }
                    if (marioActuel == mario[HAUT2]) { marioActuel = mario[EPEEHAUT2]; animMario = 3; }
                    if (marioActuel == mario[DROITE2]) { marioActuel = mario[EPEEDROITE2]; animMario = 3; }
                    if (marioActuel == mario[GAUCHE2]) { marioActuel = mario[EPEEGAUCHE2]; animMario = 3; }

                    //Test Epee Nv 3.  Rochers
                    if ( power > 2 ) {
                        if (marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 49)
                                { carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 49)
                                { carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] == 49)
                                { carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] == 49)
                                { carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2])
                            { if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] == 49)
                                { carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] == 49)
                                { carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2])
                            { if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] == 49)
                                { carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] == 49)
                                { carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                    } //Fin

                    //Test epee puissance 2 - potiches
                    if ( power > 1 ) {
                        if (marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 50)
                                { carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 50)
                                { carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] == 50)
                                { carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] == 50)
                                { carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2])
                            { if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] == 50)
                                { carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] == 50)
                                { carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                        if (marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2])
                            { if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] == 50)
                                { carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] = 21; Mix_PlayChannel(-1, destroy, 0); }
                              if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] == 50)
                                { carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] = 21; Mix_PlayChannel(-1, destroy, 0); }
                            }
                    } //Fin

                    //Test Coffres

                        if (marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y + 2) / TAILLE_BLOC + 1] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                            }
                        if (marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                              if (carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                            }
                        if (marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2])
                            { if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                              if (carte[(positionMario.x +2) / TAILLE_BLOC + 1] [positionMario.y / TAILLE_BLOC + 1] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                            }
                        if (marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2])
                            { if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                              if (carte[(positionMario.x -2) / TAILLE_BLOC] [positionMario.y / TAILLE_BLOC + 1] == 46)
                                { if ( ValeurCoffre(level) == 1) { OuvreCoffre(level); open = 1; Mix_PlayChannel(-1, fanfare, 0); } }
                            }

                        //Ouverture du coffre
                        if (open == 1) {
                            switch (coffre) {
                                case 0 :
                                money += 50;
                                AfficheDialogues (ecran, police, 995);
                                open = 0;
                                break;

                                case 1 :
                                money += 100;
                                AfficheDialogues (ecran, police, 994);
                                open = 0;
                                break;

                                case 2 :
                                money += 200;
                                AfficheDialogues (ecran, police, 993);
                                open = 0;
                                break;

                                case 3 :
                                potion++;
                                AfficheDialogues (ecran, police, 992);
                                open = 0;
                                break;

                                case 4 :
                                potion += 2;
                                AfficheDialogues (ecran, police, 991);
                                open = 0;
                                break;

                                case 5 :
                                key++;
                                AfficheDialogues (ecran, police, 990);
                                open = 0;
                                break;

                                case 6 :
                                coeur=++coeurmax;
                                AfficheDialogues (ecran, police, 989);
                                open = 0;
                                break;
                            }
                        }


                    //Test Switchs

                        if (marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2])
                            { if (carte[positionMario.x / TAILLE_BLOC] [(positionMario.y - 6) / TAILLE_BLOC] == 48 || carte[positionMario.x / TAILLE_BLOC + 1] [(positionMario.y - 6) / TAILLE_BLOC] == 48  )
                                 { if ( ValeurSwitch(lswitch) == 1) { if (key > 0) { OuvreSwitch();
                                Mix_PlayChannel(-1, fanfare, 0); if ( ValeurSwitch(lswitch) == 0) key--; break; }  } }
                            }

                    //Test baton de feu

                        if ( baton == 1 ) //Si on a le baton de feu
                        {
                            if ( baton_used == 0) // Si on ne l'a pas utilisé
                            {  //Suivant la direction de Roswyn ( Mario ? ;)
                                if (marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2])
                                {
                                    direction_baton = HAUT;
                                    PositionBaton.x = positionMario.x + 7;
                                    PositionBaton.y = positionMario.y + 7;
                                }

                                if (marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2])
                                {
                                    direction_baton = BAS;
                                    PositionBaton.x = positionMario.x + 7;
                                    PositionBaton.y = positionMario.y + 35;
                                }

                                if (marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2])
                                {
                                    direction_baton = DROITE;
                                    PositionBaton.x = positionMario.x + 35;
                                    PositionBaton.y = positionMario.y + 7;
                                }

                                if (marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2])
                                {
                                    direction_baton = GAUCHE;
                                    PositionBaton.x = positionMario.x + 7;
                                    PositionBaton.y = positionMario.y + 7;
                                }

                                baton_used = 1;
                            }
                        }
                    break;
                default:
                    break;
            }

/* Gestion de la pause */
    if (input.pause == 1)
        continuer = pauseGame();


    //Gestion du son :
    if ( animMario == 3 ) { if (epee2 == 0) { epee = 0; epee2 = 1; } }
    else epee2 = 0;
    if (epee == 0) { epee = 1;  Mix_PlayChannel(-1, ah, 0); Mix_PlayChannel(-1, sword, 0);  }


    //******Deplacement et gestion de ennemi1 s'il est vivant**********
    if (ennemi1vivant == 1) {
        // ennemi1 se deplace sauf s'il est en freeze
        if (ennemi1freeze == 0) {
        //Vers le haut si player en haut
        if (positionMario.y - positionEnnemi1.y < 0) {
        if (positionEnnemi1.y <= 1) { if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[HAUT]; } else { ennemi1Actuel = ennemi1[HAUT2]; } }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC] [(positionEnnemi1.y - 2) / TAILLE_BLOC] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[HAUT]; else ennemi1Actuel = ennemi1[HAUT2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC + 1] [(positionEnnemi1.y - 2) / TAILLE_BLOC] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[HAUT]; else ennemi1Actuel = ennemi1[HAUT2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC] [(positionEnnemi1.y - 2) / TAILLE_BLOC] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[HAUT]; else ennemi1Actuel = ennemi1[HAUT2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC + 1] [(positionEnnemi1.y - 2) / TAILLE_BLOC] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[HAUT]; else ennemi1Actuel = ennemi1[HAUT2]; }
        else positionEnnemi1.y -= 1;
        if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[HAUT]; } else { ennemi1Actuel = ennemi1[HAUT2]; }
        }
        //Vers le bas si player en bas
        if (positionMario.y - positionEnnemi1.y > 0) {
        if (positionEnnemi1.y >= orig_height - 80) { if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[BAS]; } else { ennemi1Actuel = ennemi1[BAS2]; } }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC] [(positionEnnemi1.y + 2) / TAILLE_BLOC + 1] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[BAS]; else ennemi1Actuel = ennemi1[BAS2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC + 1] [(positionEnnemi1.y + 2) / TAILLE_BLOC + 1] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[BAS]; else ennemi1Actuel = ennemi1[BAS2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC] [(positionEnnemi1.y + 2) / TAILLE_BLOC + 1] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[BAS]; else ennemi1Actuel = ennemi1[BAS2]; }
         else if (carte[positionEnnemi1.x / TAILLE_BLOC + 1] [(positionEnnemi1.y + 2) / TAILLE_BLOC + 1] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[BAS]; else ennemi1Actuel = ennemi1[BAS2]; }
        else positionEnnemi1.y += 1;
        if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[BAS]; } else { ennemi1Actuel = ennemi1[BAS2]; }
        }
        //Vers la droite si player a droite
        if (positionMario.x - positionEnnemi1.x > 0) {
        if (positionEnnemi1.x >= orig_width - 35) { if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[DROITE]; } else { ennemi1Actuel = ennemi1[DROITE2]; } }
         else if (carte[(positionEnnemi1.x + 2) / TAILLE_BLOC + 1] [positionEnnemi1.y / TAILLE_BLOC] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[DROITE]; else ennemi1Actuel = ennemi1[DROITE2]; }
         else if (carte[(positionEnnemi1.x + 2) / TAILLE_BLOC + 1] [positionEnnemi1.y / TAILLE_BLOC + 1] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[DROITE]; else ennemi1Actuel = ennemi1[DROITE2]; }
         else if (carte[(positionEnnemi1.x + 2) / TAILLE_BLOC + 1] [positionEnnemi1.y / TAILLE_BLOC] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[DROITE]; else ennemi1Actuel = ennemi1[DROITE2]; }
         else if (carte[(positionEnnemi1.x + 2) / TAILLE_BLOC + 1] [positionEnnemi1.y / TAILLE_BLOC + 1] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[DROITE]; else ennemi1Actuel = ennemi1[DROITE2]; }
        else positionEnnemi1.x += 1;
        if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[DROITE]; } else { ennemi1Actuel = ennemi1[DROITE2]; }
        }
        //Vers la gauche si player a gauche
        if (positionMario.x - positionEnnemi1.x < 0) {
        if (positionEnnemi1.x <= 1) { if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[GAUCHE]; } else { ennemi1Actuel = ennemi1[GAUCHE2]; } }
         else if (carte[(positionEnnemi1.x - 2) / TAILLE_BLOC] [positionEnnemi1.y / TAILLE_BLOC] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[GAUCHE]; else ennemi1Actuel = ennemi1[GAUCHE2]; }
         else if (carte[(positionEnnemi1.x - 2) / TAILLE_BLOC] [positionEnnemi1.y / TAILLE_BLOC + 1] <= 20) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[GAUCHE]; else ennemi1Actuel = ennemi1[GAUCHE2]; }
         else if (carte[(positionEnnemi1.x - 2) / TAILLE_BLOC] [positionEnnemi1.y / TAILLE_BLOC] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[GAUCHE]; else ennemi1Actuel = ennemi1[GAUCHE2]; }
         else if (carte[(positionEnnemi1.x - 2) / TAILLE_BLOC] [positionEnnemi1.y / TAILLE_BLOC + 1] >= 46) { if (animEnnemi1 == 1) ennemi1Actuel = ennemi1[GAUCHE]; else ennemi1Actuel = ennemi1[GAUCHE2]; }
        else positionEnnemi1.x -= 1;
        if (animEnnemi1 == 1) { ennemi1Actuel = ennemi1[GAUCHE]; } else { ennemi1Actuel = ennemi1[GAUCHE2]; }
        }
        }

            //Detection des collisions entre player et ennemi1, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionEnnemi1.x);
            y = (positionMario.y) - (positionEnnemi1.y);

            //1. S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25) {
                if (invincibilite == 0) {
                    if (animMario == 3) { if (ennemi1freeze2 == 0) { ennemi1freeze = ennemi1freeze2 = 1;
                    ennemi1life -= 1; if (ennemi1life <= 0) Mix_PlayChannel(-1, ekill, 0); else Mix_PlayChannel(-1, ehit, 0); tempsennemi1 = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } }



            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 30 && abs(y) < 25) {
                //A- On attaque, l'ennemi recule
                       //Si on regarde en haut :
                        if (  marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[EPEEBAS]; DeplacePlayer(HAUT, 1, ecran, carte); }
                            DeplaceEnnemi ( 1, HAUT, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, ennemi en hau, on se retourne
                            if ( y > 0) { marioActuel = mario[EPEEHAUT]; DeplacePlayer(BAS, 1, ecran, carte); }
                            DeplaceEnnemi (1, BAS, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a gauche, et que l'ennemi arrive a droite, on se retourne
                            if ( x > 0) { marioActuel = mario[EPEEGAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); }
                            DeplaceEnnemi (1, DROITE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive a gauche, on se retourne
                            if ( x < 0) { marioActuel = mario[EPEEDROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); }
                            DeplaceEnnemi (1, GAUCHE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Gauche
                            // Fin A- Attaque



                //B- On subit l'attaque, le player recule
                    else {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (1, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (1, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 1
                        else if (  marioActuel == mario[HAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (1, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (1, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 2
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (1, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (1, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 1
                        else if (  marioActuel == mario[BAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (1, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (1, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 2
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (1, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (1, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 1
                        else if (  marioActuel == mario[DROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive par a gauche, on se retourne
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (1, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (1, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 2
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (1, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (1, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 1
                        else if (  marioActuel == mario[GAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (1, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (1, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 2
                            }// Fin B- Subit les dommages


                 }


            // on teste si ennemi1 est encore vivant a la fin
            if (ennemi1life <= 0)
                { ennemi1vivant = 0; laisseItem(1); }

            }  // Fin test ennemi1



        //******Deplacement et gestion de ennemi2 s'il est vivant**********
    if (ennemi2vivant == 1) {
        //on tire une direction au hasard
        if ( tempsBougeEnnemi2 + 500 <= SDL_GetTicks() )
        { direction = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougeEnnemi2 = SDL_GetTicks(); }
        // ennemi2 se deplace sauf s'il est en freeze
        if (ennemi2freeze == 0) {
        //Vers le haut si 1
        if (direction == 1) {
        if (positionEnnemi2.y <= 1) { direction++; if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[HAUT]; } else { ennemi2Actuel = ennemi2[HAUT2]; } }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC] [(positionEnnemi2.y - 2) / TAILLE_BLOC] <= 20) { direction++; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[HAUT]; else ennemi2Actuel = ennemi2[HAUT2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC + 1] [(positionEnnemi2.y - 2) / TAILLE_BLOC] <= 20) { direction++; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[HAUT]; else ennemi2Actuel = ennemi2[HAUT2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC] [(positionEnnemi2.y - 2) / TAILLE_BLOC] >= 46) { direction++; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[HAUT]; else ennemi2Actuel = ennemi2[HAUT2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC + 1] [(positionEnnemi2.y - 2) / TAILLE_BLOC] >= 46) { direction++; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[HAUT]; else ennemi2Actuel = ennemi2[HAUT2]; }
        else positionEnnemi2.y -= 2;
        if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[HAUT]; } else { ennemi2Actuel = ennemi2[HAUT2]; }
        }
        //Vers le bas si 2
        if (direction == 2) {
        if (positionEnnemi2.y >= orig_height - 80) { direction++;  if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[BAS]; } else { ennemi2Actuel = ennemi2[BAS2]; } }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC] [(positionEnnemi2.y + 2) / TAILLE_BLOC + 1] <= 20) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[BAS]; else ennemi2Actuel = ennemi2[BAS2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC + 1] [(positionEnnemi2.y + 2) / TAILLE_BLOC + 1] <= 20) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[BAS]; else ennemi2Actuel = ennemi2[BAS2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC] [(positionEnnemi2.y + 2) / TAILLE_BLOC + 1] >= 46) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[BAS]; else ennemi2Actuel = ennemi2[BAS2]; }
         else if (carte[positionEnnemi2.x / TAILLE_BLOC + 1] [(positionEnnemi2.y + 2) / TAILLE_BLOC + 1] >= 46) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[BAS]; else ennemi2Actuel = ennemi2[BAS2]; }
        else positionEnnemi2.y += 2;
        if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[BAS]; } else { ennemi2Actuel = ennemi2[BAS2]; }
        }
        //Vers la droite si 3
        if (direction == 3) {
        if (positionEnnemi2.x >= orig_width - 35) { direction++;  if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[DROITE]; } else { ennemi2Actuel = ennemi2[DROITE2]; } }
         else if (carte[(positionEnnemi2.x + 2) / TAILLE_BLOC + 1] [positionEnnemi2.y / TAILLE_BLOC] <= 20) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[DROITE]; else ennemi2Actuel = ennemi2[DROITE2]; }
         else if (carte[(positionEnnemi2.x + 2) / TAILLE_BLOC + 1] [positionEnnemi2.y / TAILLE_BLOC + 1] <= 20) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[DROITE]; else ennemi2Actuel = ennemi2[DROITE2]; }
         else if (carte[(positionEnnemi2.x + 2) / TAILLE_BLOC + 1] [positionEnnemi2.y / TAILLE_BLOC] >= 46) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[DROITE]; else ennemi2Actuel = ennemi2[DROITE2]; }
         else if (carte[(positionEnnemi2.x + 2) / TAILLE_BLOC + 1] [positionEnnemi2.y / TAILLE_BLOC + 1] >= 46) { direction++;  if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[DROITE]; else ennemi2Actuel = ennemi2[DROITE2]; }
        else positionEnnemi2.x += 2;
        if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[DROITE]; } else { ennemi2Actuel = ennemi2[DROITE2]; }
        }
        //Vers la gauche si 4
        if (direction == 4) {
        if (positionEnnemi2.x <= 1) { direction = 1;  if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[GAUCHE]; } else { ennemi2Actuel = ennemi2[GAUCHE2]; } }
         else if (carte[(positionEnnemi2.x - 2) / TAILLE_BLOC] [positionEnnemi2.y / TAILLE_BLOC] <= 20) { direction = 1; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[GAUCHE]; else ennemi2Actuel = ennemi2[GAUCHE2]; }
         else if (carte[(positionEnnemi2.x - 2) / TAILLE_BLOC] [positionEnnemi2.y / TAILLE_BLOC + 1] <= 20) { direction = 1; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[GAUCHE]; else ennemi2Actuel = ennemi2[GAUCHE2]; }
         else if (carte[(positionEnnemi2.x - 2) / TAILLE_BLOC] [positionEnnemi2.y / TAILLE_BLOC] >= 46) { direction = 1; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[GAUCHE]; else ennemi2Actuel = ennemi2[GAUCHE2]; }
         else if (carte[(positionEnnemi2.x - 2) / TAILLE_BLOC] [positionEnnemi2.y / TAILLE_BLOC + 1] >= 46) { direction = 1; if (animEnnemi2 == 1) ennemi2Actuel = ennemi2[GAUCHE]; else ennemi2Actuel = ennemi2[GAUCHE2]; }
        else positionEnnemi2.x -= 2;
        if (animEnnemi2 == 1) { ennemi2Actuel = ennemi2[GAUCHE]; } else { ennemi2Actuel = ennemi2[GAUCHE2]; }
        }
        }

            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionEnnemi2.x);
            y = (positionMario.y) - (positionEnnemi2.y);

            //1. S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25) {
                if (invincibilite == 0) {
                    if (animMario == 3) { if (ennemi2freeze2 == 0) { ennemi2freeze = ennemi2freeze2 = 1; ennemi2life -= 1;
                    if (ennemi2life <= 0) Mix_PlayChannel(-1, ekill, 0); else Mix_PlayChannel(-1, ehit, 0);tempsennemi2 = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } }


            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 30 && abs(y) < 25) {
                //A- On attaque, l'ennemi recule
                       //Si on regarde en haut :
                        if (  marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[EPEEBAS]; DeplacePlayer(HAUT, 1, ecran, carte); }
                            DeplaceEnnemi (2, HAUT, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, ennemi en hau, on se retourne
                            if ( y > 0) { marioActuel = mario[EPEEHAUT]; DeplacePlayer(BAS, 1, ecran, carte); }
                            DeplaceEnnemi (2, BAS, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2]) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a gauche, et que l'ennemi arrive a droite, on se retourne
                            if ( x > 0) { marioActuel = mario[EPEEGAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); }
                            DeplaceEnnemi (2, DROITE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2]) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive a gauche, on se retourne
                            if ( x < 0) { marioActuel = mario[EPEEDROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); }
                            DeplaceEnnemi (2, GAUCHE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Gauche
                            // Fin A- Attaque



                //B- On subit l'attaque, le player recule
                    else {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (2, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (2, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 1
                        else if (  marioActuel == mario[HAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (2, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (2, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 2
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (2, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (2, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 1
                        else if (  marioActuel == mario[BAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (2, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (2, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 2
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (2, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (2, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 1
                        else if (  marioActuel == mario[DROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive par a gauche, on se retourne
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (2, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (2, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 2
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (2, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (2, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 1
                        else if (  marioActuel == mario[GAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (2, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (2, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 2
                            }// Fin B- Subit les dommages


                 }


            // on teste si ennemi1 est encore vivant a la fin
            if (ennemi2life <= 0)
                { ennemi2vivant = 0; laisseItem(2); }


            }  // Fin test ennemi2*****************



        //******Deplacement et gestion de ennemi3 s'il est vivant**********
    if (ennemi3vivant == 1) {
        //on tire une direction au hasard
        if ( tempsBougeEnnemi3 + 1000 <= SDL_GetTicks() )
        { direction2 = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougeEnnemi3 = SDL_GetTicks(); }
        // ennemi2 se deplace sauf s'il est en freeze
        if (ennemi3freeze == 0) {
        //Vers le haut si 1
        if (direction2 == 1) {
        if (positionEnnemi3.y <= 1) { direction2 = 4; if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[HAUT]; } else { ennemi3Actuel = ennemi3[HAUT2]; } }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC] [(positionEnnemi3.y - 2) / TAILLE_BLOC] <= 20) { direction2 = 4; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[HAUT]; else ennemi3Actuel = ennemi3[HAUT2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC + 1] [(positionEnnemi3.y - 2) / TAILLE_BLOC] <= 20) { direction2 = 4; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[HAUT]; else ennemi3Actuel = ennemi3[HAUT2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC] [(positionEnnemi3.y - 2) / TAILLE_BLOC] >= 46) { direction2 = 4; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[HAUT]; else ennemi3Actuel = ennemi3[HAUT2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC + 1] [(positionEnnemi3.y - 2) / TAILLE_BLOC] >= 46) { direction2 = 4; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[HAUT]; else ennemi3Actuel = ennemi3[HAUT2]; }
        else positionEnnemi3.y -= 2;
        if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[HAUT]; } else { ennemi3Actuel = ennemi3[HAUT2]; }
        }
        //Vers le bas si 2
        if (direction2 == 2) {
        if (positionEnnemi3.y >= orig_height - 80) { direction2--;  if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[BAS]; } else { ennemi3Actuel = ennemi3[BAS2]; } }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC] [(positionEnnemi3.y + 2) / TAILLE_BLOC + 1] <= 20) { direction2--;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[BAS]; else ennemi3Actuel = ennemi3[BAS2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC + 1] [(positionEnnemi3.y + 2) / TAILLE_BLOC + 1] <= 20) { direction2--;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[BAS]; else ennemi3Actuel = ennemi3[BAS2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC] [(positionEnnemi3.y + 2) / TAILLE_BLOC + 1] >= 46) { direction2--;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[BAS]; else ennemi3Actuel = ennemi3[BAS2]; }
         else if (carte[positionEnnemi3.x / TAILLE_BLOC + 1] [(positionEnnemi3.y + 2) / TAILLE_BLOC + 1] >= 46) { direction2--;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[BAS]; else ennemi3Actuel = ennemi3[BAS2]; }
        else positionEnnemi3.y += 2;
        if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[BAS]; } else { ennemi3Actuel = ennemi3[BAS2]; }
        }
        //Vers la droite si 3
        if (direction2 == 3) {
        if (positionEnnemi3.x >= orig_width - 35) { direction2++;  if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[DROITE]; } else { ennemi3Actuel = ennemi3[DROITE2]; } }
         else if (carte[(positionEnnemi3.x + 2) / TAILLE_BLOC + 1] [positionEnnemi3.y / TAILLE_BLOC] <= 20) { direction2++;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[DROITE]; else ennemi3Actuel = ennemi3[DROITE2]; }
         else if (carte[(positionEnnemi3.x + 2) / TAILLE_BLOC + 1] [positionEnnemi3.y / TAILLE_BLOC + 1] <= 20) { direction2++;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[DROITE]; else ennemi3Actuel = ennemi3[DROITE2]; }
         else if (carte[(positionEnnemi3.x + 2) / TAILLE_BLOC + 1] [positionEnnemi3.y / TAILLE_BLOC] >= 46) { direction2++;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[DROITE]; else ennemi3Actuel = ennemi3[DROITE2]; }
         else if (carte[(positionEnnemi3.x + 2) / TAILLE_BLOC + 1] [positionEnnemi3.y / TAILLE_BLOC + 1] >= 46) { direction2++;  if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[DROITE]; else ennemi3Actuel = ennemi3[DROITE2]; }
        else positionEnnemi3.x += 2;
        if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[DROITE]; } else { ennemi3Actuel = ennemi3[DROITE2]; }
        }
        //Vers la gauche si 4
        if (direction2 == 4) {
        if (positionEnnemi3.x <= 1) { direction2--;  if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[GAUCHE]; } else { ennemi3Actuel = ennemi3[GAUCHE2]; } }
         else if (carte[(positionEnnemi3.x - 2) / TAILLE_BLOC] [positionEnnemi3.y / TAILLE_BLOC] <= 20) { direction2--; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[GAUCHE]; else ennemi3Actuel = ennemi3[GAUCHE2]; }
         else if (carte[(positionEnnemi3.x - 2) / TAILLE_BLOC] [positionEnnemi3.y / TAILLE_BLOC + 1] <= 20) { direction2--; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[GAUCHE]; else ennemi3Actuel = ennemi3[GAUCHE2]; }
         else if (carte[(positionEnnemi3.x - 2) / TAILLE_BLOC] [positionEnnemi3.y / TAILLE_BLOC] >= 46) { direction2--; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[GAUCHE]; else ennemi3Actuel = ennemi3[GAUCHE2]; }
         else if (carte[(positionEnnemi3.x - 2) / TAILLE_BLOC] [positionEnnemi3.y / TAILLE_BLOC + 1] >= 46) { direction2--; if (animEnnemi3 == 1) ennemi3Actuel = ennemi3[GAUCHE]; else ennemi3Actuel = ennemi3[GAUCHE2]; }
        else positionEnnemi3.x -= 2;
        if (animEnnemi3 == 1) { ennemi3Actuel = ennemi3[GAUCHE]; } else { ennemi3Actuel = ennemi3[GAUCHE2]; }
        }
        }

            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionEnnemi3.x);
            y = (positionMario.y) - (positionEnnemi3.y);

            //1. S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25) {
                if (invincibilite == 0) {
                    if (animMario == 3) { if (ennemi3freeze2 == 0) { ennemi3freeze = ennemi3freeze2 = 1; ennemi3life -= 1;
                    if (ennemi3life <= 0) Mix_PlayChannel(-1, ekill, 0); else Mix_PlayChannel(-1, ehit, 0);tempsennemi3 = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } }


            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 30 && abs(y) < 25) {
                //A- On attaque, l'ennemi recule
                       //Si on regarde en haut :
                        if (  marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[EPEEBAS]; DeplacePlayer(HAUT, 1, ecran, carte); }
                            DeplaceEnnemi (3, HAUT, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, ennemi en hau, on se retourne
                            if ( y > 0) { marioActuel = mario[EPEEHAUT]; DeplacePlayer(BAS, 1, ecran, carte); }
                            DeplaceEnnemi (3, BAS, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a gauche, et que l'ennemi arrive a droite, on se retourne
                            if ( x > 0) { marioActuel = mario[EPEEGAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); }
                            DeplaceEnnemi (3, DROITE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive a gauche, on se retourne
                            if ( x < 0) { marioActuel = mario[EPEEDROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); }
                            DeplaceEnnemi (3, GAUCHE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Gauche
                            // Fin A- Attaque



                //B- On subit l'attaque, le player recule
                    else {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (3, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (3, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 1
                        else if (  marioActuel == mario[HAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (3, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (3, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 2
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (3, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (3, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 1
                        else if (  marioActuel == mario[BAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (3, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (3, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 2
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (3, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (3, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 1
                        else if (  marioActuel == mario[DROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive par a gauche, on se retourne
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (3, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (3, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 2
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (3, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (3, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 1
                        else if (  marioActuel == mario[GAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (3, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (3, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 2
                            }// Fin B- Subit les dommages


                 }


            // on teste si ennemi3 est encore vivant a la fin
            if (ennemi3life <= 0)
                { ennemi3vivant = 0; laisseItem(3); }


            }  // Fin test ennemi3*****************




        //******Deplacement et gestion de ennemi4 s'il est vivant**********
    if (ennemi4vivant == 1) {

        if ( tempsBougeEnnemi4 + 800 <= SDL_GetTicks() )
        { direction3 = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougeEnnemi4 = SDL_GetTicks(); }
        // ennemi4 se deplace sauf s'il est en freeze
        if (ennemi4freeze == 0) {
        //Vers le haut si 1
        if (direction3 == 1) {
        if (positionEnnemi4.y <= 1) { direction3 = 4; if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[HAUT]; } else { ennemi4Actuel = ennemi4[HAUT2]; } }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC] [(positionEnnemi4.y - 2) / TAILLE_BLOC] <= 20) { direction3 = 4; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[HAUT]; else ennemi4Actuel = ennemi4[HAUT2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC + 1] [(positionEnnemi4.y - 2) / TAILLE_BLOC] <= 20) { direction3 = 4; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[HAUT]; else ennemi4Actuel = ennemi4[HAUT2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC] [(positionEnnemi4.y - 2) / TAILLE_BLOC] >= 46) { direction3 = 4; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[HAUT]; else ennemi4Actuel = ennemi4[HAUT2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC + 1] [(positionEnnemi4.y - 2) / TAILLE_BLOC] >= 46) { direction3 = 4; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[HAUT]; else ennemi4Actuel = ennemi4[HAUT2]; }
        else positionEnnemi4.y -= 2;
        if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[HAUT]; } else { ennemi4Actuel = ennemi4[HAUT2]; }
        }
        //Vers le bas si 2
        if (direction3 == 2) {
        if (positionEnnemi4.y >= orig_height - 80) { direction3--;  if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[BAS]; } else { ennemi4Actuel = ennemi4[BAS2]; } }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC] [(positionEnnemi4.y + 2) / TAILLE_BLOC + 1] <= 20) { direction3--;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[BAS]; else ennemi4Actuel = ennemi4[BAS2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC + 1] [(positionEnnemi4.y + 2) / TAILLE_BLOC + 1] <= 20) { direction3--;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[BAS]; else ennemi4Actuel = ennemi4[BAS2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC] [(positionEnnemi4.y + 2) / TAILLE_BLOC + 1] >= 46) { direction3--;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[BAS]; else ennemi4Actuel = ennemi4[BAS2]; }
         else if (carte[positionEnnemi4.x / TAILLE_BLOC + 1] [(positionEnnemi4.y + 2) / TAILLE_BLOC + 1] >= 46) { direction3--;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[BAS]; else ennemi4Actuel = ennemi4[BAS2]; }
        else positionEnnemi4.y += 2;
        if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[BAS]; } else { ennemi4Actuel = ennemi4[BAS2]; }
        }
        //Vers la droite si 3
        if (direction3 == 3) {
        if (positionEnnemi4.x >= orig_width - 35) { direction3++;  if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[DROITE]; } else { ennemi4Actuel = ennemi4[DROITE2]; } }
         else if (carte[(positionEnnemi4.x + 2) / TAILLE_BLOC + 1] [positionEnnemi4.y / TAILLE_BLOC] <= 20) { direction3++;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[DROITE]; else ennemi4Actuel = ennemi4[DROITE2]; }
         else if (carte[(positionEnnemi4.x + 2) / TAILLE_BLOC + 1] [positionEnnemi4.y / TAILLE_BLOC + 1] <= 20) { direction3++;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[DROITE]; else ennemi4Actuel = ennemi4[DROITE2]; }
         else if (carte[(positionEnnemi4.x + 2) / TAILLE_BLOC + 1] [positionEnnemi4.y / TAILLE_BLOC] >= 46) { direction3++;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[DROITE]; else ennemi4Actuel = ennemi4[DROITE2]; }
         else if (carte[(positionEnnemi4.x + 2) / TAILLE_BLOC + 1] [positionEnnemi4.y / TAILLE_BLOC + 1] >= 46) { direction3++;  if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[DROITE]; else ennemi4Actuel = ennemi4[DROITE2]; }
        else positionEnnemi4.x += 2;
        if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[DROITE]; } else { ennemi4Actuel = ennemi4[DROITE2]; }
        }
        //Vers la gauche si 4
        if (direction3 == 4) {
        if (positionEnnemi4.x <= 1) { direction3--;  if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[GAUCHE]; } else { ennemi4Actuel = ennemi4[GAUCHE2]; } }
         else if (carte[(positionEnnemi4.x - 2) / TAILLE_BLOC] [positionEnnemi4.y / TAILLE_BLOC] <= 20) { direction3--; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[GAUCHE]; else ennemi4Actuel = ennemi4[GAUCHE2]; }
         else if (carte[(positionEnnemi4.x - 2) / TAILLE_BLOC] [positionEnnemi4.y / TAILLE_BLOC + 1] <= 20) { direction3--; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[GAUCHE]; else ennemi4Actuel = ennemi4[GAUCHE2]; }
         else if (carte[(positionEnnemi4.x - 2) / TAILLE_BLOC] [positionEnnemi4.y / TAILLE_BLOC] >= 46) { direction3--; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[GAUCHE]; else ennemi4Actuel = ennemi4[GAUCHE2]; }
         else if (carte[(positionEnnemi4.x - 2) / TAILLE_BLOC] [positionEnnemi4.y / TAILLE_BLOC + 1] >= 46) { direction3--; if (animEnnemi4 == 1) ennemi4Actuel = ennemi4[GAUCHE]; else ennemi4Actuel = ennemi4[GAUCHE2]; }
        else positionEnnemi4.x -= 2;
        if (animEnnemi4 == 1) { ennemi4Actuel = ennemi4[GAUCHE]; } else { ennemi4Actuel = ennemi4[GAUCHE2]; }
        }
        }

            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionEnnemi4.x);
            y = (positionMario.y) - (positionEnnemi4.y);

            //1. S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25) {
                if (invincibilite == 0) {
                    if (animMario == 3) { if (ennemi4freeze2 == 0) { ennemi4freeze = ennemi4freeze2 = 1; ennemi4life -= 1;
                    if (ennemi4life <= 0) Mix_PlayChannel(-1, ekill, 0); else Mix_PlayChannel(-1, ehit, 0); tempsennemi4 = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } }


            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 30 && abs(y) < 25) {
                //A- On attaque, l'ennemi recule
                       //Si on regarde en haut :
                        if (  marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[EPEEBAS]; DeplacePlayer(HAUT, 1, ecran, carte); }
                            DeplaceEnnemi (4, HAUT, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, ennemi en hau, on se retourne
                            if ( y > 0) { marioActuel = mario[EPEEHAUT]; DeplacePlayer(BAS, 1, ecran, carte); }
                            DeplaceEnnemi (4, BAS, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a gauche, et que l'ennemi arrive a droite, on se retourne
                            if ( x > 0) { marioActuel = mario[EPEEGAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); }
                            DeplaceEnnemi (4, DROITE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive a gauche, on se retourne
                            if ( x < 0) { marioActuel = mario[EPEEDROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); }
                            DeplaceEnnemi (4, GAUCHE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Gauche
                            // Fin A- Attaque



                //B- On subit l'attaque, le player recule
                    else {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (4, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (4, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 1
                        else if (  marioActuel == mario[HAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (4, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (4, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 2
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (4, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (4, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 1
                        else if (  marioActuel == mario[BAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (4, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (4, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 2
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (4, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (4, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 1
                        else if (  marioActuel == mario[DROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive par a gauche, on se retourne
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (4, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (4, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 2
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (4, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (4, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 1
                        else if (  marioActuel == mario[GAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (4, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (4, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 2
                            }// Fin B- Subit les dommages


                 }


            // on teste si ennemi3 est encore vivant a la fin
            if (ennemi4life <= 0)
                { ennemi4vivant = 0; laisseItem(4); }


            }  // Fin test ennemi4*****************



        //******Deplacement et gestion de ennemi5 s'il est vivant**********
    if (ennemi5vivant == 1) {

        if ( tempsBougeEnnemi5 + 500 <= SDL_GetTicks() )
        { direction4 = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougeEnnemi5 = SDL_GetTicks(); }
        // ennemi5 se deplace sauf s'il est en freeze
        if (ennemi5freeze == 0) {
        //Vers le haut si 1
        if (direction4 == 1) {
        if (positionEnnemi5.y <= 1) { direction4 = 4; if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[HAUT]; } else { ennemi5Actuel = ennemi5[HAUT2]; } }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC] [(positionEnnemi5.y - 2) / TAILLE_BLOC] <= 20) { direction4 = 4; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[HAUT]; else ennemi5Actuel = ennemi5[HAUT2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC + 1] [(positionEnnemi5.y - 2) / TAILLE_BLOC] <= 20) { direction4 = 4; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[HAUT]; else ennemi5Actuel = ennemi5[HAUT2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC] [(positionEnnemi5.y - 2) / TAILLE_BLOC] >= 46) { direction4 = 4; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[HAUT]; else ennemi5Actuel = ennemi5[HAUT2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC + 1] [(positionEnnemi5.y - 2) / TAILLE_BLOC] >= 46) { direction4 = 4; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[HAUT]; else ennemi5Actuel = ennemi5[HAUT2]; }
        else positionEnnemi5.y -= 2;
        if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[HAUT]; } else { ennemi5Actuel = ennemi5[HAUT2]; }
        }
        //Vers le bas si 2
        if (direction4 == 2) {
        if (positionEnnemi5.y >= orig_height - 80) { direction4--;  if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[BAS]; } else { ennemi5Actuel = ennemi5[BAS2]; } }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC] [(positionEnnemi5.y + 2) / TAILLE_BLOC + 1] <= 20) { direction4--;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[BAS]; else ennemi5Actuel = ennemi5[BAS2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC + 1] [(positionEnnemi5.y + 2) / TAILLE_BLOC + 1] <= 20) { direction4--;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[BAS]; else ennemi5Actuel = ennemi5[BAS2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC] [(positionEnnemi5.y + 2) / TAILLE_BLOC + 1] >= 46) { direction4--;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[BAS]; else ennemi5Actuel = ennemi5[BAS2]; }
         else if (carte[positionEnnemi5.x / TAILLE_BLOC + 1] [(positionEnnemi5.y + 2) / TAILLE_BLOC + 1] >= 46) { direction4--;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[BAS]; else ennemi5Actuel = ennemi5[BAS2]; }
        else positionEnnemi5.y += 2;
        if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[BAS]; } else { ennemi5Actuel = ennemi5[BAS2]; }
        }
        //Vers la droite si 3
        if (direction4 == 3) {
        if (positionEnnemi5.x >= orig_width - 35) { direction4++;  if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[DROITE]; } else { ennemi5Actuel = ennemi5[DROITE2]; } }
         else if (carte[(positionEnnemi5.x + 2) / TAILLE_BLOC + 1] [positionEnnemi5.y / TAILLE_BLOC] <= 20) { direction4++;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[DROITE]; else ennemi5Actuel = ennemi5[DROITE2]; }
         else if (carte[(positionEnnemi5.x + 2) / TAILLE_BLOC + 1] [positionEnnemi5.y / TAILLE_BLOC + 1] <= 20) { direction4++;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[DROITE]; else ennemi5Actuel = ennemi5[DROITE2]; }
         else if (carte[(positionEnnemi5.x + 2) / TAILLE_BLOC + 1] [positionEnnemi5.y / TAILLE_BLOC] >= 46) { direction4++;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[DROITE]; else ennemi5Actuel = ennemi5[DROITE2]; }
         else if (carte[(positionEnnemi5.x + 2) / TAILLE_BLOC + 1] [positionEnnemi5.y / TAILLE_BLOC + 1] >= 46) { direction4++;  if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[DROITE]; else ennemi5Actuel = ennemi5[DROITE2]; }
        else positionEnnemi5.x += 2;
        if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[DROITE]; } else { ennemi5Actuel = ennemi5[DROITE2]; }
        }
        //Vers la gauche si 4
        if (direction4 == 4) {
        if (positionEnnemi5.x <= 1) { direction4--;  if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[GAUCHE]; } else { ennemi5Actuel = ennemi5[GAUCHE2]; } }
         else if (carte[(positionEnnemi5.x - 2) / TAILLE_BLOC] [positionEnnemi5.y / TAILLE_BLOC] <= 20) { direction4--; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[GAUCHE]; else ennemi5Actuel = ennemi5[GAUCHE2]; }
         else if (carte[(positionEnnemi5.x - 2) / TAILLE_BLOC] [positionEnnemi5.y / TAILLE_BLOC + 1] <= 20) { direction4--; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[GAUCHE]; else ennemi5Actuel = ennemi5[GAUCHE2]; }
         else if (carte[(positionEnnemi5.x - 2) / TAILLE_BLOC] [positionEnnemi5.y / TAILLE_BLOC] >= 46) { direction4--; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[GAUCHE]; else ennemi5Actuel = ennemi5[GAUCHE2]; }
         else if (carte[(positionEnnemi5.x - 2) / TAILLE_BLOC] [positionEnnemi5.y / TAILLE_BLOC + 1] >= 46) { direction4--; if (animEnnemi5 == 1) ennemi5Actuel = ennemi5[GAUCHE]; else ennemi5Actuel = ennemi5[GAUCHE2]; }
        else positionEnnemi5.x -= 2;
        if (animEnnemi5 == 1) { ennemi5Actuel = ennemi5[GAUCHE]; } else { ennemi5Actuel = ennemi5[GAUCHE2]; }
        }
        }

            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionEnnemi5.x);
            y = (positionMario.y) - (positionEnnemi5.y);

            //1. S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25) {
                if (invincibilite == 0) {
                    if (animMario == 3) { if (ennemi5freeze2 == 0) { ennemi5freeze = ennemi5freeze2 = 1; ennemi5life -= 1;
                    if (ennemi5life <= 0) Mix_PlayChannel(-1, ekill, 0); else Mix_PlayChannel(-1, ehit, 0); tempsennemi5 = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } }


            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 30 && abs(y) < 25) {
                //A- On attaque, l'ennemi recule
                       //Si on regarde en haut :
                        if (  marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[EPEEBAS]; DeplacePlayer(HAUT, 1, ecran, carte); }
                            DeplaceEnnemi (5, HAUT, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, ennemi en hau, on se retourne
                            if ( y > 0) { marioActuel = mario[EPEEHAUT]; DeplacePlayer(BAS, 1, ecran, carte); }
                            DeplaceEnnemi (5, BAS, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a gauche, et que l'ennemi arrive a droite, on se retourne
                            if ( x > 0) { marioActuel = mario[EPEEGAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); }
                            DeplaceEnnemi (5, DROITE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive a gauche, on se retourne
                            if ( x < 0) { marioActuel = mario[EPEEDROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); }
                            DeplaceEnnemi (5, GAUCHE, 2, ecran, carte);
                            DrawScreen1();
                            }
                            } //Fin Gauche
                            // Fin A- Attaque



                //B- On subit l'attaque, le player recule
                    else {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (5, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (5, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 1
                        else if (  marioActuel == mario[HAUT2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (5, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (5, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut 2
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (5, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (5, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 1
                        else if (  marioActuel == mario[BAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (5, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (5, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas 2
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (5, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (5, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 1
                        else if (  marioActuel == mario[DROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde a droite, et que l'ennemi arrive par a gauche, on se retourne
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (5, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (5, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite 2
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (5, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (5, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 1
                        else if (  marioActuel == mario[GAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (5, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (5, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche 2
                            }// Fin B- Subit les dommages


                 }


            // on teste si ennemi5 est encore vivant a la fin
            if (ennemi5life <= 0)
                { ennemi5vivant = 0; laisseItem(5); }


            }  // Fin test ennemi5*****************



   //******Deplacement et gestion du ----BOSS---- s'il est vivant**********
    if (bossvivant == 1) {
       if ( boss < bossaction ) { //si on ne l'a pas deja vaincu

            if ( bossArrive == 1 ) {

                Mix_PlayChannel(-1, dragonstart, 0);


                //si c'est la premiere fois qu'on voit le boss
                //on sauvegarde les warps
                saveWarpBas = warpBas;
                saveWarpHaut = warpHaut;
                saveWarpDroite = warpDroite;
                saveWarpGauche = warpGauche;
                //et on les met a zero, pour pieger le joueur
                warpBas = 0;
                warpHaut = 0;
                warpDroite = 0;
                warpGauche = 0;


                //Initialisation du deplacement : 1 = droite, 2 = gauche
                initDeplBoss = 1;
                bossArrive = 0;






                  }

        // BOSS se deplace à droite ou a gauche
            //Animation
       if (animBoss == 1) { bossActuel = bossPic[HAUT]; }
          else { bossActuel = bossPic[BAS]; }


            //Deplacement
       // if ( initDeplBoss == 1) { savePositionBoss = positionBoss; DeplaceBoss (DROITE, 2, ecran, carte);
      //      if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { initDeplBoss = 2; } }
       // else if ( initDeplBoss == 2) { savePositionBoss = positionBoss; DeplaceBoss (GAUCHE, 2, ecran, carte);
      //      if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { initDeplBoss = 1; } }



       //******Nouveau Deplacement********** On repique les valeurs de l'ennemi 5 par économie (et comme les 2 n'apparaissent pas simultanément (sinon ça fait drôle ;)

        if ( tempsBougeEnnemi5 + 500 <= SDL_GetTicks() )
        { direction4 = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougeEnnemi5 = SDL_GetTicks(); }

        //Vers le haut si 1
        if (direction4 == 1) {
        savePositionBoss = positionBoss; DeplaceBoss (HAUT, 2, ecran, carte);
            if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { direction4 = 3; }
        }
        //Vers le bas si 2
        else if (direction4 == 2) {
        savePositionBoss = positionBoss; DeplaceBoss (BAS, 2, ecran, carte);
            if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { direction4 = 4; }
        }
        //Vers la droite si 3
        else if (direction4 == 3) {
        savePositionBoss = positionBoss; DeplaceBoss (DROITE, 2, ecran, carte);
            if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { direction4 = 2; }
        }
        //Vers la gauche si 4
        else {
        savePositionBoss = positionBoss; DeplaceBoss (GAUCHE, 2, ecran, carte);
            if (savePositionBoss.x == positionBoss.x && savePositionBoss.y == positionBoss.y) { direction4 = 1; }
        }





            //Detection des collisions entre player et boss, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionBoss.x);
            y = (positionMario.y) - (positionBoss.y);

            //1. S'il y a collision, on change les points de vie :
             //Collision : 100 pixels a droite, 40 a gauche (x negatif)
        if ( x > 0) {
             if (abs(x) < 75 && abs(y) < 75) {
                 collision = 1;
                if (invincibilite == 0) {
                    if (animMario == 3) { if (bossfreeze2 == 0) { bossfreeze = bossfreeze2 = 1;
                    bosslife -= 1; if (bosslife <= 0) Mix_PlayChannel(-1, dragondies, 0); else Mix_PlayChannel(-1, dragonhit, 0); tempsboss = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } } }
        else {
             if (abs(x) < 29 && abs(y) < 75) {
                 collision = 1;
                if (invincibilite == 0) {
                    if (animMario == 3) { if (bossfreeze2 == 0) { bossfreeze = bossfreeze2 = 1;
                    bosslife -= 1; if (bosslife <= 0) Mix_PlayChannel(-1, dragondies, 0); else Mix_PlayChannel(-1, dragonhit, 0); tempsboss = SDL_GetTicks(); } }
                    else { coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks(); }
                } } }



            //2. S'il y a collision, le player est propulsé vers le bas :
            if (collision) {
                            for ( i = 0 ; i < 10 ; i++) {
                            DeplacePlayer(BAS, 2, ecran, carte);
                            AfficheNiveau(position, ecran, carte, level);
                            if (bossvivant == 1) { BlitSprite(bossActuel, ecran, &positionBoss); }
                            if (nbfireballs >= 1) { BlitSprite(fireballActuel, ecran, &positionFireball1); }
                            if (nbfireballs >= 2) { BlitSprite(fireballActuel, ecran, &positionFireball2); }
                            if (nbfireballs >= 3) { BlitSprite(fireballActuel, ecran, &positionFireball3); }
                            if (nbfireballs >= 4) { BlitSprite(fireballActuel, ecran, &positionFireball4); }
                            if ( weather >= 1 ) BlitSprite(tempsActuel, ecran, &positionPluie);
                            BlitSprite(marioActuel, ecran, &positionMario);
                            FlipScreen();
                            collision = 0;
                            }  }





            // on teste si BOSS est encore vivant a la fin
            if (bosslife <= 0)
                { bossvivant = 0;
                  nbfireballs = 0;

                //on remet les warps
                warpBas = saveWarpBas;
                warpHaut = saveWarpHaut;
                warpDroite = saveWarpDroite;
                warpGauche = saveWarpGauche;

                //on remet bossArrive a 1 pour le prochain
                bossArrive = 1;
                boss++;

                //On efface le boss
                AfficheNiveau(position, ecran, carte, level);
                BlitSprite(marioActuel, ecran, &positionMario);
                FlipScreen();


                if (boss < 3 || boss == 4 || boss == 6 || boss == 8)
                    { coeur=++coeurmax;
                    AfficheDialogues (ecran, police, 999);
                    }
                else if (boss == 3)
                    { power = 2;
                    AfficheDialogues (ecran, police, 998);
                    }
                else if (boss == 5)
                    { power = 3;
                    AfficheDialogues (ecran, police, 997);
                    }
                else if (boss == 7)
                    { baton = 1;
                    AfficheDialogues (ecran, police, 996);
                    }
                else if (boss == 9)
                    {
                        //Fin du jeu
                        SDL_Delay(4000);
                        loadSong(0);
                        fin ( ecran, &continuer );
                    }


                // Son a mettre avec objet laisse
                Mix_PlayChannel(-1, fanfare, 0);

                 }   //on augmente le compteur comptant les boss vaincus

            }   }  // Fin test Boss




    //************Gestion de la boule de feu ****************

    if (nbfireballs > 0) {

       if ( initFball == 1 ) {
          positionFireball2 = positionFireball1;
          positionFireball3 = positionFireball1;
          positionFireball4 = positionFireball1;

           //Deplacement Boules de feu deplFire1X : 1 a droite, 2 à gauche
                //deplFire1Y : 1 en bas, 2 en haut
                deplFire1X = 2;  deplFire1Y = 1;
                deplFire2X = 1;  deplFire2Y = 1;
                deplFire3X = 1;  deplFire3Y = 2;
                deplFire4X = 2;  deplFire4Y = 2;


          initFball = 0; }



                //Animation
       if (animfireball1 == 1) { fireballActuel = fireball[HAUT]; }
          else { fireballActuel = fireball[BAS]; }


        //Boule 1
        if (nbfireballs >= 1) {
         //Deplacement gauche/droite
        if ( deplFire1X == 1) { savePositionFireball1 = positionFireball1; DeplaceFireball (1, DROITE, 3, ecran, carte);
            if (savePositionFireball1.x == positionFireball1.x) { deplFire1X = 2; } }
        else if ( deplFire1X == 2) { savePositionFireball1 = positionFireball1; DeplaceFireball (1, GAUCHE, 3, ecran, carte);
            if (savePositionFireball1.x == positionFireball1.x) { deplFire1X = 1; } }

        //Deplacement haut/bas
        if ( deplFire1Y == 1) { savePositionFireball1 = positionFireball1; DeplaceFireball (1, HAUT, 3, ecran, carte);
            if (savePositionFireball1.y == positionFireball1.y) { deplFire1Y = 2; } }
        else if ( deplFire1Y == 2) { savePositionFireball1 = positionFireball1; DeplaceFireball (1, BAS, 3, ecran, carte);
            if (savePositionFireball1.y == positionFireball1.y) { deplFire1Y = 1; } }


        //Collisions avec la boule de feu
            x = (positionMario.x) - (positionFireball1.x);
            y = (positionMario.y) - (positionFireball1.y);

             if (abs(x) < 20 && abs(y) < 20) {
                 if (invincibilite == 0) {
                    coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks();
                } }
        }

            //Boule 2
        if (nbfireballs >= 2) {
         //Deplacement gauche/droite
        if ( deplFire2X == 1) { savePositionFireball2 = positionFireball2; DeplaceFireball (2, DROITE, 3, ecran, carte);
            if (savePositionFireball2.x == positionFireball2.x) { deplFire2X = 2; } }
        else if ( deplFire2X == 2) { savePositionFireball2 = positionFireball2; DeplaceFireball (2, GAUCHE, 3, ecran, carte);
            if (savePositionFireball2.x == positionFireball2.x) { deplFire2X = 1; } }

        //Deplacement haut/bas
        if ( deplFire2Y == 1) { savePositionFireball2 = positionFireball2; DeplaceFireball (2, HAUT, 3, ecran, carte);
            if (savePositionFireball2.y == positionFireball2.y) { deplFire2Y = 2; } }
        else if ( deplFire2Y == 2) { savePositionFireball2 = positionFireball2; DeplaceFireball (2, BAS, 3, ecran, carte);
            if (savePositionFireball2.y == positionFireball2.y) { deplFire2Y = 1; } }


        //Collisions avec la boule de feu
            x = (positionMario.x) - (positionFireball2.x);
            y = (positionMario.y) - (positionFireball2.y);

             if (abs(x) < 20 && abs(y) < 20) {
                 if (invincibilite == 0) {
                    coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks();
                } }
        }

    //Boule 3
        if (nbfireballs >= 3) {
         //Deplacement gauche/droite
        if ( deplFire3X == 1) { savePositionFireball3 = positionFireball3; DeplaceFireball (3, DROITE, 3, ecran, carte);
            if (savePositionFireball3.x == positionFireball3.x) { deplFire3X = 2; } }
        else if ( deplFire3X == 2) { savePositionFireball3 = positionFireball3; DeplaceFireball (3, GAUCHE, 3, ecran, carte);
            if (savePositionFireball3.x == positionFireball3.x) { deplFire3X = 1; } }

        //Deplacement haut/bas
        if ( deplFire3Y == 1) { savePositionFireball3 = positionFireball3; DeplaceFireball (3, HAUT, 3, ecran, carte);
            if (savePositionFireball3.y == positionFireball3.y) { deplFire3Y = 2; } }
        else if ( deplFire3Y == 2) { savePositionFireball3 = positionFireball3; DeplaceFireball (3, BAS, 3, ecran, carte);
            if (savePositionFireball3.y == positionFireball3.y) { deplFire3Y = 1; } }


        //Collisions avec la boule de feu
            x = (positionMario.x) - (positionFireball3.x);
            y = (positionMario.y) - (positionFireball3.y);

             if (abs(x) < 20 && abs(y) < 20) {
                 if (invincibilite == 0) {
                    coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks();
                } }
        }


    //Boule 4
        if (nbfireballs >= 4) {
         //Deplacement gauche/droite
        if ( deplFire4X == 1) { savePositionFireball4 = positionFireball4; DeplaceFireball (4, DROITE, 3, ecran, carte);
            if (savePositionFireball4.x == positionFireball4.x) { deplFire4X = 2; } }
        else if ( deplFire4X == 2) { savePositionFireball4 = positionFireball4; DeplaceFireball (4, GAUCHE, 3, ecran, carte);
            if (savePositionFireball4.x == positionFireball4.x) { deplFire4X = 1; } }

        //Deplacement haut/bas
        if ( deplFire4Y == 1) { savePositionFireball4 = positionFireball4; DeplaceFireball (4, HAUT, 3, ecran, carte);
            if (savePositionFireball4.y == positionFireball4.y) { deplFire4Y = 2; } }
        else if ( deplFire4Y == 2) { savePositionFireball4 = positionFireball4; DeplaceFireball (4, BAS, 3, ecran, carte);
            if (savePositionFireball4.y == positionFireball4.y) { deplFire4Y = 1; } }


        //Collisions avec la boule de feu
            x = (positionMario.x) - (positionFireball4.x);
            y = (positionMario.y) - (positionFireball4.y);

             if (abs(x) < 20 && abs(y) < 20) {
                 if (invincibilite == 0) {
                    coeur -= 1; Mix_PlayChannel(-1, hurt, 0); invincibilite = 1; tempsCoeur = SDL_GetTicks();
                } }
        }


         }

//**************************fin boules de feu*********************


    //************Gestion du baton de feu : la bouboule de fire !!  ****************

    if ( baton_used == 1 )

     {


        //Deplacement
        if ( direction_baton == HAUT )
        {
        savePositionBaton = PositionBaton;
        DeplaceBaton ( HAUT, 4, ecran, carte );
            if (savePositionBaton.y == PositionBaton.y)
            {
                baton_used = 0;
            }
        }

        else if ( direction_baton == BAS )
        {
        savePositionBaton = PositionBaton;
        DeplaceBaton ( BAS, 4, ecran, carte );
            if (savePositionBaton.y == PositionBaton.y)
            {
                baton_used = 0;
            }
        }

        else if ( direction_baton == DROITE )
        {
        savePositionBaton = PositionBaton;
        DeplaceBaton ( DROITE, 4, ecran, carte );
            if (savePositionBaton.x == PositionBaton.x)
            {
                baton_used = 0;
            }
        }

        else if ( direction_baton == GAUCHE )
        {
        savePositionBaton = PositionBaton;
        DeplaceBaton ( GAUCHE, 4, ecran, carte );
            if (savePositionBaton.x == PositionBaton.x)
            {
                baton_used = 0;
            }
        }


        //Gestion des collisions ennemis / boule de feu

            //Ennemi 1
            if ( ennemi1vivant == 1 )
            {


            x = (PositionBaton.x) - (positionEnnemi1.x);
            y = (PositionBaton.y) - (positionEnnemi1.y);

                        //S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25)
             {
                 if (ennemi1freeze2 == 0)
                 {
                     ennemi1freeze = ennemi1freeze2 = 1; ennemi1life -= 1;
                     if (ennemi1life <= 0) Mix_PlayChannel(-1, ekill, 0);
                     else Mix_PlayChannel(-1, ehit, 0);
                     tempsennemi1 = SDL_GetTicks();
                 }
            }

        // on teste si ennemi1 est encore vivant a la fin
             if (ennemi1life <= 0)
                { ennemi1vivant = 0; laisseItem(1); }

            }


            //Ennemi 2
            if ( ennemi2vivant == 1 )
            {

            x = (PositionBaton.x) - (positionEnnemi2.x);
            y = (PositionBaton.y) - (positionEnnemi2.y);

                        //S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25)
             {
                 if (ennemi2freeze2 == 0)
                 {
                     ennemi2freeze = ennemi2freeze2 = 1; ennemi2life -= 1;
                     if (ennemi2life <= 0) Mix_PlayChannel(-1, ekill, 0);
                     else Mix_PlayChannel(-1, ehit, 0);
                     tempsennemi2 = SDL_GetTicks();
                 }
            }

        // on teste si ennemi2 est encore vivant a la fin
             if (ennemi2life <= 0)
                { ennemi2vivant = 0; laisseItem(2); }

            }


            //Ennemi 3
            if ( ennemi3vivant == 1 )
            {

            x = (PositionBaton.x) - (positionEnnemi3.x);
            y = (PositionBaton.y) - (positionEnnemi3.y);

                        //S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25)
             {
                 if (ennemi3freeze2 == 0)
                 {
                     ennemi3freeze = ennemi3freeze2 = 1; ennemi3life -= 1;
                     if (ennemi3life <= 0) Mix_PlayChannel(-1, ekill, 0);
                     else Mix_PlayChannel(-1, ehit, 0);
                     tempsennemi3 = SDL_GetTicks();
                 }
            }

        // on teste si ennemi3 est encore vivant a la fin
             if (ennemi3life <= 0)
                { ennemi3vivant = 0; laisseItem(3); }
            }


            //Ennemi 4
            if ( ennemi4vivant == 1 )
            {

            x = (PositionBaton.x) - (positionEnnemi4.x);
            y = (PositionBaton.y) - (positionEnnemi4.y);

                        //S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25)
             {
                 if (ennemi4freeze2 == 0)
                 {
                     ennemi4freeze = ennemi4freeze2 = 1; ennemi4life -= 1;
                     if (ennemi4life <= 0) Mix_PlayChannel(-1, ekill, 0);
                     else Mix_PlayChannel(-1, ehit, 0);
                     tempsennemi4 = SDL_GetTicks();
                 }
            }

        // on teste si ennemi4 est encore vivant a la fin
             if (ennemi4life <= 0)
                { ennemi4vivant = 0; laisseItem(4); }
            }


            //Ennemi 5
            if ( ennemi5vivant == 1 )
            {

            x = (PositionBaton.x) - (positionEnnemi5.x);
            y = (PositionBaton.y) - (positionEnnemi5.y);

                        //S'il y a collision, on change les points de vie :
             if (abs(x) < 30 && abs(y) < 25)
             {
                 if (ennemi5freeze2 == 0)
                 {
                     ennemi5freeze = ennemi5freeze2 = 1; ennemi5life -= 1;
                     if (ennemi5life <= 0) Mix_PlayChannel(-1, ekill, 0);
                     else Mix_PlayChannel(-1, ehit, 0);
                     tempsennemi5 = SDL_GetTicks();
                 }
            }

        // on teste si ennemi5 est encore vivant a la fin
             if (ennemi5life <= 0)
                { ennemi5vivant = 0; laisseItem(5); }
            }

    }
//Fin gestion de la boule de feu du baton de feu



//******Deplacement et gestion de PNJ1 s'il est vivant**********
    if (pnj1vivant == 1) {
        //on tire une direction au hasard
        if ( tempsBougePnj1 + 2000 <= SDL_GetTicks() )
        { direction = (rand() % (MAX - MIN + 1)) + MIN;
        tempsBougePnj1 = SDL_GetTicks(); }
        //Vers le haut si 1
        if (direction == 1) {
        if (positionPnj1.y <= 1) { direction++; if (animPnj1 == 1) { pnj1Actuel = pnj1[HAUT]; } else { pnj1Actuel = pnj1[HAUT2]; } }
         else if (carte[positionPnj1.x / TAILLE_BLOC] [(positionPnj1.y - 2) / TAILLE_BLOC] <= 20) { direction++; if (animPnj1 == 1) pnj1Actuel = pnj1[HAUT]; else pnj1Actuel = pnj1[HAUT2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC + 1] [(positionPnj1.y - 2) / TAILLE_BLOC] <= 20) { direction++; if (animPnj1 == 1) pnj1Actuel = pnj1[HAUT]; else pnj1Actuel = pnj1[HAUT2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC] [(positionPnj1.y - 2) / TAILLE_BLOC] >= 46) { direction++; if (animPnj1 == 1) pnj1Actuel = pnj1[HAUT]; else pnj1Actuel = pnj1[HAUT2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC + 1] [(positionPnj1.y - 2) / TAILLE_BLOC] >= 46) { direction++; if (animPnj1 == 1) pnj1Actuel = pnj1[HAUT]; else pnj1Actuel = pnj1[HAUT2]; }
        else positionPnj1.y -= 1;
        if (animPnj1 == 1) { pnj1Actuel = pnj1[HAUT]; } else { pnj1Actuel = pnj1[HAUT2]; }
        }
        //Vers le bas si 2
        if (direction == 2) {
        if (positionPnj1.y >= orig_height - 80) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[BAS]; } else { pnj1Actuel = pnj1[BAS2]; } }
         else if (carte[positionPnj1.x / TAILLE_BLOC] [(positionPnj1.y + 2) / TAILLE_BLOC + 1] <= 20) { direction++;  if (animPnj1 == 1) pnj1Actuel = pnj1[BAS]; else pnj1Actuel = pnj1[BAS2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC + 1] [(positionPnj1.y + 2) / TAILLE_BLOC + 1] <= 20) { direction++;  if (animPnj1 == 1) pnj1Actuel = pnj1[BAS]; else pnj1Actuel = pnj1[BAS2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC] [(positionPnj1.y + 2) / TAILLE_BLOC + 1] >= 46) { direction++;  if (animPnj1 == 1) pnj1Actuel = pnj1[BAS]; else pnj1Actuel = pnj1[BAS2]; }
         else if (carte[positionPnj1.x / TAILLE_BLOC + 1] [(positionPnj1.y + 2) / TAILLE_BLOC + 1] >= 46) { direction++;  if (animPnj1 == 1) pnj1Actuel = pnj1[BAS]; else pnj1Actuel = pnj1[BAS2]; }
        else positionPnj1.y += 1;
        if (animPnj1 == 1) { pnj1Actuel = pnj1[BAS]; } else { pnj1Actuel = pnj1[BAS2]; }
        }
        //Vers la droite si 3
        if (direction == 3) {
        if (positionPnj1.x >= orig_width - 35) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; } }
         else if (carte[(positionPnj1.x + 2) / TAILLE_BLOC + 1] [positionPnj1.y / TAILLE_BLOC] <= 20) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; } }
         else if (carte[(positionPnj1.x + 2) / TAILLE_BLOC + 1] [positionPnj1.y / TAILLE_BLOC + 1] <= 20) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; } }
         else if (carte[(positionPnj1.x + 2) / TAILLE_BLOC + 1] [positionPnj1.y / TAILLE_BLOC] >= 46) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; } }
         else if (carte[(positionPnj1.x + 2) / TAILLE_BLOC + 1] [positionPnj1.y / TAILLE_BLOC + 1] >= 46) { direction++;  if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; } }
        else positionPnj1.x += 1;
        if (animPnj1 == 1) { pnj1Actuel = pnj1[DROITE]; } else { pnj1Actuel = pnj1[DROITE2]; }
        }
        //Vers la gauche si 4
        if (direction == 4) {
        if (positionPnj1.x <= 1) { direction = 1;  if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; } }
         else if (carte[(positionPnj1.x - 2) / TAILLE_BLOC] [positionPnj1.y / TAILLE_BLOC] <= 20) { direction = 1;  if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; } }
         else if (carte[(positionPnj1.x - 2) / TAILLE_BLOC] [positionPnj1.y / TAILLE_BLOC + 1] <= 20) { direction = 1;  if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; } }
         else if (carte[(positionPnj1.x - 2) / TAILLE_BLOC] [positionPnj1.y / TAILLE_BLOC] >= 46) { direction = 1;  if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; } }
         else if (carte[(positionPnj1.x - 2) / TAILLE_BLOC] [positionPnj1.y / TAILLE_BLOC + 1] >= 46) { direction = 1;  if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; } }
        else positionPnj1.x -= 1;
        if (animPnj1 == 1) { pnj1Actuel = pnj1[GAUCHE]; } else { pnj1Actuel = pnj1[GAUCHE2]; }
        }


            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionPnj1.x);
            y = (positionMario.y) - (positionPnj1.y);

            //1. S'il y a collision, on joue un son :
             if (abs(x) < 20 && abs(y) < 20) {
                Mix_PlayChannel(-1, ehit, 0);
                if (keystate[SDLK_SPACE])
                {
                if ( pnj1action == 0)
                AfficheDialogues (ecran, police, dialogue1);
                else continuer = shop ( ecran, police, &potion, &coeur, &coeurmax, &money, &level, &power, &boss, &key, &baton );
                }
                else if ( SDL_JoystickGetButton(joystick, 0))
                {
                if ( pnj1action == 0)
                AfficheDialogues (ecran, police, dialogue1);
                else continuer = shop ( ecran, police, &potion, &coeur, &coeurmax, &money, &level, &power, &boss, &key, &baton );
                }

                }


            //2. S'il y a collision, on sépare les belligérants :
            if (abs(x) < 20 && abs(y) < 20) {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] || marioActuel == mario[HAUT2]
                           || marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2]) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte); DeplaceEnnemi (6, BAS, 1, ecran, carte); }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  DeplaceEnnemi (6, HAUT, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] || marioActuel == mario[BAS2]
                           || marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte); DeplaceEnnemi (6, HAUT, 1, ecran, carte); }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);  DeplaceEnnemi (6, BAS, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] || marioActuel == mario[DROITE2]
                           || marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte); DeplaceEnnemi (6, GAUCHE, 1, ecran, carte); }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);  DeplaceEnnemi (6, DROITE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] || marioActuel == mario[GAUCHE2]
                           || marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte); DeplaceEnnemi (6, DROITE, 1, ecran, carte); }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);  DeplaceEnnemi (6, GAUCHE, 1, ecran, carte); }
                            DrawScreen1();
                            }
                            } //Fin Gauche


                 }


            }  // Fin test PNJ1*****************


//******Deplacement et gestion de PNJ2 s'il est vivant**********
    if (pnj2vivant == 1) {

            //Detection des collisions entre player et ennemi2, on affine selon leurs coordonnees dans le rectangle 34*34
            x = (positionMario.x) - (positionPnj2.x);
            y = (positionMario.y) - (positionPnj2.y);

            //1. S'il y a collision, on joue un son :
             if (abs(x) < 20 && abs(y) < 20) {
                Mix_PlayChannel(-1, ehit, 0);

                if (keystate[SDLK_SPACE])
                {
                if ( pnj2action == 0)
                AfficheDialogues (ecran, police, dialogue2);
                else continuer = shop ( ecran, police, &potion, &coeur, &coeurmax, &money, &level, &power, &boss, &key, &baton );
                }
                else if ( SDL_JoystickGetButton(joystick, 0))
                {
                if ( pnj2action == 0)
                AfficheDialogues (ecran, police, dialogue2);
                else continuer = shop ( ecran, police, &potion, &coeur, &coeurmax, &money, &level, &power, &boss, &key, &baton );
                }

            }


            //2. S'il y a collision, on sépare le player :
            if (abs(x) < 20 && abs(y) < 20) {
                    //Si on regarde en haut :
                        if (  marioActuel == mario[HAUT] || marioActuel == mario[HAUT2]
                           || marioActuel == mario[EPEEHAUT] || marioActuel == mario[EPEEHAUT2]) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en haut, et que l'ennemi arrive par le bas, on se retourne
                            if ( y < 0) { marioActuel = mario[BAS]; DeplacePlayer(HAUT, 1, ecran, carte);  }
                            else { DeplacePlayer(BAS, 1, ecran, carte);  }
                            DrawScreen1();
                            }
                            } //Fin Haut
                            //Si on regarde en bas :
                        else if (  marioActuel == mario[BAS] || marioActuel == mario[BAS2]
                           || marioActuel == mario[EPEEBAS] || marioActuel == mario[EPEEBAS2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            //Si on regarde en bas, et que l'ennemi arrive par le haut, on se retourne
                            if ( y > 0) { marioActuel = mario[HAUT]; DeplacePlayer(BAS, 1, ecran, carte);  }
                            else { DeplacePlayer(HAUT, 1, ecran, carte);   }
                            DrawScreen1();
                            }
                            } //Fin Bas
                            //Si on regarde a droite :
                        else if (  marioActuel == mario[DROITE] || marioActuel == mario[DROITE2]
                           || marioActuel == mario[EPEEDROITE] || marioActuel == mario[EPEEDROITE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x > 0) { marioActuel = mario[GAUCHE]; DeplacePlayer(DROITE, 1, ecran, carte);  }
                            else { DeplacePlayer(GAUCHE, 1, ecran, carte);   }
                            DrawScreen1();
                            }
                            } //Fin droite
                            //Si on regarde a gauche :
                        else if (  marioActuel == mario[GAUCHE] || marioActuel == mario[GAUCHE2]
                           || marioActuel == mario[EPEEGAUCHE] || marioActuel == mario[EPEEGAUCHE2] ) {
                            for ( i = 0 ; i < 15 ; i++) {
                            if ( x < 0) { marioActuel = mario[DROITE]; DeplacePlayer(GAUCHE, 1, ecran, carte);  }
                            else { DeplacePlayer(DROITE, 1, ecran, carte);   }
                            DrawScreen1();
                            }
                            } //Fin Gauche


                 }


            }  // Fin test PNJ2*****************



//**********Gestion collision items************************
     //Detection des collisions avec item1
            x = (positionMario.x) - (item1.positionItem.x);
            y = (positionMario.y) - (item1.positionItem.y);

            //S'il y a collision et si l'item existe :
             if (abs(x) < 30 && abs(y) < 30) {
                if ( item1.itemExiste == 1)
                { item1.itemExiste = 0; Mix_PlayChannel(-1, item_sound, 0);
                if ( item1.itemType == 1 ) { coeur++;  if ( coeur > coeurmax) coeur = coeurmax; }
                if ( item1.itemType == 2 ) { money += (rand() % (20 - 1 + 1)) + 1;   }
                if ( item1.itemType == 3 ) { potion++;   }
                if ( item1.itemType == 4 ) { key++;   }
                    }
                    }
            if ( potion > 9) potion = 9;
            if ( key > 9) key = 9;
            if ( money > 999) money = 999;


//**********Gestion collision warpZone************************

            //S'il y a collision
        if ( marioActuel == mario [HAUT] || marioActuel == mario [HAUT2]
         ||  marioActuel == mario [EPEEHAUT] || marioActuel == mario [EPEEHAUT2] ) {
             if ( positionMario.x >= positionWarp.x      &&
                  positionMario.x <= positionWarp.x + 60 &&
                  positionMario.y <= positionWarp.y      &&
                  positionMario.y >= positionWarp.y - 10

                 ) {
                if ( warpZone == 1) {

            positionMario.x = positionWarp.x;
            positionMario.y = positionWarp.y;
            level = wlevel;
            chargerNiveau(carte, level);
            chargerDataNiveau (level);
                }  } }

        else if ( marioActuel == mario [BAS] || marioActuel == mario [BAS2]
              ||  marioActuel == mario [EPEEBAS] || marioActuel == mario [EPEEBAS2] ) {
             if ( positionMario.x >= positionWarp.x      &&
                  positionMario.x <= positionWarp.x + 60 &&
                  positionMario.y >= positionWarp.y - 40 &&
                  positionMario.y <= positionWarp.y
                 ) {
                if ( warpZone == 1) {

            positionMario.x = positionWarp.x;
            positionMario.y = positionWarp.y;
            level = wlevel;
            chargerNiveau(carte, level);
            chargerDataNiveau (level);
                }  } }

    // Mise a jour de l'affichage
    AfficheNiveau(position, ecran, carte, level);

    //Gestion de la santé
    if (coeur == 1) {
    if (tempsSante + 500 < SDL_GetTicks()) {
        tempsSante = SDL_GetTicks(); Mix_PlayChannel(-1, LowHealth, 0);
    }  }
    if (coeur < 0) coeur = 0;

    //Utilisation potion
    if ( coeur <= 0 ) {
        if ( potion >= 1)
        { potion--; coeur = coeurmax;
        Mix_PlayChannel(-1, potion_sound, 0); }

        else {
                loadSong(0);

                game_over( ecran, &coeur, &continuer, &potion, &coeurmax, &money, &level, &power, &boss, &key, &baton );
                chargerNiveau(carte, level);
                chargerDataNiveau (level);
                AfficheNiveau(position, ecran, carte, level);
                positionMario.x = orig_width / 2 - 35 / 2;
                positionMario.y = orig_height / 2 - 35 / 2;


                loadSong(musique);


    } }

           // Affichage du fond (vie, etc...)
    BlitSprite(fond, ecran, &positionFond);

    if (coeur < 6) {
    for ( j = coeur - 1 ; j >= 0 ; j-- )
    { positionCoeur.x = 8 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
    }

    //S'il y a de 6 à 10 coeurs :
    else if (coeur < 11) {
        for ( j = 4 ; j >= 0 ; j-- )
    { positionCoeur.x = 8 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
        for ( j = coeur - 6 ; j >= 0 ; j-- )
    { positionCoeur.x = 12 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
                }

    //S'il y a de 11 à 15 coeurs :
    else  {
        for ( j = 4 ; j >= 0 ; j-- )
    { positionCoeur.x = 8 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
        for ( j = 4 ; j >= 0 ; j-- )
    { positionCoeur.x = 12 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
        for ( j = coeur - 11 ; j >= 0 ; j-- )
    { positionCoeur.x = 16 + (j * 26);
      positionCoeur.y = 433;
      BlitSprite(coeurRouge, ecran, &positionCoeur); }
                    }



            // Affichage du nombre de pieces, potions, cles, etc...
    // 1. Argent (money)
    SDL_Rect pos;
    pos.x = 380;
    pos.y = 433;
    char argent[50];
    sprintf(argent, "%d", money);
    AfficheTexteItems (ecran, police, argent, pos);
    // 2. Cles (keys)
    pos.x = 328;
    pos.y = 433;
    sprintf(argent, "%d", key);
    AfficheTexteItems (ecran, police, argent, pos);
    // 3. potion)
    pos.x = 280;
    pos.y = 433;
    sprintf(argent, "%d", potion);
    AfficheTexteItems (ecran, police, argent, pos);
    // 4. Puissance epee
    if ( power == 1 ) puiss_epeeActuel = puiss_epee[0];
    else if ( power == 2 ) puiss_epeeActuel = puiss_epee[1];
    else if ( power == 3 ) puiss_epeeActuel = puiss_epee[2];
    BlitSprite(puiss_epeeActuel, ecran, &positionPuiss_epee);
    // Affichage baton de feu
    if (baton == 1)
    { SDL_Rect positionFirestick;
    positionFirestick.x = 192;
    positionFirestick.y = 431;
    BlitSprite(firestick, ecran, &positionFirestick); }


    //Affichage items s'ils existent
   if ( item1.itemExiste == 1 ) {
        if ( item1.itemType == 1) BlitSprite(item[0], ecran, &item1.positionItem);
        if ( item1.itemType == 2) BlitSprite(item[1], ecran, &item1.positionItem);
        if ( item1.itemType == 3) BlitSprite(item[2], ecran, &item1.positionItem);
        if ( item1.itemType == 4) BlitSprite(item[3], ecran, &item1.positionItem);
        }




    //Affichage ennemis si vivants
    if (ennemi1vivant == 1) { BlitSprite(ennemi1Actuel, ecran, &positionEnnemi1); }
    if (ennemi2vivant == 1) { BlitSprite(ennemi2Actuel, ecran, &positionEnnemi2); }
    if (ennemi3vivant == 1) { BlitSprite(ennemi3Actuel, ecran, &positionEnnemi3); }
    if (ennemi4vivant == 1) { BlitSprite(ennemi4Actuel, ecran, &positionEnnemi4); }
    if (ennemi5vivant == 1) { BlitSprite(ennemi5Actuel, ecran, &positionEnnemi5); }
    if (bossvivant == 1) { if ( boss < bossaction ) { BlitSprite(bossActuel, ecran, &positionBoss); } }
    if ( nbfireballs >= 1 ) BlitSprite(fireballActuel, ecran, &positionFireball1);
    if ( nbfireballs >= 2 ) BlitSprite(fireballActuel, ecran, &positionFireball2);
    if ( nbfireballs >= 3 ) BlitSprite(fireballActuel, ecran, &positionFireball3);
    if ( nbfireballs >= 4 ) BlitSprite(fireballActuel, ecran, &positionFireball4);
    if (pnj1vivant == 1) { BlitSprite(pnj1Actuel, ecran, &positionPnj1); }
    if (pnj2vivant == 1) { BlitSprite(pnj2Actuel, ecran, &positionPnj2); }

    //Affichage boule de feu du baton de feu
    if ( baton == 1)
    {
        if (baton_used == 1)
        {
            BlitSprite(baton_img, ecran, &PositionBaton);
        }
    }


    BlitSprite(marioActuel, ecran, &positionMario); /* On place mario à sa nouvelle position */

    //Pluie
    if ( weather >= 1 ) { BlitSprite(tempsActuel, ecran, &positionPluie);
        if ( tempsMusiquePluie + 6000 < SDL_GetTicks() ) { Mix_PlayChannel(-1, rain, 0); tempsMusiquePluie = SDL_GetTicks(); } }

    FlipScreen(); /* On met à jour l'affichage */


    //Pour avoir 60 fps : il faut un tour de boucle tous les 16ms (16.6 exactement)
if ( fps )
{
    if( SDL_GetTicks() < fpstime )
    { delai = fpstime - SDL_GetTicks();
    }
    else delai = 1;

    SDL_Delay(delai);

    fpstime = SDL_GetTicks() + 16;
}
else SDL_Delay(1);



        }



        //On libère la mémoire

    freeTileset();

    for (i = 0 ; i < 16 ; i++)
       { SDL_FreeSurface(mario[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(ennemi1[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(ennemi2[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(ennemi3[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(ennemi4[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(ennemi5[i]); }

    for (i = 0 ; i < 8 ; i++)
       { SDL_FreeSurface(pnj1[i]); }

    SDL_FreeSurface(pnj2);

    for (i = 0 ; i < 2 ; i++)
       { SDL_FreeSurface(bossPic[i]); }
    for (i = 0 ; i < 2 ; i++)
       { SDL_FreeSurface(fireball[i]); }

    for (i = 0 ; i < 4 ; i++)
       { SDL_FreeSurface(item[i]); }

    for (i = 0 ; i < 4 ; i++)
       { SDL_FreeSurface(temps[i]); }
    SDL_FreeSurface(orage);

    for (i = 0 ; i < 3 ; i++)
       { SDL_FreeSurface(puiss_epee[i]); }

    SDL_FreeSurface(baton_img);


    Mix_HaltChannel(-1);

    /* On libère les sons et on ferme FMOD */
    Mix_FreeChunk(sword);
    Mix_FreeChunk(ah);
    Mix_FreeChunk(hurt);
    Mix_FreeChunk(ehit);
    Mix_FreeChunk(ekill);
    Mix_FreeChunk(LowHealth);
    Mix_FreeChunk(item_sound);
    Mix_FreeChunk(fanfare);
    Mix_FreeChunk(dragondies);
    Mix_FreeChunk(dragonhit);
    Mix_FreeChunk(dragonstart);
    Mix_FreeChunk(rain);
    Mix_FreeChunk(potion_sound);


    freeMusic();

#if SDL_VERSIONNUM(SDL_MIXER_MAJOR_VERSION, SDL_MIXER_MINOR_VERSION, SDL_MIXER_PATCHLEVEL) >= SDL_VERSIONNUM(1, 2, 10)
    while (Mix_Init(0)) Mix_Quit();
#endif

    Mix_CloseAudio();

    TTF_CloseFont(police);
    TTF_Quit();

    //23 dec 09 : On quitte la gestion des joysticks ;)
    SDL_JoystickClose(joystick);

    SDL_Quit();




    return EXIT_SUCCESS;
}



