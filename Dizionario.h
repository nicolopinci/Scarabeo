bool EsisteLettera(char c)
{
    int inizio=0;
    int fine=Sacchetto.size()-1;
    int mezzo;

    while(inizio<=fine)
    {
        mezzo=(inizio+fine)/2;
        if(toupper(Sacchetto[mezzo].Lettera)==toupper(c))
        {
            return true;
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
    return false;
}

int LeggiDizionario()
{
    // Lettura del dizionario
    ifstream in ("it_IT.dic", ifstream::in);
    string stringa;
    string parola="";
    string regole="";
    bool carval=true;
    bool reg=false;
    pair<string, string> elemento;
    while(in >> stringa)
    {
        reg=false;
        carval=true;
        regole="";
        parola="";
        if(stringa.length()>2)
        {
            for(auto c:stringa)
            {
                if((!EsisteLettera(c) && c!='/') || (isupper(c) && reg==false))
                {
                    carval=false;
                }
                else if(EsisteLettera(c) && reg==false)
                {
                    parola=parola+c;
                }
                else if(EsisteLettera(c) && reg==true)
                {
                    regole=regole+c;
                }
                else if(c=='/')
                {
                    reg=true;
                }
            }
            if(parola.size()>=2 && carval)
            {
                elemento={parola, regole};
                Dizionario.insert(elemento);
            }
        }
    }
    in.close();

    // Aggiungi tutte le parole di due lettere al dizionario
    for(unsigned int prima=1;prima<Sacchetto.size();++prima)
    {
        for(unsigned int seconda=1;seconda<Sacchetto.size();++seconda)
        {
            parola="";
            parola=parola+Sacchetto[prima].Lettera;
            parola=parola+Sacchetto[seconda].Lettera;
            for(char &carat:parola)
            {
                carat=tolower(carat);
            }
            elemento={parola,""};
            Dizionario.insert(elemento);
        }
    }

    return 0;
}

void LeggiRegole()
{
    string presuf, nome, togli, metti, dove;
    regola regolaSingola;
    pair<string,regola> elemento;

    ifstream in ("sc_IT.aff", ifstream::in); // Apri il file delle regole
    while(in>>presuf>>nome>>togli>>metti>>dove)
    {
        regolaSingola.dove=dove;
        regolaSingola.metti=metti;
        regolaSingola.togli=togli;
        regolaSingola.presuf=presuf;

        elemento={nome, regolaSingola};
        Regole.insert(elemento);
    }
    in.close(); // Chiudi il file delle regole
}

void EsplodiRegole() // RICONTROLLARE
{
    bool quadra=false;
    bool chiusa=false;
    bool negazione=false;
    bool scelta=false;

    int nopz;
    int posiniz=0;
    string doveSemplice="";
    for(auto i:Regole) // Per ogni regola
    {


        quadra=false;
        chiusa=false;
        negazione=false;
        nopz=0; // Numero di opzioni (possibilità fra parentesi quadre)
        posiniz=0; // Posizione iniziale delle scelte
        pair <string, regola> elemento;


        for(char c:i.second.dove) // Per ogni carattere del campo dove
        {
            if(!quadra)
            {
                ++posiniz;
            }
            if(quadra && !chiusa)
            {
                ++nopz;
            }
            if(c=='[') // La parentesi quadra indica la scelta fra più lettere
            {
                quadra=true;
            }
            else if(c==']') // Quando viene chiusa la parentesi
            {
                chiusa=true;
                --nopz;
            }
            else if(c=='^') // Il simbolo ^ indica la negazione riferita a tutto ciò che la segue all'interno della parentesi
            {
                negazione=true;
            }

        }
        if(negazione)
        {
            --nopz;
        }
        if(quadra)
        {
            for(int n=0;n<nopz;++n)
            {
                quadra=false;
                chiusa=false;
                negazione=false;
                scelta=false;

                regola Nuova;
                doveSemplice="";
                // Nuova struttura uguale alla precedente tranne per il campo DOVE
                Nuova.metti=i.second.metti;
                Nuova.togli=i.second.togli;
                Nuova.presuf=i.second.presuf;
                for(char c:i.second.dove)
                {
                    if(c=='[')
                    {
                        quadra=true;
                    }
                    else if(c==']')
                    {
                        chiusa=true;
                    }
                    else if(c=='^')
                    {
                        negazione=true;
                        doveSemplice=doveSemplice+'^';
                    }
                    else if(!quadra || (quadra && chiusa))
                    {
                        doveSemplice=doveSemplice+c;
                    }
                    else if(quadra && !chiusa && !negazione && !scelta)
                    {
                        doveSemplice=doveSemplice+i.second.dove[posiniz+n];
                        scelta=true;
                    }
                    else if(quadra && !chiusa && negazione && !scelta)
                    {
                        doveSemplice=doveSemplice+i.second.dove[posiniz+n+1];
                        scelta=true;
                    }
                }
                Nuova.dove=doveSemplice;
                elemento={i.first,Nuova};


                    RegoleEsplose.insert(elemento);


            }
        }
        else if(!quadra) // Copia la regola vecchia in RegoleEsplose
        {


                RegoleEsplose.insert({i.first, i.second});

        }
    }

    // Svuota le regole
    auto iteratore = Regole.begin();
    while (iteratore != Regole.end())
    {

        iteratore = Regole.erase(iteratore);

    }

}

void ApplicaRegole(multimap<string, regola> Tipologia)
{
    string sreg;
    string nuovaparola="";
    pair <string, string> nuovoel;
    bool quadre=false;
    bool finevalida=true;
    bool iniziovalido=true;
    bool negato=false;


    for(auto parola:Dizionario)
    {
        if(parola.second!="")
        {
            for(char reg:parola.second)
            {
                sreg=reg;
                // Cerca tutte le regole che hanno quel nome nell'elenco
                pair <std::multimap<string,regola>::iterator, std::multimap<string,regola>::iterator> intervallo;
                intervallo = Tipologia.equal_range(sreg);

                // Per ogni elemento della mappa che abbia come nome quello indicato dalla regola
                for (std::multimap<string,regola>::iterator elemento=intervallo.first; elemento!=intervallo.second; ++elemento)
                {
                    if(elemento->second.presuf=="SFX") // Caso in cui sia un suffisso
                    {
                        quadre=false;
                        for(char c:elemento->second.dove)
                        {
                            if(c=='[' || c==']')
                            {
                                quadre=true;
                            }
                        }
                        negato=false;
                        for(char c:elemento->second.dove)
                        {
                            if(c=='^')
                            {
                                negato=true;
                            }
                        }
                        if(!quadre)
                        {
                            if(elemento->second.dove==".") // DOVE? Dopo qualsiasi cosa
                            {
                                if(elemento->second.togli=="0") // Se non bisogna togliere niente...
                                {
                                    if(elemento->second.metti!="0") // ...ma bisogna aggiungere qualcosa
                                    {
                                        nuovaparola=parola.first+elemento->second.metti;
                                        nuovoel={nuovaparola, ""};
                                        DizionarioGen.insert(nuovoel);
                                    }
                                    // Non ha senso non togliere niente e non aggiungere niente: la parola rimarrebbe uguale!
                                }
                                else // Se bisogna togliere qualcosa
                                {
                                    // Vedi se esiste il pezzo da togliere
                                    finevalida=true;
                                    if(parola.first.length()>=elemento->second.togli.length())
                                    {
                                        for(unsigned int nf=parola.first.length()-1;nf>=parola.first.length()-elemento->second.togli.length();--nf)
                                        {
                                            if(parola.first[nf]!=elemento->second.togli[nf-parola.first.length()+elemento->second.togli.length()])
                                            {
                                                finevalida=false;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        finevalida=false;
                                    }
                                    // Se esiste il pezzo da togliere
                                    if(finevalida)
                                    {
                                        nuovaparola="";
                                        for(unsigned int nf=0;nf<parola.first.length()-elemento->second.togli.length();++nf)
                                        {
                                            nuovaparola=nuovaparola+parola.first[nf];
                                        }
                                        if(elemento->second.metti!="0") // Se bisogna aggiungere qualcosa
                                        {
                                            for(unsigned int nf=0;nf<elemento->second.metti.length();++nf)
                                            {
                                                nuovaparola=nuovaparola+elemento->second.metti[nf];
                                                nuovoel={nuovaparola,""};
                                            }
                                        }
                                        DizionarioGen.insert(nuovoel);

                                    }
                                }
                            }
                            else // Se invece non si può mettere la parola sempre
                            {
                                finevalida=true;

                                if(parola.first.length()>elemento->second.dove.length())
                                {
                                    for(unsigned int nf=parola.first.length()-1;nf>=parola.first.length()-elemento->second.dove.length();--nf)
                                    {
                                        if(parola.first[nf]!=elemento->second.dove[nf-parola.first.length()+elemento->second.dove.length()])
                                        {
                                            finevalida=false;
                                        }
                                    }
                                }
                                else
                                {
                                    finevalida=false;
                                }
                            }





                            // Se valgono le condizioni di tipo DOVE
                            if(finevalida)
                            {
                                if(elemento->second.togli!="0" && elemento->second.metti!="0") // Se bisogna togliere qualcosa e mettere qualcosa
                                {
                                    nuovaparola="";
                                    for(unsigned int nf=0;nf<parola.first.length()-elemento->second.togli.length();++nf)
                                    {
                                        nuovaparola=nuovaparola+parola.first[nf];
                                    }
                                    for(unsigned int nf=0;nf<elemento->second.metti.length();++nf)
                                    {
                                        nuovaparola=nuovaparola+elemento->second.metti[nf];

                                    }
                                    nuovoel={nuovaparola,""};
                                    DizionarioGen.insert(nuovoel);
                                }
                                else if(elemento->second.togli=="0" && elemento->second.metti!="0") // Se non bisogna togliere nulla ma mettere qualcosa
                                {
                                    nuovaparola=parola.first+elemento->second.metti;
                                    nuovoel={nuovaparola,""};
                                    DizionarioGen.insert(nuovoel);
                                }
                                else if(elemento->second.togli!="0" && elemento->second.metti=="0") // Se bisogna togliere senza mettere nulla
                                {
                                    nuovaparola="";
                                    for(unsigned int nf=0;nf<parola.first.length()-elemento->second.togli.length();++nf)
                                    {
                                        nuovaparola=nuovaparola+parola.first[nf];
                                    }
                                    nuovoel={nuovaparola,""};
                                    DizionarioGen.insert(nuovoel);
                                }
                            }
                        }
                    }

                    else if(elemento->second.presuf=="PFX") // Se invece è un prefisso
                    {
                        nuovaparola="";
                        quadre=false;
                        for(char c:elemento->second.dove)
                        {
                            if(c=='[' || c==']')
                            {
                                quadre=true;
                            }
                        }
                        negato=false;
                        for(char c:elemento->second.dove)
                        {
                            if(c=='^')
                            {
                                negato=true;
                            }
                        }
                        if(!quadre)
                        {
                            if(elemento->second.dove==".") // Metti sempre il prefisso
                            {
                                if(elemento->second.togli=="0") // Se non va tolto nulla
                                {
                                    if(elemento->second.metti!="0") // ...ma bisogna aggiungere qualcosa
                                    {
                                        nuovaparola=elemento->second.metti+parola.first;
                                    }
                                    nuovoel={nuovaparola,""};
                                    DizionarioGen.insert(nuovoel);
                                }
                                else if(elemento->second.togli!="0") // Se bisogna togliere qualcosa
                                {

                                    // Vedi se esiste il qualcosa da togliere
                                    iniziovalido=true;
                                    if(parola.first.length()>=elemento->second.togli.length())
                                    {
                                        for(unsigned int l=0;l<elemento->second.togli.length();++l)
                                        {
                                            if(elemento->second.togli[l]!=parola.first[l])
                                            {
                                                iniziovalido=false;
                                            }
                                        }
                                        if(iniziovalido)
                                        {
                                            if(elemento->second.metti!="0") // aggiungendo qualcosa
                                            {
                                                nuovaparola=elemento->second.metti;
                                            }
                                            for(unsigned int l=elemento->second.togli.length();l<parola.first.length();++l)
                                            {
                                                nuovaparola=nuovaparola+parola.first[l];
                                            }
                                            nuovoel={nuovaparola,""};
                                            DizionarioGen.insert(nuovoel);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if(!negato)
                                {
                                    iniziovalido=true;
                                    for(unsigned int l=0;l<elemento->second.dove.length();++l) // Vedi se l'inizio della parola è quello previsto
                                    {
                                        if(elemento->second.dove[l]!=parola.first[l])
                                        {
                                            iniziovalido=false;
                                        }
                                    }
                                }
                                else
                                {
                                    iniziovalido=false;
                                    for(unsigned int l=2;l<elemento->second.dove.length();++l) // Vedi se l'inizio della parola è quello previsto
                                    {
                                        if(elemento->second.dove[l]!=parola.first[l])
                                        {
                                            iniziovalido=true;
                                        }
                                    }
                                    if(elemento->second.dove[1]==parola.first[1])
                                    {
                                        iniziovalido=false;
                                    }
                                }
                                if(iniziovalido)
                                {
                                    if(elemento->second.togli=="0") // Se non bisogna togliere nulla
                                    {
                                        if(elemento->second.metti!="0") // ... ma bisogna mettere qualcosa
                                        {
                                            nuovaparola=elemento->second.metti+parola.first;
                                            nuovoel={nuovaparola,""};
                                            DizionarioGen.insert(nuovoel);
                                        }
                                    }
                                    else // Se bisogna togliere qualcosa
                                    {
                                        if(elemento->second.metti!="0") // ... mettendo anche qualcosa
                                        {
                                            nuovaparola=elemento->second.metti;
                                        }
                                        for(unsigned int l=elemento->second.togli.length();l<parola.first.length();++l)
                                        {
                                            nuovaparola=nuovaparola+parola.first[l];
                                        }
                                        nuovoel={nuovaparola, ""};
                                        DizionarioGen.insert(nuovoel);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    DizionarioBase.insert(Dizionario.begin(), Dizionario.end());
    Dizionario.insert(DizionarioGen.begin(), DizionarioGen.end());
}

void ImpostazioniIniziali()
{
    LeggiLettere();
    OrdinaLettere();

    InizializzaGriglia();
    ImpostaLivelli();

    LeggiDizionario();
    LeggiRegole();

    EsplodiRegole();

    ApplicaRegole(RegoleEsplose);


}
