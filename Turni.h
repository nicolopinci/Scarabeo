void AssegnaLeggioCorrente(string &LeggioProvvisorio)
{
    if(Giocatore==1)
    {
        LeggioProvvisorio=PrimoLeggio;
    }
    else if(Giocatore==2)
    {
        LeggioProvvisorio=SecondoLeggio;
    }
    else if(Giocatore==3)
    {
        LeggioProvvisorio=TerzoLeggio;
    }
    else if(Giocatore==4)
    {
        LeggioProvvisorio=QuartoLeggio;
    }
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
    SvuotaLeggio(PrimoLeggio);
    RiempiLeggio(PrimoLeggio);
    SvuotaLeggio(SecondoLeggio);
    RiempiLeggio(SecondoLeggio);


    if(numgioc>2)
    {
        SvuotaLeggio(TerzoLeggio);
        RiempiLeggio(TerzoLeggio);
    }
    if(numgioc>3)
    {
        SvuotaLeggio(QuartoLeggio);
        RiempiLeggio(QuartoLeggio);
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
    if(Giocatore==1)
    {
        PunteggioA=PunteggioA+punti;
    }
    else if(Giocatore==2)
    {
        PunteggioB=PunteggioB+punti;
    }
    else if(Giocatore==3)
    {
        PunteggioC=PunteggioC+punti;
    }
    else if(Giocatore==4)
    {
        PunteggioD=PunteggioD+punti;
    }
}

string InserisciParolaMiglioreGiocatore(int riga, int colonna, bool verticale)
{
    if(Giocatore==1)
    {
        InserisciParola(riga,colonna,parolamax,verticale);
        RiempiLeggio(PrimoLeggio);
        return PrimoLeggio;

    }
    else if(Giocatore==2)
    {
        InserisciParola(riga,colonna,parolamax,verticale);
        RiempiLeggio(SecondoLeggio);
        return SecondoLeggio;

    }
    else if(Giocatore==3)
    {
        InserisciParola(riga,colonna,parolamax,verticale);
        RiempiLeggio(TerzoLeggio);
        return TerzoLeggio;

    }
    else if(Giocatore==4)
    {
        InserisciParola(riga,colonna,parolamax,verticale);
        RiempiLeggio(QuartoLeggio);
        return QuartoLeggio;

    }
    return "";
}

DatiParola SuggerisciGiocatoreCorrente(int modsug)
{
    if(Giocatore==1)
    {
        return SuggerimentiGenerici(PrimoLeggio, modsug);
    }
    else if(Giocatore==2)
    {
        return SuggerimentiGenerici(SecondoLeggio, modsug);
    }
    else if(Giocatore==3)
    {
        return SuggerimentiGenerici(TerzoLeggio, modsug);
    }
    else if(Giocatore==4)
    {
        return SuggerimentiGenerici(QuartoLeggio, modsug);
    }
    return SuggerimentiGenerici(PrimoLeggio, modsug);
}

void GeneraParoleCompleteGiocatore()
{
    if(Giocatore==1)
    {
        GeneraParoleComplete(PrimoLeggio);
    }
    else if(Giocatore==2)
    {
        GeneraParoleComplete(SecondoLeggio);
    }
    else if(Giocatore==3)
    {
        GeneraParoleComplete(TerzoLeggio);
    }
    else if(Giocatore==4)
    {
        GeneraParoleComplete(QuartoLeggio);
    }
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
        if(Giocatore==1)
        {
            for(int i=0;i<LETTDISP;++i)
            {
                if(SecondoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(SecondoLeggio[i]);
                }

                if(TerzoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(TerzoLeggio[i]);
                }

                if(QuartoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(QuartoLeggio[i]);
                }
            }
        }

        if(Giocatore==2)
        {
            for(int i=0;i<LETTDISP;++i)
            {
                if(PrimoLeggio[i]!=' ')
                {
                    PunteggioB+=ValoreLettera(PrimoLeggio[i]);
                }

                if(TerzoLeggio[i]!=' ')
                {
                    PunteggioB+=ValoreLettera(TerzoLeggio[i]);
                }

                if(QuartoLeggio[i]!=' ')
                {
                    PunteggioB+=ValoreLettera(QuartoLeggio[i]);
                }
            }
        }

        if(Giocatore==3)
        {
            for(int i=0;i<LETTDISP;++i)
            {
                if(SecondoLeggio[i]!=' ')
                {
                    PunteggioC+=ValoreLettera(SecondoLeggio[i]);
                }

                if(PrimoLeggio[i]!=' ')
                {
                    PunteggioC+=ValoreLettera(PrimoLeggio[i]);
                }

                if(QuartoLeggio[i]!=' ')
                {
                    PunteggioC+=ValoreLettera(QuartoLeggio[i]);
                }
            }
        }

        if(Giocatore==4)
        {
            for(int i=0;i<LETTDISP;++i)
            {
                if(SecondoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(SecondoLeggio[i]);
                }

                if(TerzoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(TerzoLeggio[i]);
                }

                if(PrimoLeggio[i]!=' ')
                {
                    PunteggioA+=ValoreLettera(PrimoLeggio[i]);
                }
            }
        }

        if(max(max(max(PunteggioA, PunteggioB), PunteggioC), PunteggioD)==PunteggioA)
        {
            informazione+=" giocatore 1";
        }
        if(max(max(max(PunteggioA, PunteggioB), PunteggioC), PunteggioD)==PunteggioB)
        {
            informazione+=" giocatore 2";
        }
        if(max(max(max(PunteggioA, PunteggioB), PunteggioC), PunteggioD)==PunteggioC)
        {
            informazione+=" giocatore 3";
        }
        if(max(max(max(PunteggioA, PunteggioB), PunteggioC), PunteggioD)==PunteggioD)
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

void NumeroGiocatori()
{
    QInputDialog numGiocatori;
    numgioc=numGiocatori.getInt(0, "Scarabeo","Inserire il numero dei giocatori",2,2,4,1);
}
