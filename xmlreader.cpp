#include <QFile>
#include <QTextStream>
#include <QtXml>
#include <QList>

#include "xmlreader.h"

QString XMLReader::basePath = "saves/";

QList<ColorPair> XMLReader::import(QString path){
    //Initialiser les variables
    QDomDocument xmlBOM;
    QFile f(path);
    QList<ColorPair> colorsPair;

    //On ouvre le fichier
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
    }
    xmlBOM.setContent(&f);
    f.close();

    //On importe tout
    QDomElement root=xmlBOM.documentElement();
    QDomElement Component=root.firstChild().toElement();
    //Pour chaque élément
    while(!Component.isNull()){
        QString id = Component.attribute("id","noId");
        QColor source = ColorPair().fromRGBA(Component.attribute("source","#00000000"));
        QColor target = ColorPair().fromRGBA(Component.attribute("target","#00000000"));
        colorsPair.append(ColorPair(id, source, target));
        Component = Component.nextSibling().toElement();
    }

    return colorsPair;
};

void XMLReader::save(Theme theme){
   QDomDocument xmlBOM;
   QDomElement colors = xmlBOM.createElement("colors");
   foreach(ColorPair c, theme.getColorsPair()){
        QDomElement colorPair = xmlBOM.createElement("color");
        colorPair.setAttribute("id", c.getId());
        colorPair.setAttribute("source", ColorPair::toRGBA(c.getSource()));
        colorPair.setAttribute("target", ColorPair::toRGBA(c.getTarget()));
        colors.appendChild(colorPair);
   }
   xmlBOM.appendChild(colors);

   //On enregistre le tout
   QFile f(basePath + theme.getName() + ".xml");
   if (!f.open(QIODevice::ReadWrite))
           return;
   QTextStream out(&f);
   f.close();
}

void XMLReader::createSavePath(){
    QDir dir;
    if(!dir.exists(basePath)){
        dir.mkdir(basePath);
    }
}
