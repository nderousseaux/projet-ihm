#include "theme.h"
#include "xmlreader.h"

//Nouveau thème
Theme::Theme(QString name){
    m_name = name;
    m_isSave = false;
    m_selected = false;
}

//Thème à partir d'un fichier source
Theme::Theme(QString name, QString file_path){
    m_name = name;
    m_colorsPair = XMLReader::import(file_path);
    m_isSave = false;
    m_selected = false;
}

//Thème à partir d'un fichier externe/interne XML
Theme::Theme(QString name, QString xml, bool isInterne){
    m_name = name;
    Theme *t = XMLReader::importXML(xml);
    m_colorsPair = t->getColorsPair();
    m_link = t->getLink();
    m_isSave = isInterne;
    m_selected = false;
}

QList<ColorPair*> Theme::getColorsPair(){
    return m_colorsPair;
}
void Theme::setColorsPair(QList<ColorPair*> cp){
    m_colorsPair=cp;
}
void Theme::addColorPair(ColorPair *colorPair){
    foreach(ColorPair *cp, m_colorsPair){
        if(cp->getSource() == colorPair->getSource()) return;
    }
    m_colorsPair.append(colorPair);
}
QString Theme::getLink(){
    return m_link;
}
void Theme::setLink(QString link){
    m_link = link;
}
QString Theme::getName(){
    return m_name;
}
void Theme::setName(QString name){
    m_name = name;
}
void Theme::save(){
    XMLReader::save(this);
}
bool Theme::getIsSave(){
    return m_isSave;
}
void Theme::setIsSave(bool save){
    m_isSave = save;
}
bool Theme::getSelected(){
    return m_selected;
}
void Theme::setSelected(bool selected){
    m_selected = selected;
}
bool Theme::isPresent(QList<ColorPair*>res, QString color){
    foreach(ColorPair *c, res){
        if(!QString::compare(ColorPair::toRGBA(c->getSource()), color)){
            return true;
        }
    }
    return false;
}
