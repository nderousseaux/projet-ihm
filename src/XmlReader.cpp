#include <QFile>
#include <QTextStream>
#include <QtXml>

#include "XmlReader.h"

XMLReader::XMLReader(){}

set<ColorPair, CompareColorPair> XMLReader::getColorsPairs(){ return m_colors_pair; }
void XMLReader::addColorPair(ColorPair c){ m_colors_pair.insert(c); }

void XMLReader::read(QString file_path){

    //Ouvrir le fichier
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QDomDocument xmlBOM;
    xmlBOM.setContent(&file);
    file.close();
    QDomElement root=xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement();
    //Pour chaque élément
    while(!Component.isNull()){
        QString id = Component.attribute("id","noId");
        QColor source = ColorPair().fromRGBA(Component.attribute("source","#00000000"));
        QColor target = ColorPair().fromRGBA(Component.attribute("target","#00000000"));
        this->addColorPair(ColorPair(id, source, target));
        Component = Component.nextSibling().toElement();
    }
};
