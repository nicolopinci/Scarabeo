void GiocatoreSuccessivo()
{
    if(Giocatore==1)
    {
        Giocatore=2;
    }
    else if(Giocatore==2)
    {
        if(numgioc==2)
        {
            Giocatore=1;
        }
        else
        {
            Giocatore=3;
        }
    }
    else if(Giocatore==3)
    {
        if(numgioc==3)
        {
            Giocatore=1;
        }
        else
        {
            Giocatore=4;
        }
    }
    else if(Giocatore==4)
    {
        Giocatore=1;
    }
}

void RiempiLeggioCorrente(string &LeggioProvvisorio)
{
    if(Giocatore==1)
    {
        RiempiLeggio(PrimoLeggio);
        LeggioProvvisorio=PrimoLeggio;
    }
    else if(Giocatore==2)
    {
        RiempiLeggio(SecondoLeggio);
        LeggioProvvisorio=SecondoLeggio;
    }
    else if(Giocatore==3)
    {
        RiempiLeggio(TerzoLeggio);
        LeggioProvvisorio=TerzoLeggio;
    }
    else if(Giocatore==4)
    {
        RiempiLeggio(QuartoLeggio);
        LeggioProvvisorio=QuartoLeggio;
    }
}

void RisincronizzaLeggii(string LeggioProvvisorio)
{
    if(Giocatore==1)
    {
        PrimoLeggio=LeggioProvvisorio;
    }
    else if(Giocatore==2)
    {
        SecondoLeggio=LeggioProvvisorio;
    }
    else if(Giocatore==3)
    {
        TerzoLeggio=LeggioProvvisorio;
    }
    else if(Giocatore==4)
    {
        QuartoLeggio=LeggioProvvisorio;

    }
}

bool ParolaEsiste(string parola, map<string, string>& Diz)
{
    for(auto &c:parola)
    {
        c=tolower(c);
    }
    return (Diz.find(parola) != Diz.end() );


}

int ValoreLettera(char c)
{
    int inizio=0;
    int fine=Sacchetto.size()-1;
    int mezzo;

    while(inizio<=fine)
    {
        mezzo=(inizio+fine)/2;
        if(toupper(Sacchetto[mezzo].Lettera)==toupper(c))
        {
            return Sacchetto[mezzo].val;
        }
        else if(toupper(Sacchetto[mezzo].Lettera)<toupper(c))
        {
            inizio=mezzo+1;
        }
        else
        {
            fine=mezzo-1;
        }
    }

    return 0;

}


int InserisciParola(int r, int c, string parola, bool vert)
{
    if(vert && (unsigned int)r<=R-parola.size()+1 && c>=0 && r>=0) // Inserimento della parola nella griglia (verticale)
    {
        for(unsigned int i=0;i<parola.size();++i)
        {
            Griglia[r+i][c][0]=toupper(parola[i]);
        }
        return 0;
    }
    else if(!vert && (unsigned int)c<=C-parola.size()+1 && c>=0 && r>=0) // Inserimento della parola nella griglia (orizzontale)
    {
        for(unsigned int i=0;i<parola.size();++i)
        {
            Griglia[r][c+i][0]=toupper(parola[i]);
        }
        return 0;
    }
    else
    {
        cerr << "Errore. La parola esce dalla griglia." << endl;
        return -1;
    }


    return 0;
}

void InserisciSuggerimento(int r, int c, string parola, bool vert, string &Leggio)
{
    int nsc=0;
    bool trsc;
    int sc=0;

    if(vert)
    {
        // Parola verticale -> scorro le righe
        for(unsigned int rc=r;rc<r+parola.length();++rc)
        {
            if(Griglia[rc][c][0]==' ')
            {
                bool trovata=false;
                Griglia[rc][c][0]=toupper(parola[rc-r]);
                // Togli lettera dal leggio
                for(unsigned int l=0;l<Leggio.length();++l)
                {
                    if(Leggio[l]==parola[rc-r] && !trovata)
                    {
                        Leggio[l]=' ';
                        trovata=true;
                    }
                }
                if(!trovata)
                {
                    ++nsc;
                }
            }
        }

        // Elimino gli scarabei
        trsc=false;
        if(nsc==1)
        {
            sc=0;
            while(!trsc)
            {
                if(Leggio[sc]=='#')
                {
                    Leggio[sc]=' ';
                    trsc=true;
                }
                ++sc;
            }
        }

        if(nsc==2)
        {
            for(unsigned int dsc=0;dsc<Leggio.length();++dsc)
            {
                if(Leggio[dsc]=='#')
                {
                    Leggio[dsc]=' ';
                }
            }
        }
    }
    else
    {
        // Parola orizzontale -> scorro le colonne
        for(unsigned int cc=c;cc<c+parola.length();++cc)
        {
            if(Griglia[r][cc][0]==' ')
            {
                bool trovata=false;
                Griglia[r][cc][0]=toupper(parola[cc-c]);
                // Togli lettera dal leggio
                for(unsigned int l=0;l<Leggio.length();++l)
                {
                    if(Leggio[l]==parola[cc-c] && !trovata)
                    {
                        Leggio[l]=' ';
                        trovata=true;
                    }
                }
                if(!trovata)
                {
                    ++nsc;
                }
            }
        }

        // Elimino gli scarabei
        trsc=false;
        if(nsc==1)
        {
            sc=0;
            while(!trsc)
            {
                if(Leggio[sc]=='#')
                {
                    Leggio[sc]=' ';
                    trsc=true;
                }
                ++sc;
            }
        }

        if(nsc==2)
        {
            for(unsigned int dsc=0;dsc<Leggio.length();++dsc)
            {
                if(Leggio[dsc]=='#')
                {
                    Leggio[dsc]=' ';
                }
            }
        }
    }
}

void ParolaMassimaMaiuscola()
{
    for(unsigned int car=0;car<parolamax.length();++car)
    {
        parolamax[car]=toupper(parolamax[car]);
    }
}


void PuntiIntersezioni(string parola, int r, int c, int &pp, bool intersezioniverticali)
{
    if(intersezioniverticali)
    {
        int ps=0;
        int ms=1;

        // Calcola il punteggio delle intersezioni (se esistono)
        for(unsigned int l=0;l<parola.length();++l) // Per ogni lettera della parola
        {
            if(Griglia[r][l+c][0]==' ')
            {
                ps=0;
                ms=1;

                // Se la lettera della parola principale ha intersezioni e non è già sul tabellone riconta punteggio
                if(Griglia[r][c+l][0]==' ' && ((r-1>=0 && Griglia[r-1][c+l][0]!=' ') || (r+1<=R-1 && Griglia[r+1][c+l][0]!=' ')))
                {
                    if(Griglia[r][c+l][1]==' ')
                    {
                        ps+=ValoreLettera(parola[l]);
                    }
                    if(Griglia[r][c+l][1]=='2')
                    {
                        ps=ps+2*ValoreLettera(parola[l]);
                    }
                    else if(Griglia[r][c+l][1]=='3')
                    {
                        ps=ps+3*ValoreLettera(parola[l]);
                    }

                    if(Griglia[r][c+l][2]=='3')
                    {
                        ms=ms*3;
                    }
                    else if(Griglia[r][c+l][2]=='2')
                    {
                        ms=ms*2;
                    }
                }

                // Scorri perpendicolarmente in una direzione
                int scorriperpendicolare=r-1;
                if(scorriperpendicolare>=0 && Griglia[scorriperpendicolare][c+l][0]!=' ')
                {
                    while(scorriperpendicolare>=0 && Griglia[scorriperpendicolare][c+l][0]!=' ')
                    {
                        if(Griglia[scorriperpendicolare][c+l][1]==' ')
                        {
                            ps+=ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }

                        if(Griglia[scorriperpendicolare][c+l][1]=='2')
                        {
                            ps=ps+2*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }
                        else if(Griglia[scorriperpendicolare][c+l][1]=='3')
                        {
                            ps=ps+3*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }

                        if(Griglia[scorriperpendicolare][c+l][2]=='3')
                        {
                            ms=ms*3;
                        }
                        else if(Griglia[scorriperpendicolare][c+l][2]=='2')
                        {
                            ms=ms*2;
                        }
                        --scorriperpendicolare;
                    }
                }
                // Scorri perpendicolarmente nell'altra
                scorriperpendicolare=r+1;
                if(scorriperpendicolare<=R-1 && Griglia[scorriperpendicolare][c+l][0]!=' ')
                {
                    while(scorriperpendicolare<=R-1 && Griglia[scorriperpendicolare][c+l][0]!=' ')
                    {

                        if(Griglia[scorriperpendicolare][c+l][1]==' ' )
                        {
                            ps+=ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }

                        if(Griglia[scorriperpendicolare][c+l][1]=='2')
                        {
                            ps=ps+2*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }
                        else if(Griglia[scorriperpendicolare][c+l][1]=='3')
                        {
                            ps=ps+3*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }

                        if(Griglia[scorriperpendicolare][c+l][2]=='3')
                        {
                            ms=ms*3;
                        }
                        else if(Griglia[scorriperpendicolare][c+l][2]=='2')
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
    }
    else
    {
        int ps=0;
        int ms=1;

        // Calcola il punteggio delle intersezioni (se esistono)
        for(unsigned int l=0;l<parola.length();++l) // Per ogni lettera della parola
        {
            if(Griglia[r+l][c][0]==' ')
            {
                ps=0;
                ms=1;

                // Se la lettera della parola principale ha intersezioni e non è già sul tabellone riconta punteggio
                if(Griglia[r+l][c][0]==' ' && ((c-1>=0 && Griglia[r+l][c-1][0]!=' ') || (c+1<=C-1 && Griglia[c+l][c+1][0]!=' ')))
                {
                    if(Griglia[r+l][c][1]==' ')
                    {
                        ps+=ValoreLettera(parola[l]);
                    }
                    if(Griglia[r+l][c][1]=='2')
                    {
                        ps=ps+2*ValoreLettera(parola[l]);
                    }
                    else if(Griglia[r+l][c][1]=='3')
                    {
                        ps=ps+3*ValoreLettera(parola[l]);
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
                int scorriperpendicolare=c-1;
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
                            ps=ps+2*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
                        }
                        else if(Griglia[r+l][scorriperpendicolare][1]=='3')
                        {
                            ps=ps+3*ValoreLettera(Griglia[scorriperpendicolare][c+l][0]);
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
                    while(scorriperpendicolare<=R-1 && Griglia[r+l][scorriperpendicolare][0]!=' ')
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
    }



}

void PuntiParola(string parola, int colonnabottone, int rigabottone, int &punti, bool verticale)
{
    if(!verticale)
    {
        // Calcolo il suo punteggio
        int moltiplica=1;
        punteggiosingolaparola=0;

        // Punteggio della parola principale
        for(unsigned int scorrimento=colonnabottone;scorrimento<colonnabottone+parola.length();++scorrimento)
        {
            if(Griglia[rigabottone][scorrimento][1]==' ')
            {
                punti=punti+ValoreLettera(Griglia[rigabottone][scorrimento][0]);
            }
            else if(Griglia[rigabottone][scorrimento][1]=='2')
            {
                punti=punti+2*ValoreLettera(Griglia[rigabottone][scorrimento][0]);
            }
            else if(Griglia[rigabottone][scorrimento][1]=='3')
            {
                punti=punti+3*ValoreLettera(Griglia[rigabottone][scorrimento][0]);
            }
            if(Griglia[rigabottone][scorrimento][2]=='2')
            {
                moltiplica=moltiplica*2;
            }
            else if(Griglia[rigabottone][scorrimento][2]=='3')
            {
                moltiplica=moltiplica*3;
            }
        }
        punti=punti*moltiplica;
    }
    else
    {
        // Calcolo il suo punteggio
        int moltiplica=1;
        punteggiosingolaparola=0;

        // Punteggio della parola principale
        for(unsigned int scorrimento=rigabottone;scorrimento<rigabottone+parola.length();++scorrimento)
        {
            if(Griglia[scorrimento][colonnabottone][1]==' ')
            {
                punti=punti+ValoreLettera(Griglia[scorrimento][colonnabottone][0]);
            }
            else if(Griglia[scorrimento][colonnabottone][1]=='2')
            {
                punti=punti+2*ValoreLettera(Griglia[scorrimento][colonnabottone][0]);
            }
            else if(Griglia[scorrimento][colonnabottone][1]=='3')
            {
                punti=punti+3*ValoreLettera(Griglia[scorrimento][colonnabottone][0]);
            }
            if(Griglia[scorrimento][colonnabottone][2]=='2')
            {
                moltiplica=moltiplica*2;
            }
            else if(Griglia[scorrimento][colonnabottone][2]=='3')
            {
                moltiplica=moltiplica*3;
            }
        }
        punti=punti*moltiplica;
    }
}

void PuntiBonus(int lettereinserite, int &punti, bool &bnsc)
{
    if(lettereinserite==6)
    {
        punti+=10;
    }
    else if(lettereinserite==7)
    {
        punti+=30;
    }
    else if(lettereinserite==8)
    {
        punti+=50;
    }

    if(bnsc)
    {
        punti+=10;
        bnsc=false;
    }
}

int SvuotaLeggio(string &Leggio)
{
    for(unsigned l=0;l<LETTDISP;++l)
    {
        Leggio[l]=' ';
    }
    return 0;
}
