#ifndef XMLREADER_H
#define XMLREADER_H
#include <set>
#include <QFile>
#include <QList>
#include <QMessageBox>

#include "colorpair.h"
#include "comparecolorpair.h"
#include "theme.h"

using namespace std;

class XMLReader{
    public:
        //Méthode de classes
        static QList<ColorPair> importXML(QString path);
        static QList<ColorPair> import(QString path);
        static void save(Theme * theme);
        static void createSavePath();
        static QString basePath;
};

#endif // XMLREADER_H
