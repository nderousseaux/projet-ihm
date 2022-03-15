#ifndef XMLREADER_H
#define XMLREADER_H
#include <set>
#include <QFile>

#include "./ColorPair.h"
#include "./CompareColorPair.h"

using namespace std;

class XMLReader
{
    public:
        //Constructeur
        XMLReader();

        //Accesseurs
        set<ColorPair, CompareColorPair> getColorsPairs();
        void addColorPair(ColorPair c);

        //Méthode d'instance
        void read(QString file_path);

    private:
        set<ColorPair, CompareColorPair> m_colors_pair;
        QFile m_file;
};

#endif // XMLREADER_H
