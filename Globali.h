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
#include <future>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

#define LETTDISP 8
#define R 17
#define C 17
#define LIV 3
#define TOTSCA 2
bool prima=true;
char ScarabeoA=' ';
char ScarabeoB=' ';
int numgioc;
int Giocatore=1;
int punteggiosingolaparola=0;
char sct1=' ';
char sct2=' ';

// TURNI
// Gestione dei punteggi
int PunteggioA=0;
int PunteggioB=0;
int PunteggioC=0;
int PunteggioD=0;

// Gestione dei leggii
string PrimoLeggio="        "; // primo giocatore
string SecondoLeggio="        "; // secondo giocatore
string TerzoLeggio="        "; // terzo giocatore
string QuartoLeggio="        "; // quarto giocatore

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
multimap <string, regola> Regole; // Nome - altro
multimap <string, regola> RegoleEsplose;

// GRIGLIA
// Matrice tridimensionale per la rappresentazione della griglia
char Griglia[R][C][LIV];

// FORMAZIONE DELLE PAROLE
// Mappe relative alle combinazioni di lettere che possono formare una parola
map<string, int> ParolePossibili;
map <string, int> Combinazioni;

// PAROLA MIGLIORE (E SUE INTERSEZIONI)
// Gestione della parola migliore e delle sue caratteristiche
string parolamax=""; // Parola migliore
//int punteggiomax=0; // Punteggio della parola migliore
int ptmx=0;
int rigamax=0; // Riga di inizio della parola migliore
int colonnamax=0; // Riga di fine della parola migliore
bool maxvert=false; // Se la parola con il punteggio massimo è verticale allora diventa true

// Gestione delle intersezioni
int totperp=0;
int punteggioperp=0;
int scorriperp;
int lettereinserite=0;
bool bonusnosc=false;

string LeggioP;
int inizioparola, fineparola;

typedef struct
{
    string parola;
    int punteggio;
    string LeggioR;
    int riga;
    int colonna;
    bool maxdirvert;
} DatiParola;

DatiParola OrS;
DatiParola OrP;
DatiParola VerS;
DatiParola VerP;

unsigned int PosSpazi[LETTDISP]; // Contiene le posizioni degli spazi dell'intervallo considerato

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QInputDialog>
#include <QString>

