bool acompare(elemSacc lhs, elemSacc rhs) {return lhs.Lettera < rhs.Lettera;}

int LeggiLettere()
{
    // Memorizzo le lettere, la loro quantità e i loro valori in uno struct
    // A mano a mano che queste vengono distribuite il numero complessivo di lettere nel sacchetto diminuisce

    ifstream in ("Lettere.txt", ifstream::in);
    unsigned int i=0;
    char lettera;
    int num, val;
    while(in >> lettera >> num >> val)
    {
        Sacchetto.push_back(elemSacc());
        Sacchetto[i].Lettera=lettera;
        Sacchetto[i].num=num;
        Sacchetto[i].val=val;
        ++i;
    }
    in.close();
    return 0;
}

int TotaleLettere()
{
    int somma=0;
    for(unsigned int i=0;i<Sacchetto.size();++i)
    {
        somma=somma+Sacchetto[i].num;
    }
    return somma;
}

char EstraiLettera()
{
    srand(time(NULL));

    int casuale=rand()%TotaleLettere();
    int somma=0;
    for(unsigned int i=0;i<Sacchetto.size();++i)
    {
        somma=somma+Sacchetto[i].num;
        if(casuale<somma && casuale>=somma-Sacchetto[i].num)
        {
            Sacchetto[i].num=Sacchetto[i].num-1;
            return Sacchetto[i].Lettera;
        }

    }
    return '-';
}



int RiempiLeggio(string &Leggio)
{
    for(unsigned int l=0;l<LETTDISP;++l)
    {
        if(Leggio[l]==' ' && TotaleLettere()>=1)
        {
            Leggio[l]=EstraiLettera();
        }
        else if(Leggio[l]==' ' && TotaleLettere()==0)
        {
            Leggio[l]=' ';
        }
    }
    return 0;
}

int OrdinaLettere()
{
    sort(Sacchetto.begin(), Sacchetto.end(), acompare);
    return 0;
}
