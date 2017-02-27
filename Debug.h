int QuantLettera(char lett)
{
    for(unsigned i=0;i<Sacchetto.size();++i)
    {
        if(Sacchetto[i].Lettera==lett)
        {
            return Sacchetto[i].num;
        }

    }
    return 0;
}

int VisualizzaSacchetto()
{
    cout << "Lettera" << "\t" << "Qta" << "\t" << "Valore" << endl;
    for(unsigned int i=0;i<Sacchetto.size();++i)
    {
        cout << Sacchetto[i].Lettera << "\t" << Sacchetto[i].num << "\t" << Sacchetto[i].val << endl;
    }
    return 0;
}

void VisualizzaPossibili(map<string, int>& ParolePossibili)
{
    for(auto p:ParolePossibili)
    {
        cout << p.first << "\t" << p.second << endl;
    }
}

void VisualizzaDizionario()
{
    for(auto i:Dizionario)
    {
        cout << setw(25) << i.first << "\t" << i.second << endl;
    }
}



int ContaRegole(multimap<string, string>& Multimappa, string nomeRegola)
{
    return Multimappa.count(nomeRegola);

}

int VisualizzaGriglia(int liv)
{
    cout << setw(4) << "";
    for(unsigned int c=0;c<C;++c)
    {
        cout << setw(3) << left << c+1;

    }
    cout << endl;
    for(unsigned int r=0;r<R;++r)
    {
        cout << setw(4) << left << r+1;
        for(unsigned int c=0;c<C;++c)
        {
            if(Griglia[r][c][liv]==' ')
            {
                cout << setw(3) << '-';
            }
            else
            {
                cout << setw(3) << Griglia[r][c][liv];
            }
        }
        cout << endl;
    }
    return 0;
}

int AggiungiLettera(int r, int c, char lett)
{
    Griglia[r][c][0]=lett;
    return 0;
}

int VisualizzaLeggio(string Leggio)
{
    for(unsigned int l=0;l<LETTDISP;++l)
    {
        cout << Leggio[l] << " ";
    }
    return 0;
}
