#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QList>
#include <QDebug>
using namespace std;

#include "colorpair.h"
#include "comparecolorpair.h"
#include "xmlreader.h"

int main(int argc, char *argv[])
{
    //Affichage de la fenêtre
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
