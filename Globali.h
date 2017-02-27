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

// GRIGLIA
// Matrice tridimensionale per la rappresentazione della griglia
char Griglia[R][C][LIV];

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

// INFORMAZIONI SULLA MANO
typedef struct
{
    bool prima=true;
    char Jolly[2][2]={{' ',' '},{' ',' '}};
    int NumeroGiocatori;
    int Giocatore=1;
    std::string Leggii[4]={"        ","        ","        ","        "};
    int PunteggiGiocatori[4]={0,0,0,0};
    DatiParola ParolaMx={"",0,"",0,0,false};
    int punteggiosingolaparola=0;
    bool bonusnosc=false;

} Mano;

Mano ManoCorrente;


// MEMORIZZAZIONE EFFICIENTE DELLE PAROLE
vector<map<string, string>::iterator> MatriceMP[9][26];

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QInputDialog>
#include <QString>
