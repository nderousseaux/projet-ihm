#include "themes.h"
#include "xmlreader.h"
Themes::Themes(){}

QList<Theme *> Themes::getThemes(){
    return m_themes;
}

QString Themes::newName(){
    int i = 1;
    bool dispo = false;
    QString name;
    while(dispo != true){
        dispo = true;
        name = "Nouveau theme " + QString::number(i);
        //On regarde si le nom est dispo
        foreach(Theme * theme, getThemes()){
            if(QString::compare(theme->getName(), name) == 0){
                dispo = false;
                i++;
                break;
            }
        }
    }
    return name;
}

//Crée un nouveau thème
Theme * Themes::newTheme(){
    Theme * theme = new Theme(newName());
    m_themes.append(theme);
    return theme;
}

Theme * Themes::newThemeFromXML(QString path){
    QFileInfo fi(path);
    Theme * theme = new Theme(fi.baseName(), path, false);
    m_themes.append(theme);
    return theme;
}

Theme * Themes::newThemeFromFile(QString path){
    Theme * theme = new Theme(newName(), path);
    m_themes.append(theme);
    return theme;
}

void Themes::saveAll(){
    foreach(Theme * theme, Themes::getThemes()){
        theme->save();
    }
}

QList<Theme *> Themes::importAll(){
    QDir directory(XMLReader::basePath);
    QStringList xml = directory.entryList(QStringList() << "*.xml" << "*.xml",QDir::Files);
    foreach(QString filename, xml) {
        QString path = XMLReader::basePath + filename;
        QFileInfo fi(path);
        m_themes.append(new Theme(fi.baseName(), path, true));
    }
    return getThemes();
}
