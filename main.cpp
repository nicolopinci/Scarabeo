#include "finestraprincipale.h"
#include <QApplication>

using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cctype>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FinestraPrincipale w;

    w.show();

    return a.exec();
}
