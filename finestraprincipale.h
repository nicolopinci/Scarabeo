#ifndef FINESTRAPRINCIPALE_H
#define FINESTRAPRINCIPALE_H

#include <QMainWindow>
#include <string>

namespace Ui {
class FinestraPrincipale;
}

class FinestraPrincipale : public QMainWindow
{
    Q_OBJECT

public:

    explicit FinestraPrincipale(QWidget *parent = 0);
    char a;
    void VisualizzaLeggioGrafico(char lettera, int tessera);
    void AggiornaGriglia(char Matrice[][17][3]);
    void MostraLeggioGraficoCorrente(std::string Leggio);
    void ImpostazioneLeggio(int tessera, QString stringa);
    void VisualizzaScarabei();
    void FineGioco();

    ~FinestraPrincipale();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_Scar1_clicked();

    void on_Scar2_clicked();

private:
    Ui::FinestraPrincipale *ui;


};

#endif // FINESTRAPRINCIPALE_H
