using namespace std;

#include "Globali.h"
#include "finestraprincipale.h"
#include "ui_finestraprincipale.h"

#include "Sacchetto.h"
#include "Griglia.h"
#include "Dizionario.h"
#include "Parole.h"
#include "Suggerimenti.h"
#include "Turni.h"
#include "Debug.h"


FinestraPrincipale::FinestraPrincipale(QWidget *parent) : // Impostazioni iniziali della finestra principale
    QMainWindow(parent),
    ui(new Ui::FinestraPrincipale)
{
    ui->setupUi(this);

    std::thread Impostazioni(ImpostazioniIniziali);


    NumeroGiocatori();
    Impostazioni.join();

    InizializzaLeggii();

    MostraLeggioGraficoCorrente(PrimoLeggio);

}

FinestraPrincipale::~FinestraPrincipale() // Distruzione della finestra principale
{
    delete ui;
}

void FinestraPrincipale::AggiornaGriglia(char Matrice[][17][3]) // Aggiornamento grafico del contenuto della griglia
{
    for(unsigned int r=0;r<17;++r)
    {
        for(unsigned int c=0; c<17;++c)
        {
            if(Matrice[r][c][0]!=' ')
            {
                QString lettera="";
                lettera=lettera+Matrice[r][c][0];
                QLayoutItem* item = ui->gridLayout_2->itemAtPosition(r, c);
                QWidget* widget = item->widget();
                QPushButton* button = dynamic_cast<QPushButton*>(widget);
                button->setText(lettera);
                button->setStyleSheet("background-color:gray");
            }
        }
    }
}

void FinestraPrincipale::on_pushButton_clicked() // Cambio di tutte le lettere
{
    if(Giocatore==1)
    {
        if(PrimoLeggio!="        ")
        {
            for(unsigned int t=0;t<PrimoLeggio.length();++t)
            {
                for(unsigned int sacc=0;sacc<Sacchetto.size();++sacc)
                {
                    if(PrimoLeggio[t]==Sacchetto[sacc].Lettera)
                    {
                        Sacchetto[sacc].num=Sacchetto[sacc].num+1;
                    }
                }
            }
        }
        SvuotaLeggio(PrimoLeggio);
        RiempiLeggio(PrimoLeggio);


    }
    else if(Giocatore==2)
    {
        if(SecondoLeggio!="        ")
        {
            for(unsigned int t=0;t<SecondoLeggio.length();++t)
            {
                for(unsigned int sacc=0;sacc<Sacchetto.size();++sacc)
                {
                    if(SecondoLeggio[t]==Sacchetto[sacc].Lettera)
                    {
                        Sacchetto[sacc].num=Sacchetto[sacc].num+1;
                    }
                }
            }
        }

        SvuotaLeggio(SecondoLeggio);
        RiempiLeggio(SecondoLeggio);


    }
    else if(Giocatore==3)
    {
        if(TerzoLeggio!="        ")
        {
            for(unsigned int t=0;t<TerzoLeggio.length();++t)
            {
                for(unsigned int sacc=0;sacc<Sacchetto.size();++sacc)
                {
                    if(TerzoLeggio[t]==Sacchetto[sacc].Lettera)
                    {
                        Sacchetto[sacc].num=Sacchetto[sacc].num+1;
                    }
                }
            }
        }

        SvuotaLeggio(TerzoLeggio);
        RiempiLeggio(TerzoLeggio);


    }
    else if(Giocatore==4)
    {
        if(QuartoLeggio!="        ")
        {
            for(unsigned int t=0;t<QuartoLeggio.length();++t)
            {
                for(unsigned int sacc=0;sacc<Sacchetto.size();++sacc)
                {
                    if(QuartoLeggio[t]==Sacchetto[sacc].Lettera)
                    {
                        Sacchetto[sacc].num=Sacchetto[sacc].num+1;
                    }
                }
            }
        }

        SvuotaLeggio(QuartoLeggio);
        RiempiLeggio(QuartoLeggio);


    }

    // Passa il turno
    FinestraPrincipale::on_pushButton_4_clicked();

}

void FinestraPrincipale::on_pushButton_2_clicked() // Inserimento di una parola
{
    // Scorri tutti i bottoni per vedere se qualcuno è selezionato
    string LeggioProvvisorio;
    int selezionato=0;
    int rigabottone;
    int colonnabottone;
    bool ammessa;
    bool intersezione;
    QMessageBox informazioni;
    string parola;
    int scarab=0;
    lettereinserite=0;

    VisualizzaScarabei();

    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            if(Griglia[r][c][0]!=' ')
            {
                prima=false;
            }
        }
    }

    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            QLayoutItem* item = ui->gridLayout_2->itemAtPosition(r, c);
            QWidget* widget = item->widget();
            QPushButton* Bottone = dynamic_cast<QPushButton*>(widget);
            if(Bottone->isChecked())
            {
                SelezionaCella(rigabottone, colonnabottone, selezionato, r, c);
            }
        }

    }

    parola=ui->plainTextEdit->toPlainText().toStdString();

    if(parola!="" && (ParolaEsiste(parola, Dizionario) || parola.length()==2))
    {
        if(selezionato==0) // Non sono state selezionate celle
        {
            informazioni.critical(0, "Errore", "Bisogna selezionare una casella di partenza.");
            AssegnaLeggioCorrente(LeggioProvvisorio);
        }
        if(selezionato>1) // Sono state selezionate troppe celle
        {
            informazioni.critical(0, "Errore", "Hai selezionato troppe caselle. Bisogna selezionare solo la casella di partenza.");
            AssegnaLeggioCorrente(LeggioProvvisorio);

        }
        if(selezionato==1) // Effettivamente è stata selezionata una sola cella
        {
            ammessa=true;
            intersezione=false;
            LeggioProvvisorio="";

            int scelta=informazioni.question(0,"Direzione della parola","Inserire la parola in verticale o in orizzontale?", "Orizzontale", "Verticale");

            AssegnaLeggioCorrente(LeggioProvvisorio);

            switch(scelta)
            {

            // INSERIMENTO IN ORIZZONTALE
            case 0:
                intersezione=false;
                sct1=ScarabeoA;
                sct2=ScarabeoB;

                // Se la parola viene inserita in una posizione tale da non avere altre celle adiacenti (a dx o a sx) non vuote
                if(colonnabottone+parola.length()<=C && ((colonnabottone>0 && Griglia[rigabottone][colonnabottone-1][0]==' ') || (colonnabottone==0)) && (Griglia[rigabottone][colonnabottone+parola.length()][0]==' ' || colonnabottone+parola.length()==C))
                {

                    scarab=0;
                    for(unsigned int scorri=colonnabottone;scorri<colonnabottone+parola.length();++scorri)
                    {
                        if(Griglia[rigabottone][scorri][0]!=' ' && Griglia[rigabottone][scorri][0]!=toupper(parola[scorri-colonnabottone]))
                        {
                            if(parola[scorri-colonnabottone]!='#')
                            {
                                ammessa=false;
                            }
                        }

                        if(!prima && Griglia[rigabottone][scorri][0]==toupper(parola[scorri-colonnabottone])) // Esiste un'intersezione
                        {
                            intersezione=true;
                        }

                        else // Se non mi trovo nel punto dell'incrocio
                        {
                            bool trovato=false;

                            // Scorri il leggio e vedi se c'è la lettera
                            for(unsigned int l=0;l<LeggioProvvisorio.length();++l)
                            {
                                if(toupper(LeggioProvvisorio[l])==toupper(parola[scorri-colonnabottone]) && !trovato)
                                {
                                    LeggioProvvisorio[l]=' ';
                                    trovato=true;
                                }

                            }
                            if(!trovato)
                            {
                                ++scarab;
                                if(sct1==' ')
                                {
                                    sct1=toupper(parola[scorri-rigabottone]);
                                }
                                else
                                {
                                    sct2=toupper(parola[scorri-rigabottone]);
                                }
                            }
                        }
                    }
                    RimuoviScarabeiLeggio(scarab, ammessa, LeggioProvvisorio);
                }


                // Se invece le celle alle estremità della parola sono piene
                else
                {
                    ammessa=false;
                }

                // Se la parola è la prima ed è possibile metterla in una certa posizione (serve nel caso in cui la griglia venga definita come più corta delle lettere disponibili)
                if(ammessa && prima)
                {
                    intersezione=true;
                    if(rigabottone!=8) // La parola infatti deve passare per il centro
                    {
                        ammessa=false;
                    }
                    else if(rigabottone==8)
                    {
                        if(colonnabottone<=8 && colonnabottone+parola.size()>8) // La parola però può iniziare anche prima del centro
                        {
                            ammessa=true;
                        }
                        else
                        {
                            ammessa=false;
                        }
                    }

                }

                // Se la parola è ammessa (criteri precedenti) e forma un'intersezione
                // Intersezione è true per la prima parola, anche se in realtà essendo l'unica non forma intersezioni
                if(ammessa && intersezione)
                {

                    for(unsigned int scorri=colonnabottone;scorri<colonnabottone+parola.length();++scorri)
                    {
                        string parolaperpendicolare="";
                        int scorriperpendicolare=rigabottone;

                        if(Griglia[rigabottone][scorri][0]==' ')
                        {
                            ++lettereinserite;
                        }

                        // Vai su
                        while(scorriperpendicolare>0 && Griglia[scorriperpendicolare-1][scorri][0]!=' ')
                        {
                            --scorriperpendicolare;
                        }


                        // Leggi tutta la parola che si interseca (in verticale)
                        while((scorriperpendicolare<=R-1 && Griglia[scorriperpendicolare][scorri][0]!=' ') || scorriperpendicolare==rigabottone)
                        {
                            if(scorriperpendicolare!=rigabottone)
                            {
                                parolaperpendicolare=parolaperpendicolare+Griglia[scorriperpendicolare][scorri][0];
                            }
                            else // La lettera non si trova già sul tabellone
                            {
                                parolaperpendicolare=parolaperpendicolare+parola[scorri-colonnabottone];
                            }
                            ++scorriperpendicolare;
                        }

                        // Se l'intersezione non esiste la parola non viene accettata
                        // Vengono accettate le intersezioni che formano parole di 2 lettere
                        if(!ParolaEsiste(parolaperpendicolare, Dizionario) && parolaperpendicolare.length()>2)
                        {
                            ammessa=false;
                        }
                    }
                }
                if(ammessa && intersezione) // Parola inseribile in orizzontale
                {
                    //prima=false;
                    AggiornaGriglia(Griglia);

                    if(ScarabeoA==' ')
                    {
                        ScarabeoA=toupper(sct1);
                    }

                    if(ScarabeoB==' ')
                    {
                        ScarabeoB=toupper(sct2);
                    }

                    punteggioperp=0;

                    PuntiIntersezioni(parola, rigabottone, colonnabottone, punteggioperp, true); // intersezioni verticali

                    InserisciParola(rigabottone,colonnabottone, parola,false); // orizzontale

                    PuntiParola(parola, colonnabottone, rigabottone, punteggiosingolaparola, false); // parola orizzontale
                    punteggiosingolaparola+=punteggioperp;

                    PuntiBonus(lettereinserite, punteggiosingolaparola, bonusnosc);

                    AggiornaPunteggio(punteggiosingolaparola);

                    RisincronizzaLeggii(LeggioProvvisorio);
                    RiempiLeggioCorrente(LeggioProvvisorio);

                    FineGioco();

                    FinestraPrincipale::on_pushButton_4_clicked(); // giocatore successivo

                }
                else
                {
                    informazioni.critical(0,"Errore","La parola non può essere inserita in questa posizione.");

                    AssegnaLeggioCorrente(LeggioProvvisorio);

                }
                break;



            case 1: // Parola principale verticale

                sct1=ScarabeoA;
                sct2=ScarabeoB;

                intersezione=false;

                // Se la parola viene inserita in una posizione tale da non avere altre celle adiacenti (sopra/sotto) non vuote
                if(rigabottone+parola.length()<=R && ((rigabottone>0 && Griglia[rigabottone-1][colonnabottone][0]==' ') || (rigabottone==0)) && (Griglia[rigabottone+parola.length()][colonnabottone][0]==' ' || rigabottone+parola.length()==R))
                {

                    scarab=0;
                    for(unsigned int scorri=rigabottone;scorri<rigabottone+parola.length();++scorri)
                    {
                        if(Griglia[scorri][colonnabottone][0]!=' ' && Griglia[scorri][colonnabottone][0]!=toupper(parola[scorri-rigabottone]))
                        {
                            if(parola[scorri-rigabottone]!='#')
                            {
                                ammessa=false;
                            }
                        }

                        if(!prima && Griglia[scorri][colonnabottone][0]==toupper(parola[scorri-rigabottone])) // Esiste un'intersezione
                        {
                            intersezione=true;
                        }

                        else // Se non mi trovo nel punto dell'incrocio
                        {
                            bool trovato=false;

                            // Scorri il leggio e vedi se c'è la lettera
                            for(unsigned int l=0;l<LeggioProvvisorio.length();++l)
                            {
                                if(toupper(LeggioProvvisorio[l])==toupper(parola[scorri-rigabottone]) && !trovato)
                                {
                                    LeggioProvvisorio[l]=' ';
                                    trovato=true;
                                }

                            }
                            if(!trovato)
                            {
                                ++scarab;

                                if(sct1==' ')
                                {
                                    sct1=toupper(parola[scorri-rigabottone]);
                                }
                                else
                                {
                                    sct2=toupper(parola[scorri-rigabottone]);
                                }
                            }
                        }
                    }
                    RimuoviScarabeiLeggio(scarab, ammessa, LeggioProvvisorio);
                }


                // Se invece le celle alle estremità della parola sono piene
                else
                {
                    ammessa=false;
                }

                // Se la parola è la prima ed è possibile metterla in una certa posizione (serve nel caso in cui la griglia venga definita come più corta delle lettere disponibili)
                if(ammessa && prima)
                {
                    intersezione=true;
                    if(colonnabottone!=8) // La parola infatti deve passare per il centro
                    {
                        ammessa=false;
                    }
                    else if(colonnabottone==8)
                    {
                        if(rigabottone<=8 && rigabottone+parola.size()>8) // La parola però può iniziare anche prima del centro
                        {
                            ammessa=true;
                        }
                        else
                        {
                            ammessa=false;
                        }
                    }

                }

                // Se la parola è ammessa (criteri precedenti) e forma un'intersezione
                // Intersezione è true per la prima parola, anche se in realtà essendo l'unica non forma intersezioni
                if(ammessa && intersezione)
                {

                    for(unsigned int scorri=rigabottone;scorri<rigabottone+parola.length();++scorri)
                    {
                        string parolaperpendicolare="";
                        int scorriperpendicolare=colonnabottone;

                        if(Griglia[scorri][colonnabottone][0]==' ')
                        {
                            ++lettereinserite;
                        }

                        // Vai su
                        while(scorriperpendicolare>0 && Griglia[scorri][scorriperpendicolare-1][0]!=' ')
                        {
                            --scorriperpendicolare;
                        }


                        // Leggi tutta la parola che si interseca (in verticale)
                        while((scorriperpendicolare<=C-1 && Griglia[scorri][scorriperpendicolare][0]!=' ') || scorriperpendicolare==colonnabottone)
                        {
                            if(scorriperpendicolare!=colonnabottone)
                            {
                                parolaperpendicolare=parolaperpendicolare+Griglia[scorri][scorriperpendicolare][0];
                            }
                            else // La lettera non si trova già sul tabellone
                            {
                                parolaperpendicolare=parolaperpendicolare+parola[scorri-rigabottone];
                            }
                            ++scorriperpendicolare;
                        }

                        // Se l'intersezione non esiste la parola non viene accettata
                        // Vengono accettate le intersezioni che formano parole di 2 lettere
                        if(!ParolaEsiste(parolaperpendicolare, Dizionario) && parolaperpendicolare.length()>2)
                        {
                            ammessa=false;
                        }
                    }
                }
                if(ammessa && intersezione) // Parola inseribile in orizzontale
                {
                    //prima=false;

                    if(ScarabeoA==' ')
                    {
                        ScarabeoA=toupper(sct1);
                    }

                    if(ScarabeoB==' ')
                    {
                        ScarabeoB=toupper(sct2);
                    }

                    punteggioperp=0;

                    PuntiIntersezioni(parola, rigabottone, colonnabottone, punteggioperp, false); // intersezioni orizzontali

                    InserisciParola(rigabottone,colonnabottone, parola,true); // verticali

                    PuntiParola(parola, colonnabottone, rigabottone, punteggiosingolaparola, true); // parola verticaleR
                    punteggiosingolaparola+=punteggioperp;

                    PuntiBonus(lettereinserite, punteggiosingolaparola, bonusnosc);

                    AggiornaPunteggio(punteggiosingolaparola);

                    RisincronizzaLeggii(LeggioProvvisorio);
                    RiempiLeggioCorrente(LeggioProvvisorio);
                    FineGioco();

                    FinestraPrincipale::on_pushButton_4_clicked(); // giocatore successivo
                }
                else
                {
                    informazioni.critical(0,"Errore","La parola non può essere inserita in questa posizione.");

                    AssegnaLeggioCorrente(LeggioProvvisorio);

                }

                break;
            }

            AggiornaGriglia(Griglia);


        }

    }
    else
    {
        informazioni.critical(0, "Errore", "Inserire una parola valida.");
        AssegnaLeggioCorrente(LeggioProvvisorio);
        ammessa=false;
        intersezione=false;
    }

    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            QLayoutItem* item = ui->gridLayout_2->itemAtPosition(r, c);
            QWidget* widget = item->widget();
            QPushButton* Bottone = dynamic_cast<QPushButton*>(widget);
            if(Bottone->isChecked())
            {
                Bottone->setChecked(false);

            }
        }

    }



    QString nomegiocatore="Giocatore "+ QString::number(Giocatore);
    ui->label->setText(nomegiocatore);

    RiempiLeggioCorrente(LeggioProvvisorio);

    MostraLeggioGraficoCorrente(LeggioProvvisorio);

    VisualizzaScarabei();


}

void FinestraPrincipale::on_pushButton_4_clicked() // Passa il turno senza cambiare le lettere
{

    // Passa il turno
    if(Giocatore==1)
    {
        Giocatore=2;

        for(unsigned int t=0;t<SecondoLeggio.length();++t)
        {
            this->VisualizzaLeggioGrafico(SecondoLeggio[t],t);
        }
        this->repaint();
    }
    else if(Giocatore==2)
    {
        if(numgioc==2)
        {
            Giocatore=1;
            for(unsigned int t=0;t<PrimoLeggio.length();++t)
            {
                this->VisualizzaLeggioGrafico(PrimoLeggio[t],t);
            }
            this->repaint();
        }
        else
        {
            Giocatore=3;
            for(unsigned int t=0;t<TerzoLeggio.length();++t)
            {
                this->VisualizzaLeggioGrafico(TerzoLeggio[t],t);
            }
            this->repaint();
        }
    }
    else if(Giocatore==3)
    {
        if(numgioc==3)
        {
            Giocatore=1;
            for(unsigned int t=0;t<PrimoLeggio.length();++t)
            {
                this->VisualizzaLeggioGrafico(PrimoLeggio[t],t);
            }
            this->repaint();
        }
        else
        {
            Giocatore=4;
            for(unsigned int t=0;t<QuartoLeggio.length();++t)
            {
                this->VisualizzaLeggioGrafico(QuartoLeggio[t],t);
            }
            this->repaint();
        }
    }
    else if(Giocatore==4)
    {
        Giocatore=1;
        for(unsigned int t=0;t<PrimoLeggio.length();++t)
        {
            this->VisualizzaLeggioGrafico(PrimoLeggio[t],t);
        }

    }
    ui->label->setText("Giocatore " + QString::number(Giocatore));
}

void FinestraPrincipale::on_pushButton_3_clicked() // Suggerimenti
{

    parolamax="";
    QMessageBox indicaparola;
    QMessageBox nessunaparola;
    prima=true;

    for(int r=0;r<R;++r)
    {
        for(int c=0;c<C;++c)
        {
            if(Griglia[r][c][0]!=' ')
            {
                prima=false;
            }
        }
    }

    VisualizzaScarabei();

    if(prima)
    {
        GeneraParoleCompleteGiocatore();
        EsplodiScarabei();
        TrovaPrimaMigliore();
        QString informazione="La parola migliore è " + QString::fromUtf8(parolamax.c_str()) + " e vale " + QString::number(ptmx);
        int scelta=indicaparola.information(0,"Parola migliore",informazione, "Inserire la parola", "Evidenziare la cella di partenza");

        int contamancanti=0;
        int numeroscarabei=0;


        switch(scelta)
        {
        case 0: // Inserire la parola

            LeggioP=InserisciParolaMiglioreGiocatore(8, colonnamax, false);


            contamancanti=0;
            numeroscarabei=0;

            for(unsigned int letteranecessaria=0;letteranecessaria<parolamax.length();++letteranecessaria)
            {
                bool trovato=false;
                for(int letteraleggio=0;letteraleggio<LETTDISP;++letteraleggio)
                {
                    if(tolower(parolamax[letteranecessaria])==tolower(LeggioP[letteraleggio]) && !trovato)
                    {
                        LeggioP[letteraleggio]=' ';
                        trovato=true;
                    }

                }
                if(!trovato)
                {
                    ++contamancanti;
                    if(sct1==' ')
                    {
                        sct1=toupper(parolamax[letteranecessaria]);
                    }
                    else
                    {
                        sct2=toupper(parolamax[letteranecessaria]);
                    }
                }
            }

            // Conto gli scarabei
            numeroscarabei=0;
            for(unsigned int nsc=0;nsc<LeggioP.length();++nsc)
            {
                if(LeggioP[nsc]=='#')
                {
                    ++numeroscarabei;
                }
            }
            if(contamancanti==0 || (contamancanti==1 && numeroscarabei>=1) || (contamancanti==2 && numeroscarabei==2))
            {
                // Se ci sono gli scarabei li elimino (q.b.)
                if(numeroscarabei==1)
                {
                    int nsc=0;
                    while(LeggioP[nsc]!='#')
                    {
                        ++nsc;
                    }
                    if(ScarabeoA==' ')
                    {
                        ScarabeoA=toupper(sct1);
                    }
                    else if(ScarabeoB==' ')
                    {
                        ScarabeoB=toupper(sct2);
                    }
                    VisualizzaScarabei();
                    LeggioP[nsc]=' ';
                }
                else if(numeroscarabei==2)
                {
                    for(unsigned int nsc=0;nsc<LeggioP.length();++nsc)
                    {
                        if(LeggioP[nsc]=='#')
                        {
                            if(ScarabeoA==' ')
                            {
                                ScarabeoA=toupper(sct1);
                            }
                            else if(ScarabeoB==' ')
                            {
                                ScarabeoB=toupper(sct2);
                            }
                            VisualizzaScarabei();
                            LeggioP[nsc]=' ';
                        }
                    }
                }
            }


            AggiornaGriglia(Griglia);
            AggiornaPunteggio(ptmx);

            RisincronizzaLeggii(LeggioP);
            RiempiLeggioCorrente(LeggioP);

            FinestraPrincipale::on_pushButton_4_clicked(); // Passa al giocatore successivo
            this->repaint();
            prima=false;

            break;
        case 1: // Selezionare la cella di partenza della parola
            for(int r=0;r<R;++r)
            {
                for(int c=0;c<C;++c)
                {
                    QLayoutItem* item = ui->gridLayout_2->itemAtPosition(r, c);
                    QWidget* widget = item->widget();
                    QPushButton* Bottone = dynamic_cast<QPushButton*>(widget);
                    if(r==8 && c==colonnamax)
                    {
                        Bottone->setChecked(true);
                    }
                }

            }
            break;

        }
        SvuotaPossibili();
    }
    else
    {

        SvuotaPossibili();
        DatiParola InfoMigliore;
        bool letteratrovata;
        string LeggioCopiato="";
        AssegnaLeggioCorrente(LeggioCopiato);
        int modsug=indicaparola.information(0,"Modalità di suggerimento","<qt>Il programma può cercare la parola migliore nelle seguenti modalità:<br ><br >"
                                                                         "<b>Scansione completa di tutte le parole del dizionario</b><br><font size = 2>Trova effettivamente la parola migliore ma può impiegare qualche minuto.</font><br><br>"
                                                                         "<b>Scansione delle parole di base</b><br><font size = 2>Trova la parola migliore tra le parole di base, ovvero tra quelle già presenti nel dizionario di partenza.</font></qt>",
                                            "Ricerca completa", "Ricerca ristretta");
        InfoMigliore=SuggerisciGiocatoreCorrente(modsug);

        parolamax=InfoMigliore.parola;
        ptmx=InfoMigliore.punteggio;
        maxvert=InfoMigliore.maxdirvert;
        rigamax=InfoMigliore.riga;
        colonnamax=InfoMigliore.colonna;

        if(parolamax=="")
        {
            nessunaparola.information(0, "Nessuna parola", "Non è possibile inserire parole con le lettere a disposizione.");
            return;
        }
        ParolaMassimaMaiuscola();

        QString informazione="La parola migliore è " + QString::fromUtf8(parolamax.c_str()) + ", vale " + QString::number(ptmx) + " ed è posizionata in ";

        if(maxvert)
        {
            informazione=informazione+" verticale.";
        }
        else
        {
            informazione=informazione+" orizzontale.";
        }
        int scelta=indicaparola.information(0,"Parola migliore",informazione, "Inserire la parola", "Evidenziare la cella di partenza");

        int contascarabei=0;
        switch(scelta)
        {
        case 0: // Inserimento della parola

            letteratrovata=false;
            contascarabei=0;

            for(int ls=0;ls<LeggioCopiato.size();++ls)
            {
                if(LeggioCopiato[ls]=='#')
                {
                    ++contascarabei;
                }
            }

            if(contascarabei>0)
            {


                for(int ll=0;ll<InfoMigliore.parola.size();++ll)
                {
                    letteratrovata=false;
                    for(int li=0;li<LeggioCopiato.size();++li)
                    {
                        if(!letteratrovata)
                        {
                            // Se la lettera è nel leggio oppure esisteva già sul tabellone
                            if(toupper(LeggioCopiato[li])==toupper(InfoMigliore.parola[ll]) || ((maxvert && Griglia[rigamax+ll][colonnamax][0]!=' ') || (!maxvert && Griglia[rigamax][colonnamax+ll][0]!=' ')))
                            {
                                letteratrovata=true;
                            }
                        }
                    }

                    if(!letteratrovata)
                    {
                        if(ScarabeoA==' ')
                        {
                            ScarabeoA=toupper(InfoMigliore.parola[ll]);
                        }
                        else
                        {
                            ScarabeoB=toupper(InfoMigliore.parola[ll]);
                        }

                    }
                }

            }

            InserisciParolaMiglioreGiocatore(rigamax, colonnamax, maxvert);
            AggiornaGriglia(Griglia);

            AggiornaPunteggio(ptmx);
            VisualizzaScarabei();
            RisincronizzaLeggii(InfoMigliore.LeggioR);
            RiempiLeggioCorrente(InfoMigliore.LeggioR);
            FineGioco();
            FinestraPrincipale::on_pushButton_4_clicked(); // Passa al giocatore successivo
            this->repaint();

            break;
        case 1: // Evidenzia la cella di inizio della parola
            for(int r=0;r<R;++r)
            {
                for(int c=0;c<C;++c)
                {
                    QLayoutItem* item = ui->gridLayout_2->itemAtPosition(r, c);
                    QWidget* widget = item->widget();
                    QPushButton* Bottone = dynamic_cast<QPushButton*>(widget);
                    if(r==rigamax && c==colonnamax)
                    {
                        Bottone->setChecked(true);
                    }
                }
            }
            break;
        }

    }
    VisualizzaScarabei();

}

void FinestraPrincipale::on_pushButton_5_clicked() // Punteggi
{
    QMessageBox Punteggi;
    QString Messaggio="";
    Messaggio=Messaggio+"Giocatore 1:\t"+QString::number(PunteggioA);
    Messaggio=Messaggio+"\nGiocatore 2:\t"+QString::number(PunteggioB);
    if(numgioc>=3)
    {
        Messaggio=Messaggio+"\nGiocatore 3:\t"+QString::number(PunteggioC);
        if(numgioc==4)
        {
            Messaggio=Messaggio+"\nGiocatore 4:\t"+QString::number(PunteggioD);
        }
    }
    Punteggi.information(0, "Riepilogo dei punteggi", Messaggio);
}

void FinestraPrincipale::on_Scar1_clicked()
{
    unsigned int ll=0;
    bool trovato=false;
    string LeggioS;
    AssegnaLeggioCorrente(LeggioS);
    while(ll<LeggioS.length() && !trovato)
    {
        QString corrente="";
        corrente+=LeggioS[ll];
        if(corrente==ui->Scar1->text())
        {
            LeggioS[ll]='#';
            ui->Scar1->setText("");
            ScarabeoA=' ';
            trovato=true;
        }
        ++ll;
    }
    RisincronizzaLeggii(LeggioS);
    MostraLeggioGraficoCorrente(LeggioS);
}

void FinestraPrincipale::on_Scar2_clicked()
{
    unsigned int ll=0;
    bool trovato=false;
    string LeggioS;
    AssegnaLeggioCorrente(LeggioS);
    while(ll<LeggioS.length() && !trovato)
    {
        QString corrente="";
        corrente+=LeggioS[ll];
        if(corrente==ui->Scar2->text())
        {
            LeggioS[ll]='#';
            ui->Scar2->setText("");
            ScarabeoB=' ';
            trovato=true;
        }
        ++ll;
    }
    RisincronizzaLeggii(LeggioS);
    MostraLeggioGraficoCorrente(LeggioS);
}
