#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cctype>
#include <thread>
#include <iomanip>
#include <map>
#include <algorithm>
#include <time.h>

#define LETTDISP 8
const int R = 17;
const int C = 17;

#define LIV 3
#define TOTSCA 2

bool prima=true;
char Jolly[2]={' ',' '};
int NumeroGiocatori;
int Giocatore=1;

int punteggiosingolaparola=0;

char sct1=' ';
char sct2=' ';

// TURNI
// Gestione dei punteggi
int PunteggiGiocatori[4]={0,0,0,0};

// Gestione dei leggii
string Leggii[4]={"        ","        ","        ","        "};

// SACCHETTO
// Gestione del sacchetto delle lettere
typedef struct
{
    char Lettera;
    int num;
    int val;
} elemSacc;

vector<elemSacc> Sacchetto;

// GESTIONE DEL DIZIONARIO
// Mappe che contengono il dizionario
map<string, string> Dizionario;
map<string, string> DizionarioGen;
map<string, string> DizionarioBase;

// Struttura di una regola per la generazione del dizionario
typedef struct
{
    string presuf;
    string togli;
    string metti;
    string dove;
} regola;

// Mappe che contengono le regole
map <char, string> CombinaRegole;
multimap <string, regola> Regole;
multimap <string, regola> RegoleEsplose;

// GRIGLIA
// Matrice tridimensionale per la rappresentazione della griglia
char Griglia[R][C][LIV];

// FORMAZIONE DELLE PAROLE
// Mappe relative alle combinazioni di lettere che possono formare una parola
//map<string, int> ParolePossibili;
//map <string, int> Combinazioni;

// Gestione delle intersezioni
bool bonusnosc=false;

typedef struct
{
    string parola;
    int punteggio;
    string LeggioR;
    int riga;
    int colonna;
    bool maxdirvert;
} DatiParola;

DatiParola ParolaMx={"",0,"",0,0,false};

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QInputDialog>
#include <QString>
