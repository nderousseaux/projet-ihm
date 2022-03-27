#include "theme.h"
#include "xmlreader.h"
Theme::Theme(QString name){
    m_name = name;
}
Theme::Theme(QString name, QString file_path){
    m_name = name;
    m_colorsPair = XMLReader::import(file_path);
}

QList<ColorPair> Theme::getColorsPair(){
    return m_colorsPair;
}
void Theme::addColorPair(ColorPair colorPair){
    foreach(ColorPair cp, m_colorsPair){
        if(cp.getSource() == colorPair.getSource()) return;
    }
    m_colorsPair.append(colorPair);
}
QString Theme::getName(){
    return m_name;
}
void Theme::setName(QString name){
    m_name = name;
}

void Theme::save(){
    XMLReader::save(*this);
}
