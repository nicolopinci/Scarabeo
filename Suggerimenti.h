void GeneraParoleComplete(string stringa)
{
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
                    ++scarabeo;
                }

            }
            if(scarabeo==0)
            {
                if(ParolaEsiste(sottostringa, Dizionario) || sottostringa.length()==2)
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
    while(next_permutation(stringa.begin(), stringa.end()));
}

void GeneraCombinazioni(string stringa, int nsp)
{
    string sottostringa;
    sort(stringa.begin(), stringa.end());
    pair<string,int> elemento;
    int scarabeo;
    do
    {
        for(int i=1;i<=nsp;++i)
        {
            sottostringa="";
            scarabeo=0;
            for(int j=0;j<i;++j)
            {
                sottostringa=sottostringa+stringa[j];
                if(stringa[j]=='#')
                {
                    ++scarabeo;
                }

            }


            elemento={sottostringa, scarabeo};
            Combinazioni.insert(elemento);

        }

    }

    while(next_permutation(stringa.begin(), stringa.end()));
}

void SvuotaPossibili()
{
    auto iteratore = ParolePossibili.begin();
    while (iteratore != ParolePossibili.end())
    {

        iteratore = ParolePossibili.erase(iteratore);

    }
}

void SvuotaCombinazioni()
{
    auto iteratore = Combinazioni.begin();
    while (iteratore != Combinazioni.end())
    {

        iteratore = Combinazioni.erase(iteratore);

    }
}

void TrovaPrimaMigliore()
{
    int punti=0;

    int moltiplicatore=1;
    int partenza=0;

    ptmx=0;

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
                    punti=punti+ValoreLettera(p.first[l-i])*(int)(Griglia[8][l][1]-'0');
                }
                else if(Griglia[8][l][2]!=' ')
                {
                    moltiplicatore=moltiplicatore*(int)(Griglia[8][l][2]-'0');
                }
                else
                {
                    punti=punti+ValoreLettera(p.first[l-i]);
                }
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
            if(p.first=="SCARABEO" || p.first=="SCARABEI")
            {
                punti=punti+100;
            }
            if(p.second==0)
            {
                punti=punti+10;
            }
            if(punti>ptmx)
            {
                ptmx=punti;
                parolamax=p.first;
                colonnamax=i;
            }


        }

    }

}

void EliminaScarabei()
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

void EsplodiScarabei()
{
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
                if(ParolaEsiste(nuovaparola, Dizionario))
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
                    if(ParolaEsiste(nuovaparola, Dizionario))
                    {
                        elemento={nuovaparola,3};
                        ParolePossibili.insert(elemento);
                    }
                }
            }


        }
    }
    EliminaScarabei();
}

void SuggerimentiGenericiOrizzontali(string Leggio, int rmin, int rmax, map<string, string>& CopiaDizionario, DatiParola &Correnti, char Griglia[][C][LIV])
{
    DatiParola Risultato;

    Risultato.parola="";
    Risultato.punteggio=0;
    Risultato.LeggioR="";
    Risultato.riga=0;
    Risultato.colonna=0;
    Risultato.maxdirvert=true;

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
    int ms=1;
    int mp=1;

    string strutturaparola="";
    bool accettabile=false;
    string lettereeffettive="";
    string CopiaLeggio;



    for(int c=0;c<C;++c)
    {
        for(int r=rmin;r<rmax;++r)
        {

            if(c==0 || (c>0 && Griglia[r][c-1][0]==' ' && c!=C-1))
            {
                for(int spazitot=1;spazitot<=LETTDISP;++spazitot)
                {
                    cc=c;
                    numerospazi=0;
                    strutturaparola="";
                    while(cc<C && numerospazi<spazitot) // Vai avanti fintanto che ci sono degli spazi
                    {
                        if(Griglia[r][cc][0]==' ')
                        {
                            ++numerospazi;
                        }
                        strutturaparola=strutturaparola+Griglia[r][cc][0];


                        ++cc;
                    }


                    while(cc<C && Griglia[r][cc][0]!=' ') // Finché dopo lo spazio ci sono altre lettere da aggiungere
                    {
                        strutturaparola=strutturaparola+Griglia[r][cc][0];
                        ++cc;
                    }


                    if(strutturaparola.length()!=(unsigned int)numerospazi)
                    {
                        for(auto parola:CopiaDizionario)
                        {
                            accettabile=false;
                            if(parola.first.length()==strutturaparola.length())
                            {

                                accettabile=true;
                                unsigned int lettera=0;

                                while(accettabile && lettera<parola.first.length())
                                {
                                    if(tolower(parola.first[lettera])!=tolower(strutturaparola[lettera]) && strutturaparola[lettera]!=' ')
                                    {
                                        accettabile=false;
                                    }
                                    ++lettera;

                                }

                                if(accettabile) // Se posso mettere quella parola negli spazi della struttura
                                {

                                    // Verifico che ci siano le lettere nel leggio
                                    lettereeffettive="";
                                    for(unsigned int lettera=0;lettera<parola.first.length();++lettera)
                                    {
                                        // Se struttura e parola corrispondono in un punto non ho bisogno di quella lettera
                                        if(tolower(strutturaparola[lettera])!=tolower(parola.first[lettera]))
                                        {
                                            lettereeffettive=lettereeffettive+parola.first[lettera];
                                        }
                                    }


                                    if(lettereeffettive!="")
                                    {

                                            CopiaLeggio=Leggio;


                                        contamancanti=0;
                                        int letteranecessaria=0;
                                        while(letteranecessaria<lettereeffettive.length() && contamancanti<=2)
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
                                        while(nsc<CopiaLeggio.length() && numeroscarabei<=2)
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
                                            if(numeroscarabei==1)
                                            {
                                                int nsc=0;
                                                while(CopiaLeggio[nsc]!='#')
                                                {
                                                    ++nsc;
                                                }
                                                CopiaLeggio[nsc]=' ';
                                            }
                                            else if(numeroscarabei==2)
                                            {
                                                int nsc=0;
                                                int contasc=0;
                                                while(nsc<CopiaLeggio.length() && contasc<2)
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

                                            while(intersezionivalide && cc<c+(int)parola.first.length())
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
                                                while((scorriperpendicolare<R && Griglia[scorriperpendicolare][cc][0]!=' ') || scorriperpendicolare==r)
                                                {
                                                    if(scorriperpendicolare==r)
                                                    {
                                                        stringaperpendicolare=stringaperpendicolare+parola.first[cc-c];
                                                    }
                                                    else
                                                    {
                                                        stringaperpendicolare=stringaperpendicolare+Griglia[scorriperpendicolare][cc][0];
                                                    }
                                                    ++scorriperpendicolare;
                                                }


                                                // Vedi se la parola esiste
                                                if(stringaperpendicolare.length()>2 && !ParolaEsiste(stringaperpendicolare, CopiaDizionario))
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
                                                for(unsigned int l=0;l<parola.first.length();++l) // Per ogni lettera della parola
                                                {
                                                    if(Griglia[r][c+l][1]==' ' )
                                                    {
                                                        pp+=ValoreLettera(parola.first[l]);
                                                    }
                                                    if(Griglia[r][c+l][1]=='2')
                                                    {
                                                        pp=pp+2*ValoreLettera(parola.first[l]);
                                                    }
                                                    else if(Griglia[r][c+l][1]=='3')
                                                    {
                                                        pp=pp+3*ValoreLettera(parola.first[l]);
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

                                                PuntiIntersezioni(parola.first, r, c, pp, true); // Intersezioni verticali

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
                                                    Correnti.parola=parola.first;
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

void SuggerimentiGenericiVerticali(string Leggio, int rmin, int rmax, map<string, string>& CopiaDizionario, DatiParola &Correnti, char Griglia[][C][LIV])
{

    DatiParola Risultato;

    Risultato.parola="";
    Risultato.punteggio=0;
    Risultato.LeggioR="";
    Risultato.riga=0;
    Risultato.colonna=0;
    Risultato.maxdirvert=true;

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
    string CopiaLeggio;

    string strutturaparola="";
    bool accettabile=false;
    string lettereeffettive="";

    // Genera tutte le sottostrutture di minimo 2 celle (PAROLE VERTICALI)
    for(int r=rmin; r<rmax; ++r)
    {
        for(int c=0;c<C;++c)
        {
            if(r==0 || (r>0 && Griglia[r-1][c][0]==' ' && r!=R-1))
            {
                for(int spazitot=1;spazitot<=LETTDISP;++spazitot)
                {
                    rc=r;
                    numerospazi=0;
                    strutturaparola="";
                    while(numerospazi<spazitot && rc<R) // Vai avanti fintanto che ci sono degli spazi
                    {
                        if(Griglia[rc][c][0]==' ')
                        {
                            ++numerospazi;
                        }
                        strutturaparola=strutturaparola+Griglia[rc][c][0];


                        ++rc;
                    }

                    while(rc<R && Griglia[rc][c][0]!=' ') // Finché dopo lo spazio ci sono altre lettere da aggiungere
                    {
                        strutturaparola=strutturaparola+Griglia[rc][c][0];
                        ++rc;
                    }

                    if(strutturaparola.length()!=(unsigned int)numerospazi)
                    {
                        for(auto parola:CopiaDizionario)
                        {

                            accettabile=false;
                            if(parola.first.length()==strutturaparola.length())
                            {

                                accettabile=true;
                                unsigned int lettera=0;

                                while(accettabile && lettera<parola.first.length())
                                {
                                    if(tolower(parola.first[lettera])!=tolower(strutturaparola[lettera]) && strutturaparola[lettera]!=' ')
                                    {
                                        accettabile=false;
                                    }
                                    ++lettera;

                                }

                                if(accettabile) // Se posso mettere quella parola negli spazi della struttura
                                {


                                    // Verifico che ci siano le lettere nel leggio
                                    lettereeffettive="";
                                    for(unsigned int lettera=0;lettera<parola.first.length();++lettera)
                                    {
                                        // Se struttura e parola corrispondono in un punto non ho bisogno di quella lettera
                                        if(tolower(strutturaparola[lettera])!=tolower(parola.first[lettera]))
                                        {
                                            lettereeffettive=lettereeffettive+parola.first[lettera];
                                        }
                                    }


                                    if(lettereeffettive!="")
                                    {

                                            CopiaLeggio=Leggio;


                                        contamancanti=0;
                                        int letteranecessaria=0;
                                        while(letteranecessaria<lettereeffettive.length() && contamancanti<=2)
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
                                        while(nsc<CopiaLeggio.length() && numeroscarabei<=2)
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
                                            if(numeroscarabei==1)
                                            {
                                                int nsc=0;
                                                while(CopiaLeggio[nsc]!='#')
                                                {
                                                    ++nsc;
                                                }
                                                CopiaLeggio[nsc]=' ';
                                            }
                                            else if(numeroscarabei==2)
                                            {
                                                int nsc=0;
                                                int contasc=0;
                                                while(contasc<2 && nsc<CopiaLeggio.length())
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

                                            while(intersezionivalide && rc<r+(int)parola.first.length())
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
                                                        stringaperpendicolare=stringaperpendicolare+parola.first[rc-r];
                                                    }
                                                    else
                                                    {
                                                        stringaperpendicolare=stringaperpendicolare+Griglia[rc][scorriperpendicolare][0];
                                                    }
                                                    ++scorriperpendicolare;
                                                }

                                                // Vedi se la parola esiste
                                                if(stringaperpendicolare.length()>2 && !ParolaEsiste(stringaperpendicolare, CopiaDizionario))
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
                                                for(unsigned int l=0;l<parola.first.length();++l) // Per ogni lettera della parola
                                                {
                                                    if(Griglia[r+l][c][1]==' ')
                                                    {
                                                        pp+=ValoreLettera(parola.first[l]);
                                                    }
                                                    if(Griglia[r+l][c][1]=='2')
                                                    {
                                                        pp=pp+2*ValoreLettera(parola.first[l]);
                                                    }
                                                    else if(Griglia[r+l][c][1]=='3')
                                                    {
                                                        pp=pp+3*ValoreLettera(parola.first[l]);
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
                                                for(unsigned int l=0;l<parola.first.length();++l) // Per ogni lettera della parola
                                                {
                                                    if(Griglia[l+r][c][0]==' ')
                                                    {
                                                        ps=0;
                                                        ms=1;

                                                        // Se la lettera della parola principale ha intersezioni e non è già sul tabellone riconta punteggio
                                                        if(Griglia[r+l][c][0]==' ' && ((c-1>=0 && Griglia[r+l][c-1][0]!=' ') || (c+1<=C-1 && Griglia[r+l][c+1][0]!=' ')))
                                                        {
                                                            if(Griglia[r+l][c][1]==' ' )
                                                            {
                                                                ps+=ValoreLettera(parola.first[l]);
                                                            }
                                                            if(Griglia[r+l][c][1]=='2')
                                                            {
                                                                ps=ps+2*ValoreLettera(parola.first[l]);
                                                            }
                                                            else if(Griglia[r+l][c][1]=='3')
                                                            {
                                                                ps=ps+3*ValoreLettera(parola.first[l]);
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
                                                                    ps+=ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
                                                                }

                                                                if(Griglia[r+l][scorriperpendicolare][1]=='2')
                                                                {
                                                                    ps=ps+2*ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
                                                                }
                                                                else if(Griglia[r+l][scorriperpendicolare][1]=='3')
                                                                {
                                                                    ps=ps+3*ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
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
                                                        if(scorriperpendicolare<=C-1 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                        {
                                                            while(scorriperpendicolare<=C-1 && Griglia[r+l][scorriperpendicolare][0]!=' ')
                                                            {

                                                                if(Griglia[r+l][scorriperpendicolare][1]==' ' )
                                                                {
                                                                    ps+=ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
                                                                }

                                                                if(Griglia[r+l][scorriperpendicolare][1]=='2')
                                                                {
                                                                    ps=ps+2*ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
                                                                }
                                                                else if(Griglia[r+l][scorriperpendicolare][1]=='3')
                                                                {
                                                                    ps=ps+3*ValoreLettera(Griglia[r+l][scorriperpendicolare][0]);
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
                                                    Correnti.parola=parola.first;
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

DatiParola SuggerimentiGenerici(string Leggio, int modsug)
{

    DatiParola VerS, OrS, VerP, OrP;

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

    bool trovamin=false;
    int rigamin=0;
    int rigamax=0;

    int colonnamin=0;
    int colonnamax=0;

    char GOP[R][C][LIV];
    char GOS[R][C][LIV];

    char GVP[R][C][LIV];

    char GVS[R][C][LIV];

    map<string, string> Dizi1;
    map<string, string> Dizi2;
    map<string, string> Dizi3;
    map<string, string> Dizi4;

    if(modsug==0)
    {
        Dizi1=Dizionario;
        Dizi2=Dizionario;
        Dizi3=Dizionario;
        Dizi4=Dizionario;
    }
    else
    {
        Dizi1=DizionarioBase;
        Dizi2=DizionarioBase;
        Dizi3=DizionarioBase;
        Dizi4=DizionarioBase;
    }

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

    int rigamed=(rigamin+rigamax)/2;
    int colonnamed=(colonnamin+colonnamax)/2;


    // Copio la griglia nelle griglie locali
    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            for(int l=0;l<LIV;++l)
            {
                GOP[r][c][l]=Griglia[r][c][l];
                GOS[r][c][l]=Griglia[r][c][l];

                GVP[r][c][l]=Griglia[r][c][l];

                GVS[r][c][l]=Griglia[r][c][l];

            }
        }
    }

    // Esegue in parallelo la ricerca delle parole verticali e orizzontali


    thread OP(SuggerimentiGenericiOrizzontali, Leggio, rigamin, rigamed, std::ref(Dizi1), std::ref(OrP), GOP);

    thread OS(SuggerimentiGenericiOrizzontali, Leggio, rigamed, rigamax+1, std::ref(Dizi2), std::ref(OrS), GOS);

    thread VP(SuggerimentiGenericiVerticali, Leggio, colonnamin, colonnamed, std::ref(Dizi3), std::ref(VerP), GVP);

    thread VS(SuggerimentiGenericiVerticali, Leggio, colonnamed, colonnamax+1, std::ref(Dizi4), std::ref(VerS), GVS);


    OP.join();

    OS.join();

    VP.join();

    VS.join();


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
