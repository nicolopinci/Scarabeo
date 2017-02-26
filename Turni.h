void AssegnaLeggioCorrente(string &LeggioProvvisorio)
{

    LeggioProvvisorio=Leggii[Giocatore-1];

}

void FinestraPrincipale::ImpostazioneLeggio(int tessera, QString stringa)
{
    switch(tessera)
    {
    case 1:
        ui->Leggio1->setText(stringa);
        break;
    case 2:
        ui->Leggio2->setText(stringa);
        break;
    case 3:
        ui->Leggio3->setText(stringa);
        break;
    case 4:
        ui->Leggio4->setText(stringa);
        break;
    case 5:
        ui->Leggio5->setText(stringa);
        break;
    case 6:
        ui->Leggio6->setText(stringa);
        break;
    case 7:
        ui->Leggio7->setText(stringa);
        break;
    case 8:
        ui->Leggio8->setText(stringa);
        break;
    }
}

void InizializzaLeggii()
{
    for(int sl=0;sl<NumeroGiocatori;++sl)
    {
        SvuotaLeggio(Leggii[sl]);
        RiempiLeggio(Leggii[sl]);
    }

}

void FinestraPrincipale::MostraLeggioGraficoCorrente(string Leggio)
{
    for(unsigned int t=0;t<Leggio.length();++t)
    {
        FinestraPrincipale::VisualizzaLeggioGrafico(Leggio[t],t);
    }
}

void AggiornaPunteggio(int punti)
{

    PunteggiGiocatori[Giocatore-1]=PunteggiGiocatori[Giocatore-1]+punti;

}

string InserisciParolaMiglioreGiocatore(int riga, int colonna, bool verticale)
{

    InserisciParola(riga,colonna,ParolaMx.parola,verticale);
    RiempiLeggio(Leggii[Giocatore-1]);
    return Leggii[Giocatore-1];
}

DatiParola SuggerisciGiocatoreCorrente()
{

    return SuggerimentiGenerici(Leggii[Giocatore-1]);
}

void GeneraParoleCompleteGiocatore(map<string, int>& ParolePossibili)
{

    GeneraParoleComplete(Leggii[Giocatore-1], ParolePossibili);

}

void RimuoviScarabeiLeggio(int &scarab, bool &ammessa, string &LeggioProvvisorio)
{
    if(scarab>2)
    {
        ammessa=false;
    }
    else if(scarab==2)
    {
        for(unsigned int lp=0;lp<LeggioProvvisorio.length();++lp)
        {
            if(LeggioProvvisorio[lp]=='#')
            {
                LeggioProvvisorio[lp]=' ';
                --scarab;
            }
        }
        if(scarab!=0)
        {
            ammessa=false;
        }
    }
    else if(scarab==1)
    {
        for(unsigned int lp=0;lp<LeggioProvvisorio.length();++lp)
        {
            if(LeggioProvvisorio[lp]=='#')
            {
                LeggioProvvisorio[lp]=' ';
                --scarab;
            }
        }
        if(scarab!=0)
        {
            ammessa=false;
        }
    }
    else if(scarab==0)
    {
        bonusnosc=true;
    }
}

void SelezionaCella(int &rigabottone, int &colonnabottone, int &selezionato, int &r, int &c)
{
    ++selezionato;
    rigabottone=r;
    colonnabottone=c;
}

void FinestraPrincipale::FineGioco()
{
    QMessageBox fine;
    QString informazione="";
    string LeggioF="";
    AssegnaLeggioCorrente(LeggioF);

    if(LeggioF=="        ")
    {
        for(int j=0;j<NumeroGiocatori;++j)
        {
            if(j!=Giocatore-1)
            {
                for(int i=0;i<LETTDISP;++i)
                {
                    if(Leggii[j][i]!=' ')
                    {
                        PunteggiGiocatori[Giocatore-1]+=ValoreLettera(Leggii[j][i], Sacchetto);
                    }


                }
            }
        }


        if(max(max(max(PunteggiGiocatori[0], PunteggiGiocatori[1]), PunteggiGiocatori[2]), PunteggiGiocatori[3])==PunteggiGiocatori[0])
        {
            informazione+=" giocatore 1";
        }
        if(max(max(max(PunteggiGiocatori[0], PunteggiGiocatori[1]), PunteggiGiocatori[2]), PunteggiGiocatori[3])==PunteggiGiocatori[1])
        {
            informazione+=" giocatore 2";
        }
        if(max(max(max(PunteggiGiocatori[0], PunteggiGiocatori[1]), PunteggiGiocatori[2]), PunteggiGiocatori[3])==PunteggiGiocatori[2])
        {
            informazione+=" giocatore 3";
        }
        if(max(max(max(PunteggiGiocatori[0], PunteggiGiocatori[1]), PunteggiGiocatori[2]), PunteggiGiocatori[3])==PunteggiGiocatori[3])
        {
            informazione+=" giocatore 4";
        }

        if(informazione.length()>12) // Più di un vincitore
        {
            informazione="La partita è terminata. I vincitori sono: " + informazione;
            fine.information(0, "Fine della partita", informazione);

        }
        else
        {
            informazione="La partita è terminata. Ha vinto il " + informazione;
            fine.information(0, "Fine della partita", informazione);
        }
    }
}

void FinestraPrincipale::VisualizzaLeggioGrafico(char lettera, int postessera)
{
    QString stringa="";
    stringa=stringa+lettera;
    ++postessera;
    ImpostazioneLeggio(postessera, stringa);
}

void ScegliNumeroGiocatori()
{
    QInputDialog numGiocatori;
    NumeroGiocatori=numGiocatori.getInt(0, "Scarabeo","Inserire il numero dei giocatori",2,2,4,1);
}

