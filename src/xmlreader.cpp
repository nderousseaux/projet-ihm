#include <QFile>
#include <QTextStream>
#include <QtXml>
#include <QList>

#include "xmlreader.h"

QString XMLReader::basePath = "saves/";

QList<ColorPair*> XMLReader::importXML(QString path){
    //Initialiser les variables
    QDomDocument xmlBOM;
    QFile f(path);
    QList<ColorPair*> colorsPair;

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
        colorsPair.append(new ColorPair(id, source, target));
        Component = Component.nextSibling().toElement();
    }

    return colorsPair;
};

QList<ColorPair*> XMLReader::import(QString path){
    QList<ColorPair*> res;
    //On rempli le theme avec les couleurs du fichier
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
    }
    QTextStream stream(&f);
    QString file = stream.readAll();
    f.close();
    QString color;
    for(int i = 0; i<file.length(); i++){
        if(file[i] == '#'){
             color = file.mid(i, 9);
            if(!Theme::isPresent(res, color)){
                res.append(new ColorPair("Id", ColorPair::fromRGBA(color), nullptr));
            }
        }
    }
    return res;
};

void XMLReader::save(Theme * theme){
   QDomDocument xmlBOM;
   QDomElement colors = xmlBOM.createElement("colors");
   foreach(ColorPair *c, theme->getColorsPair()){
        ColorPair co = *c;
        QDomElement colorPair = xmlBOM.createElement("color");
        colorPair.setAttribute("id", co.getId());
        colorPair.setAttribute("source", ColorPair::toRGBA(co.getSource()));
        colorPair.setAttribute("target", ColorPair::toRGBA(co.getTarget()));
        colors.appendChild(colorPair);
   }
   xmlBOM.appendChild(colors);

   //On enregistre le tout
   QFile f(basePath + theme->getName() + ".xml");
   if (!f.open(QIODevice::ReadWrite))
           return;
   QTextStream out(&f);
   out << xmlBOM.toString();
   theme->setIsSave(true);
   f.close();
}

void XMLReader::createSavePath(){
    QDir dir;
    if(!dir.exists(basePath)){
        dir.mkdir(basePath);
    }
}
//Supprimer un fichier
void XMLReader::deleteFile(QString name){
    QDir dir(basePath);
    dir.remove(name + ".xml");
}
