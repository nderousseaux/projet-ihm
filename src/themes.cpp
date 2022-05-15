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

Theme * Themes::newThemeFromXML(QString file, QString name, bool isSave){
    if(name == nullptr){
        name = Themes::newName();
    }
    Theme * theme = new Theme(name, file, isSave);
    m_themes.append(theme);
    return theme;
}

Theme * Themes::newThemeFromXMLPath(QString path, bool isSave){
    //On ouvre le fichier, et on lit son contenu
    QFileInfo fi(path);
    QString text;
    QFile f(path);
    //On ouvre le fichier
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
        throw std::invalid_argument("Unable to open file" );

    }
    text = f.readAll();
    f.close();
    return this->newThemeFromXML(text, fi.baseName(), isSave);
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
        this->newThemeFromXMLPath(path, true);
    }
    return getThemes();
}

//Supprimer un thème
void Themes::deleteTheme(Theme* t){
    int idx = 0;
    int i=0;
    foreach(Theme * th, m_themes){
        if(th == t){
            idx=i;
        }
        i++;
    }
    //On supprime le fichier egalemment
    XMLReader::deleteFile(t->getName());
    m_themes.removeAt(idx);
}
