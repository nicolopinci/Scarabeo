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

// Gestione delle intersezioni
bool bonusnosc=false;

// MEMORIZZAZIONE DEI DATI DI UNA PAROLA
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

// MEMORIZZAZIONE EFFICIENTE DELLE PAROLE
vector<map<string, string>::iterator> MatriceMP[26][9];

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QInputDialog>
#include <QString>
