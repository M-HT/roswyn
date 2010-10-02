

#ifndef DEF_FICHIERS
#define DEF_FICHIERS

    int readNumber(FILE *fichier, int length);
    int readSmallInteger(FILE *fichier, int maxvalue);
    int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR], int level);
    int chargerDataNiveau(int level);
    int readCoffres(FILE *fichier);
    int writeCoffres(FILE *fichier);
    int readSwitchs(FILE *fichier);
    int writeSwitchs(FILE *fichier);
    int InitCoffres ( );
    int InitSwitchs();
    int ValeurCoffre( int level );
    int OuvreCoffre( int niveau );
    int ValeurSwitch( int level );
    int OuvreSwitch( );

#endif
