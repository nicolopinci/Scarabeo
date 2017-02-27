void GeneraParoleComplete(string stringa, map<string, int>& ParolePossibili)
{
    /* Generazione di tutte le parole possibili (riferito alla prima parola)
     * in base alle combinazioni di lettere che si possono formare con le lettere del leggio */

    string sottostringa;
    sort(stringa.begin(), stringa.end());
    pair<string,int> elemento;
    int scarabeo;
    do
    {
        for(int i=1;i<LETTDISP;++i)
        {
            sottostringa="";
            scarabeo=0;
            for(int j=0;j<=i;++j)
            {
                sottostringa=sottostringa+stringa[j];
                if(stringa[j]=='#')
                {
                    ++scarabeo; // Numero di scarabei (o jolly) presenti sul leggio
                }

            }
            if(scarabeo==0)
            {
                if(sottostringa.length()<=3 || (ParolaEsiste(sottostringa, Dizionario))) // Controlla se la parola esiste solo nel caso in cui sia più lunga di tre lettere
                {
                    elemento={sottostringa, scarabeo};
                    ParolePossibili.insert(elemento);
                }
            }
            else
            {
                elemento={sottostringa, scarabeo};
                ParolePossibili.insert(elemento);
            }

        }
    }
    while(next_permutation(stringa.begin(), stringa.end())); // Funzione STL
}

void SvuotaPossibili(map<string, int>& ParolePossibili)
{
    auto iteratore = ParolePossibili.begin();
    while (iteratore != ParolePossibili.end())
    {

        iteratore = ParolePossibili.erase(iteratore);

    }
}

void TrovaPrimaMigliore(map<string, int>& ParolePossibili)
{
    int punti=0;

    int moltiplicatore=1;
    int partenza=0;

    ManoCorrente.ParolaMx.punteggio=0;

    for(auto p:ParolePossibili) // Per ogni parola
    {
        partenza=8-p.first.length()+1;
        for(int i=partenza;i<=8;++i) // Per ogni possibile punto di partenza della parola
        {
            moltiplicatore=1;
            punti=0;
            for(unsigned int l=i;l<i+p.first.length();++l) // Per ogni lettera della parola
            {
                //Cerca punteggio della lettera
                if(Griglia[8][l][1]!=' ')
                {
                    punti=punti+ValoreLettera(p.first[l-i], Sacchetto)*(int)(Griglia[8][l][1]-'0');
                }
                else if(Griglia[8][l][2]!=' ')
                {
                    moltiplicatore=moltiplicatore*(int)(Griglia[8][l][2]-'0');
                }
                else
                {
                    punti=punti+ValoreLettera(p.first[l-i], Sacchetto);
                }

                // Non ho considerato i moltiplicatori di parola perché la prima parola non può passare sopra di essi
            }
            punti=punti*moltiplicatore;
            if(p.first.length()==6)
            {
                punti=punti+10;
            }
            else if(p.first.length()==7)
            {
                punti=punti+30;
            }
            else if(p.first.length()==8)
            {
                punti=punti+50;
            }
            if(p.first=="SCARABEO" || p.first=="SCARABEI" || p.first=="scarabeo" || p.first=="scarabei")
            {
                punti=punti+100;
            }
            if(p.second==0)
            {
                punti=punti+10;
            }
            if(punti>ManoCorrente.ParolaMx.punteggio)
            {
                ManoCorrente.ParolaMx.punteggio=punti;
                ManoCorrente.ParolaMx.parola=p.first;
                ManoCorrente.ParolaMx.colonna=i;
            }


        }

    }

}

void EliminaScarabei(map<string, int>& ParolePossibili)
{
    auto iteratore = ParolePossibili.begin();
    while (iteratore != ParolePossibili.end())
    {
        if (iteratore->second == 1 || iteratore->second == 2) {
            iteratore = ParolePossibili.erase(iteratore);
        }
        else
        {
            iteratore++;
        }
    }


}

void EsplodiScarabei(map<string, int>& ParolePossibili)
{
    // Generazione delle parole possibili se nel leggio (della prima parola) sono presenti dei jolly
    pair<string, int> elemento;
    string nuovaparola;
    bool primo=true;

    for (auto parola:ParolePossibili)
    {
        if(parola.second==1) // Un solo scarabeo disponibile per formare la parola
        {
            for(unsigned int i=1;i<Sacchetto.size();++i)
            {
                nuovaparola="";
                for(char c:parola.first) // Per ogni carattere della parola
                {
                    if(c!='#')
                    {
                        nuovaparola=nuovaparola+c;
                    }
                    else
                    {
                        nuovaparola=nuovaparola+Sacchetto[i].Lettera;
                    }

                }
                if(nuovaparola.length()<=3 || ParolaEsiste(nuovaparola, Dizionario))
                {
                    elemento={nuovaparola,3};
                    ParolePossibili.insert(elemento);
                }
            }
        }
        else if(parola.second==2) // Due scarabei disponibili
        {
            primo=true;
            for(unsigned int i=1;i<Sacchetto.size();++i)
            {
                for(unsigned int j=1;j<Sacchetto.size();++j)
                {
                    nuovaparola="";
                    for(char c:parola.first)
                    {
                        if(c!='#')
                        {
                            nuovaparola=nuovaparola+c;
                        }
                        else if(primo)
                        {
                            nuovaparola=nuovaparola+Sacchetto[j].Lettera;
                            primo=false;
                        }
                        else
                        {
                            nuovaparola=nuovaparola+Sacchetto[i].Lettera;
                            primo=true;
                        }
                    }
                    if(nuovaparola.length() <=3 || ParolaEsiste(nuovaparola, Dizionario))
                    {
                        elemento={nuovaparola,3};
                        ParolePossibili.insert(elemento);
                    }
                }
            }


        }
    }
    EliminaScarabei(ParolePossibili);
}

void SuggerimentiGenericiOrizzontali(string Leggio, int rmin, int rmax, DatiParola &Correnti)
{

    int punteggiomax=0; // Punteggio della parola migliore


    int numerospazi=0;
    int cc=0; // colonna corrente

    int contamancanti=0;
    int numeroscarabei=0;
    int scorriperpendicolare=0;
    string stringaperpendicolare="";
    bool intersezionivalide=true;
    int pp=0;
    int ps=0;
    int ms=0;
    int mp=1;

    string strutturaparola="";
    bool accettabile=false;
    string lettereeffettive="";
    string CopiaLeggio="";

    int primaletterapos=0;
    char primalettera= ' ';


    for(int c=0;c<17;++c) // Per ogni colonna della matrice
    {

        for(int r=rmin;r<rmax;++r) // Per ogni riga della matrice
        {

            if(c==0 || (c>0 && Griglia[r][c-1][0]==' ' && c!=16)) // Se sono al limite sinistro oppure se nella cella immediatamente precedente non ci sono lettere
            {
                for(int spazitot=1;spazitot<=LETTDISP;++spazitot) // Per un numero di spazi variabile tra 1 e 8
                {
                    cc=c;
                    numerospazi=0;
                    strutturaparola=""; // La struttura della parola è costituita dai caratteri presenti sulla griglia e si estende fintanto che non si è raggiunto il limite della griglia oppure il numero di spazi massimi possibili indicati

                    primalettera=' '; // Primo elemento della struttura a essere un non-spazio
                    primaletterapos=0; // Posizione del primo elemento della struttura che non è uno spazio

                    while(cc<17 && numerospazi<spazitot) // Vai avanti fintanto che ci sono degli spazi
                    {
                        if(Griglia[r][cc][0]==' ')
                        {
                            ++numerospazi;
                        }
                        else
                        {
                            if(numerospazi==strutturaparola.length()) // Se prima ci sono solo spazi
                            {
                                primaletterapos=numerospazi;
                                primalettera=Griglia[r][cc][0];
                            }
                        }

                        strutturaparola=strutturaparola+Griglia[r][cc][0];

                        ++cc;
                    }


                    while(cc<17 && Griglia[r][cc][0]!=' ') // Finché dopo lo spazio ci sono altre lettere da aggiungere
                    {
                        strutturaparola=strutturaparola+Griglia[r][cc][0];
                        if(primalettera==' ') // Se non ho ancora incontrato una lettera
                        {
                            primalettera=Griglia[r][cc][0]; // Adesso l'ho trovata ...
                            primaletterapos=numerospazi; // ... e questa è la sua posizione
                        }
                        ++cc;
                    }

                    if(strutturaparola.length()!=numerospazi) // Se la struttura non è formata soltanto da spazi
                    {
                        if(tolower(primalettera)<=122 && tolower(primalettera)>=97) // Se la lettera esiste
                        {
                            for(auto itera:MatriceMP[primaletterapos][(int)(tolower(primalettera)-97)]) // Trova la cella corrispondente nella matrice di vector di iteratori di mappe di coppie di stringhe
                            {
                                string parola=itera->first; // Questa è la parola puntata

                                accettabile=false;
                                if(parola.length()==strutturaparola.length()) // Se è lunga quanto la struttura
                                {

                                    accettabile=true;
                                    unsigned int lettera=0;

                                    while(accettabile && lettera<parola.length())
                                    {
                                        if(strutturaparola[lettera]!=' ' && tolower(parola[lettera])!=tolower(strutturaparola[lettera])) // Se non coincide con il carattere presente nella struttura
                                        {
                                            accettabile=false;
                                        }
                                        ++lettera;

                                    }

                                    if(accettabile) // Se posso mettere quella parola negli spazi della struttura
                                    {

                                        // Verifico che ci siano le lettere nel leggio
                                        lettereeffettive="";
                                        for(unsigned int lettera=0;lettera<parola.length();++lettera)
                                        {
                                            // Se struttura e parola corrispondono in un punto non ho bisogno di quella lettera
                                            if(tolower(strutturaparola[lettera])!=tolower(parola[lettera]))
                                            {
                                                lettereeffettive=lettereeffettive+parola[lettera];
                                            }
                                        }


                                        if(lettereeffettive!="")
                                        {

                                            if(CopiaLeggio!=Leggio)
                                            {
                                                CopiaLeggio=Leggio;
                                            }

                                            // Se non ho tutte le lettere provo a vedere se posso utilizzare degli scarabei (se ci sono sul mio leggio)
                                            contamancanti=0;
                                            int letteranecessaria=0;
                                            while((unsigned int)letteranecessaria<lettereeffettive.length() && contamancanti<=2)
                                            {
                                                bool trovato=false;
                                                int letteraleggio=0;
                                                while(!trovato && letteraleggio<LETTDISP)
                                                {
                                                    if(tolower(lettereeffettive[letteranecessaria])==tolower(CopiaLeggio[letteraleggio]) && !trovato)
                                                    {
                                                        CopiaLeggio[letteraleggio]=' ';
                                                        trovato=true;
                                                    }
                                                    ++letteraleggio;

                                                }
                                                if(!trovato)
                                                {
                                                    ++contamancanti;
                                                }
                                                ++letteranecessaria;
                                            }

                                            // Conto gli scarabei
                                            numeroscarabei=0;
                                            int nsc=0;
                                            while((unsigned int)nsc<CopiaLeggio.length() && numeroscarabei<=2)
                                            {
                                                if(CopiaLeggio[nsc]=='#')
                                                {
                                                    ++numeroscarabei;
                                                }
                                                ++nsc;
                                            }

                                            if(contamancanti==0 || (contamancanti==1 && numeroscarabei>=1) || (contamancanti==2 && numeroscarabei==2))
                                            {
                                                // Se ci sono gli scarabei li elimino (q.b.)
                                                if((numeroscarabei==1 && contamancanti==1) || (numeroscarabei==2 && contamancanti==1))
                                                {
                                                    int nsc=0;
                                                    while(CopiaLeggio[nsc]!='#')
                                                    {
                                                        ++nsc;
                                                    }
                                                    CopiaLeggio[nsc]=' ';
                                                }
                                                else if(numeroscarabei==2 && contamancanti==2)
                                                {
                                                    int nsc=0;
                                                    int contasc=0;
                                                    while((unsigned int)nsc<CopiaLeggio.length() && contasc<2)
                                                    {
                                                        if(CopiaLeggio[nsc]=='#')
                                                        {
                                                            CopiaLeggio[nsc]=' ';
                                                            ++contasc;
                                                        }
                                                        ++nsc;
                                                    }
                                                }



                                                // Vedo se ci sono intersezioni e le scorro per vedere se esistono

                                                intersezionivalide=true;

                                                cc=c;

                                                while(intersezionivalide && cc<c+(int)parola.length())
                                                {
                                                    scorriperpendicolare=r;

                                                    // Vai fino all'inizio dell'intersezione
                                                    if(scorriperpendicolare!=0) // Non sono già al limite del tabellone
                                                    {
                                                        --scorriperpendicolare;
                                                        while(scorriperpendicolare>=0 && Griglia[scorriperpendicolare][cc][0]!=' ')
                                                        {
                                                            --scorriperpendicolare;
                                                        }
                                                        ++scorriperpendicolare;
                                                    }

                                                    // Scorri tutta la parola
                                                    stringaperpendicolare="";
                                                    while((scorriperpendicolare<17 && Griglia[scorriperpendicolare][cc][0]!=' ') || scorriperpendicolare==r)
                                                    {
                                                        if(scorriperpendicolare==r)
                                                        {
                                                            stringaperpendicolare=stringaperpendicolare+parola[cc-c];
                                                        }
                                                        else
                                                        {
                                                            stringaperpendicolare=stringaperpendicolare+Griglia[scorriperpendicolare][cc][0];
                                                        }
                                                        ++scorriperpendicolare;
                                                    }


                                                    // Vedi se la parola esiste
                                                    if(stringaperpendicolare.length()>3 && !ParolaEsiste(stringaperpendicolare, Dizionario))
                                                    {
                                                        if(Griglia[r][cc][0]==' ')
                                                        {
                                                            intersezionivalide=false;
                                                        }
                                                    }

                                                    ++cc;

                                                }

                                                // Se tutte le intersezioni sono valide
                                                if(intersezionivalide)
                                                {
                                                    pp=0;
                                                    ps=0;
                                                    mp=1;
                                                    ms=1;

                                                    // Calcola il punteggio della parola principale
                                                    for(unsigned int l=0;l<parola.length();++l) // Per ogni lettera della parola
                                                    {
                                                        if(Griglia[r][c+l][1]==' ' )
                                                        {
                                                            pp+=ValoreLettera(parola[l], Sacchetto);
                                                        }
                                                        if(Griglia[r][c+l][1]=='2')
                                                        {
                                                            pp=pp+2*ValoreLettera(parola[l], Sacchetto);
                                                        }
                                                        else if(Griglia[r][c+l][1]=='3')
                                                        {
                                                            pp=pp+3*ValoreLettera(parola[l], Sacchetto);
                                                        }

                                                        if(Griglia[r][c+l][2]=='3')
                                                        {
                                                            mp=mp*3;
                                                        }
                                                        else if(Griglia[r][c+l][2]=='2')
                                                        {
                                                            mp=mp*2;
                                                        }
                                                    }

                                                    pp=pp*mp;

                                                    PuntiIntersezioni(parola, r, c, pp, true, Sacchetto); // Intersezioni verticali

                                                    // Aggiungi eventuale bonus lettere (-> lettereeffettive.size())
                                                    if(lettereeffettive.size()==6)
                                                    {
                                                        pp+=10;
                                                    }
                                                    else if(lettereeffettive.size()==7)
                                                    {
                                                        pp+=30;
                                                    }
                                                    else if(lettereeffettive.size()==8)
                                                    {
                                                        pp+=50;
                                                    }

                                                    // Aggiungi eventuale bonus jolly (->numeroscarabei==0)
                                                    if(numeroscarabei==0)
                                                    {
                                                        pp+=10;
                                                    }

                                                    if(pp>punteggiomax) // Se il mio punteggio è più alto rispetto a quello della parola con punteggio maggiore trovata fino ad ora divento la parola migliore (per adesso)
                                                    {
                                                        Correnti.parola=parola;
                                                        Correnti.punteggio=pp;
                                                        Correnti.LeggioR=CopiaLeggio;
                                                        Correnti.riga=r;
                                                        Correnti.colonna=c;
                                                        Correnti.maxdirvert=false;

                                                        punteggiomax=pp;


                                                    }


                                                }
                                            }

                                        }
                                    }
                                }

                            }
                        }
                    }


                }
            }

        }
    }


}

void SuggerimentiGenericiVerticali(string Leggio, int rmin, int rmax, DatiParola &Correnti)
{
    int punteggiomax=0; // Punteggio della parola migliore

    int numerospazi=0;
    int rc=0; // riga corrente

    int contamancanti=0;
    int numeroscarabei=0;
    int scorriperpendicolare=0;
    string stringaperpendicolare="";
    bool intersezionivalide=true;
    int pp=0;
    int ps=0;
    int mp=1;
    int ms=1;
    string CopiaLeggio="";
    int primaletterapos=0;
    char primalettera=' ';

    string strutturaparola="";
    bool accettabile=false;
    string lettereeffettive="";

    // Genera tutte le sottostrutture di minimo 2 celle (PAROLE VERTICALI)
    for(int r=0; r<17; ++r)
    {
        for(int c=rmin;c<rmax;++c)
        {
            if(r==0 || (r>0 && Griglia[r-1][c][0]==' ' && r!=16))
            {
                for(int spazitot=1;spazitot<=LETTDISP;++spazitot)
                {
                    rc=r;
                    numerospazi=0;
                    strutturaparola="";
                    primalettera=' ';
                    primaletterapos=0;

                    while(numerospazi<spazitot && rc<17) // Vai avanti fintanto che ci sono degli spazi
                    {
                        if(Griglia[rc][c][0]==' ')
                        {
                            ++numerospazi;

                        }
                        else
                        {
                            if(numerospazi==strutturaparola.length())
                            {
                                primaletterapos=numerospazi;
                                primalettera=Griglia[rc][c][0];



                            }
                        }
                        strutturaparola=strutturaparola+Griglia[rc][c][0];


                        ++rc;
                    }

                    while(rc<17 && Griglia[rc][c][0]!=' ') // Finché dopo lo spazio ci sono altre lettere da aggiungere
                    {
                        strutturaparola=strutturaparola+Griglia[rc][c][0];
                        if(primalettera==' ')
                        {
                            primalettera=Griglia[rc][c][0];
                            primaletterapos=numerospazi;
                        }
                        ++rc;
                    }


                    if(strutturaparola.length()!=(unsigned int)numerospazi)
                    {



                        if(tolower(primalettera)<=122 && tolower(primalettera)>=97)
                        {


                            for(auto itera:MatriceMP[primaletterapos][(int)(tolower(primalettera)-97)])
                            {

                                string parola=itera->first;

                                accettabile=false;
                                if(parola.size()==strutturaparola.length())
                                {

                                    accettabile=true;
                                    unsigned int lettera=0;

                                    while(accettabile && lettera<parola.length())
                                    {
                                        if(strutturaparola[lettera]!=' ' && tolower(parola[lettera])!=tolower(strutturaparola[lettera]))
                                        {
                                            accettabile=false;
                                        }
                                        ++lettera;

                                    }

                                    if(accettabile) // Se posso mettere quella parola negli spazi della struttura
                                    {


                                        // Verifico che ci siano le lettere nel leggio
                                        lettereeffettive="";
                                        for(unsigned int lettera=0;lettera<parola.length();++lettera)
                                        {
                                            // Se struttura e parola corrispondono in un punto non ho bisogno di quella lettera
                                            if(tolower(strutturaparola[lettera])!=tolower(parola[lettera]))
                                            {
                                                lettereeffettive=lettereeffettive+parola[lettera];
                                            }
                                        }


                                        if(lettereeffettive!="")
                                        {

                                            if(CopiaLeggio!=Leggio)
                                            {
                                                CopiaLeggio=Leggio;
                                            }


                                            contamancanti=0;
                                            int letteranecessaria=0;
                                            while((unsigned int)letteranecessaria<lettereeffettive.length() && contamancanti<=2)
                                            {
                                                bool trovato=false;
                                                int letteraleggio=0;
                                                while(!trovato && letteraleggio<LETTDISP)
                                                {
                                                    if(tolower(lettereeffettive[letteranecessaria])==tolower(CopiaLeggio[letteraleggio]) && !trovato)
                                                    {
                                                        CopiaLeggio[letteraleggio]=' ';
                                                        trovato=true;
                                                    }
                                                    ++letteraleggio;

                                                }
                                                if(!trovato)
                                                {
                                                    ++contamancanti;
                                                }
                                                ++letteranecessaria;
                                            }

                                            // Conto gli scarabei
                                            numeroscarabei=0;
                                            int nsc=0;
                                            while((unsigned int)nsc<CopiaLeggio.length() && numeroscarabei<=2)
                                            {
                                                if(CopiaLeggio[nsc]=='#')
                                                {
                                                    ++numeroscarabei;
                                                }
                                                ++nsc;
                                            }
                                            if(contamancanti==0 || (contamancanti==1 && numeroscarabei>=1) || (contamancanti==2 && numeroscarabei==2))
                                            {
                                                // Se ci sono gli scarabei li elimino (q.b.)
                                                if((numeroscarabei==1 && contamancanti==1) || (numeroscarabei==2 && contamancanti==1))
                                                {
                                                    int nsc=0;
                                                    while(CopiaLeggio[nsc]!='#')
                                                    {
                                                        ++nsc;
                                                    }
                                                    CopiaLeggio[nsc]=' ';
                                                }
                                                else if(numeroscarabei==2 && contamancanti==2)
                                                {
                                                    int nsc=0;
                                                    int contasc=0;
                                                    while(contasc<2 && (unsigned int)nsc<CopiaLeggio.length())
                                                    {
                                                        if(CopiaLeggio[nsc]=='#')
                                                        {
                                                            CopiaLeggio[nsc]=' ';
                                                            ++contasc;
                                                        }
                                                        ++nsc;
                                                    }
                                                }

                                                // Vedo se ci sono intersezioni e le scorro per vedere se esistono

                                                intersezionivalide=true;

                                                rc=r;

                                                while(intersezionivalide && rc<r+(int)parola.length())
                                                {
                                                    scorriperpendicolare=c;

                                                    // Vai fino all'inizio dell'intersezione
                                                    if(scorriperpendicolare!=0) // Non sono già al limite del tabellone
                                                    {
                                                        --scorriperpendicolare;
                                                        while(scorriperpendicolare>=0 && Griglia[rc][scorriperpendicolare][0]!=' ')
                                                        {
                                                            --scorriperpendicolare;
                                                        }
                                                        ++scorriperpendicolare;
                                                    }

                                                    // Scorri tutta la parola
                                                    stringaperpendicolare="";
                                                    while((scorriperpendicolare<C && Griglia[rc][scorriperpendicolare][0]!=' ') || scorriperpendicolare==c)
                                                    {
                                                        if(scorriperpendicolare==c)
                                                        {
                                                            stringaperpendicolare=stringaperpendicolare+parola[rc-r];
                                                        }
                                                        else
                                                        {
                                                            stringaperpendicolare=stringaperpendicolare+Griglia[rc][scorriperpendicolare][0];
                                                        }
                                                        ++scorriperpendicolare;
                                                    }

                                                    // Vedi se la parola esiste
                                                    if(stringaperpendicolare.length()>3 && !ParolaEsiste(stringaperpendicolare, Dizionario))
                                                    {
                                                        if(Griglia[rc][c][0]==' ')
                                                        {
                                                            intersezionivalide=false;
                                                        }
                                                    }


                                                    ++rc;

                                                }

                                                // Se tutte le intersezioni sono valide
                                                if(intersezionivalide)
                                                {
                                                    pp=0;
                                                    ps=0;
                                                    mp=1;
                                                    ms=1;

                                                    // Calcola il punteggio della parola principale
                                                    for(unsigned int l=0;l<parola.length();++l) // Per ogni lettera della parola
                                                    {
                                                        if(Griglia[r+l][c][1]==' ')
                                                        {
                                                            pp+=ValoreLettera(parola[l], Sacchetto);
                                                        }
                                                        if(Griglia[r+l][c][1]=='2')
                                                        {
                                                            pp=pp+2*ValoreLettera(parola[l], Sacchetto);
                                                        }
                                                        else if(Griglia[r+l][c][1]=='3')
                                                        {
                                                            pp=pp+3*ValoreLettera(parola[l], Sacchetto);
                                                        }

                                                        if(Griglia[r+l][c][2]=='3')
                                                        {
                                                            mp=mp*3;
                                                        }
                                                        else if(Griglia[r+l][c][2]=='2')
                                                        {
                                                            mp=mp*2;
                                                        }
                                                    }

                                                    pp=pp*mp;

                                                    // Calcola il punteggio delle intersezioni (se esistono)
                                                    for(unsigned int l=0;l<parola.length();++l) // Per ogni lettera della parola
                                                    {
                                                        if(Griglia[l+r][c][0]==' ')
                                                        {
                                                            ps=0;
                                                            ms=1;

                                                            // Se la lettera della parola principale ha intersezioni e non è già sul tabellone riconta punteggio
                                                            if(Griglia[r+l][c][0]==' ' && ((c-1>=0 && Griglia[r+l][c-1][0]!=' ') || (c+1<=16 && Griglia[r+l][c+1][0]!=' ')))
                                                            {
                                                                if(Griglia[r+l][c][1]==' ' )
                                                                {
                                                                    ps+=ValoreLettera(parola[l], Sacchetto);
                                                                }
                                                                if(Griglia[r+l][c][1]=='2')
                                                                {
                                                                    ps=ps+2*ValoreLettera(parola[l], Sacchetto);
                                                                }
                                                                else if(Griglia[r+l][c][1]=='3')
                                                                {
                                                                    ps=ps+3*ValoreLettera(parola[l], Sacchetto);
                                                                }

                                                                if(Griglia[r+l][c][2]=='3')
                                                                {
                                                                    ms=ms*3;
                                                                }
                                                                else if(Griglia[r+l][c][2]=='2')
                                                                {
                                                                    ms=ms*2;
                                                                }
                                                            }

                                                            // Scorri perpendicolarmente in una direzione
                                                            scorriperpendicolare=c-1;
                                                            if(scorriperpendicolare>=0 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                            {
                                                                while(scorriperpendicolare>=0 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                                {
                                                                    if(Griglia[r+l][scorriperpendicolare][1]==' ')
                                                                    {
                                                                        ps+=ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }

                                                                    if(Griglia[r+l][scorriperpendicolare][1]=='2')
                                                                    {
                                                                        ps=ps+2*ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }
                                                                    else if(Griglia[r+l][scorriperpendicolare][1]=='3')
                                                                    {
                                                                        ps=ps+3*ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }

                                                                    if(Griglia[r+l][scorriperpendicolare][2]=='3')
                                                                    {
                                                                        ms=ms*3;
                                                                    }
                                                                    else if(Griglia[r+l][scorriperpendicolare][2]=='2')
                                                                    {
                                                                        ms=ms*2;
                                                                    }
                                                                    --scorriperpendicolare;
                                                                }
                                                            }
                                                            // Scorri perpendicolarmente nell'altra
                                                            scorriperpendicolare=c+1;
                                                            if(scorriperpendicolare<=16 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                            {
                                                                while(scorriperpendicolare<=16 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                                {

                                                                    if(Griglia[r+l][scorriperpendicolare][1]==' ' )
                                                                    {
                                                                        ps+=ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }

                                                                    if(Griglia[r+l][scorriperpendicolare][1]=='2')
                                                                    {
                                                                        ps=ps+2*ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }
                                                                    else if(Griglia[r+l][scorriperpendicolare][1]=='3')
                                                                    {
                                                                        ps=ps+3*ValoreLettera(Griglia[r+l][scorriperpendicolare][0], Sacchetto);
                                                                    }

                                                                    if(Griglia[r+l][scorriperpendicolare][2]=='3')
                                                                    {
                                                                        ms=ms*3;
                                                                    }
                                                                    else if(Griglia[r+l][scorriperpendicolare][2]=='2')
                                                                    {
                                                                        ms=ms*2;
                                                                    }
                                                                    ++scorriperpendicolare;
                                                                }
                                                            }
                                                            ps=ps*ms;
                                                            pp=pp+ps;
                                                        }
                                                    }


                                                    // Aggiungi eventuale bonus lettere (-> lettereeffettive.size())
                                                    if(lettereeffettive.size()==6)
                                                    {
                                                        pp+=10;
                                                    }
                                                    else if(lettereeffettive.size()==7)
                                                    {
                                                        pp+=30;
                                                    }
                                                    else if(lettereeffettive.size()==8)
                                                    {
                                                        pp+=50;
                                                    }

                                                    // Aggiungi eventuale bonus jolly (->numeroscarabei==0)
                                                    if(numeroscarabei==0)
                                                    {
                                                        pp+=10;
                                                    }

                                                    if(pp>punteggiomax)
                                                    {
                                                        //DatiParola Risultato;
                                                        Correnti.parola=parola;
                                                        Correnti.punteggio=pp;
                                                        Correnti.LeggioR=CopiaLeggio;
                                                        Correnti.riga=r;
                                                        Correnti.colonna=c;
                                                        Correnti.maxdirvert=true;

                                                        punteggiomax=pp;
                                                    }


                                                }
                                            }

                                        }
                                    }
                                }


                            }
                        }
                    }
                }
            }
        }
    }

}

void TrovaLimiti(int& rigamin, int& rigamax, int& colonnamin, int& colonnamax)
{
    bool trovamin=false;

    // Riga minima e rigamassima
    for(int rv=0;rv<R;++rv)
    {
        for(int cv=0;cv<C;++cv)
        {
            if(!trovamin)
            {
                if(Griglia[rv][cv][0]!=' ')
                {
                    rigamin=rv;
                    trovamin=true;
                }
            }
            if(Griglia[rv][cv][0]!=' ')
            {
                rigamax=rv;
            }
        }
    }

    trovamin=false;

    // Colonna minima e massima
    for(int cv=0;cv<C;++cv)
    {
        for(int rv=0;rv<R;++rv)
        {
            if(!trovamin)
            {
                if(Griglia[rv][cv][0]!=' ')
                {
                    colonnamin=cv;
                    trovamin=true;
                }
            }
            if(Griglia[rv][cv][0]!=' ')
            {
                colonnamax=cv;
            }
        }
    }

}

void TrovaMedie(int& rigamed, int& colonnamed, int& rigamin, int& rigamax, int& colonnamin, int& colonnamax)
{
    rigamed=(rigamin+rigamax)/2;
    colonnamed=(colonnamin+colonnamax)/2;
}

void InizializzaDatiParola(DatiParola& OrP, DatiParola& OrS, DatiParola& VerP, DatiParola& VerS)
{
    VerS.parola="";
    VerS.punteggio=0;
    VerS.LeggioR="";
    VerS.riga=0;
    VerS.colonna=0;
    VerS.maxdirvert=true;

    OrS.parola="";
    OrS.punteggio=0;
    OrS.LeggioR="";
    OrS.riga=0;
    OrS.colonna=0;
    OrS.maxdirvert=false;

    VerP.parola="";
    VerP.punteggio=0;
    VerP.LeggioR="";
    VerP.riga=0;
    VerP.colonna=0;
    VerP.maxdirvert=true;

    OrP.parola="";
    OrP.punteggio=0;
    OrP.LeggioR="";
    OrP.riga=0;
    OrP.colonna=0;
    OrP.maxdirvert=false;
}

DatiParola PunteggioMassimo(DatiParola& OrP, DatiParola& OrS, DatiParola& VerP, DatiParola& VerS)
{
    // Trova quello con il punteggio più alto
    if(OrP.punteggio>=OrS.punteggio && OrP.punteggio>=VerP.punteggio && OrP.punteggio >=VerS.punteggio)
    {
        return OrP;
    }
    else if(OrS.punteggio>=OrP.punteggio && OrS.punteggio>=VerP.punteggio && OrS.punteggio >=VerS.punteggio)
    {
        return OrS;
    }
    else if(VerP.punteggio>=OrP.punteggio && VerP.punteggio>=VerS.punteggio && VerP.punteggio >=OrS.punteggio)
    {
        return VerP;
    }
    else
    {
        return VerS;
    }

}

DatiParola SuggerimentiGenerici(string Leggio)
{

    DatiParola VerS, OrS, VerP, OrP;
    InizializzaDatiParola(VerS, OrS, VerP, OrP);

    int rigamin=0;
    int rigamed=0;
    int rigamax=0;

    int colonnamin=0;
    int colonnamed=0;
    int colonnamax=0;


    TrovaLimiti(rigamin, rigamax, colonnamin, colonnamax);
    TrovaMedie(rigamed, colonnamed, rigamin, rigamax, colonnamin, colonnamax);

    // Esegue in parallelo la ricerca delle parole verticali e orizzontali

    thread OP(SuggerimentiGenericiOrizzontali, Leggio, rigamin, rigamed, std::ref(OrP));
    thread OS(SuggerimentiGenericiOrizzontali, Leggio, rigamed, rigamax+1, std::ref(OrS));
    thread VP(SuggerimentiGenericiVerticali, Leggio, colonnamin, colonnamed, std::ref(VerP));
    thread VS(SuggerimentiGenericiVerticali, Leggio, colonnamed, colonnamax+1, std::ref(VerS));

    OP.join();
    OS.join();
    VP.join();
    VS.join();

    return PunteggioMassimo(OrP, OrS, VerP, VerS);

}
