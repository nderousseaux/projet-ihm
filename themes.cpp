#include "themes.h"
#include "xmlreader.h"
Themes::Themes(){}

QList<Theme> Themes::getThemes(){
    return m_themes;
}
void Themes::addTheme(Theme theme){
    m_themes.append(theme);
}

//Crée un nouveau thème avec un nom pas encore pris
Theme Themes::newTheme(){
    int i = 1;
    bool dispo = false;
    QString name;
    while(dispo != true){
        dispo = true;
        name = "Nouveau theme " + QString::number(i);
        //On regarde si le nom est dispo
        foreach(Theme theme, getThemes()){
            if(QString::compare(theme.getName(), name) == 0){
                dispo = false;
                i++;
                break;
            }
        }
    }
    Theme theme = *new Theme(name);
    Themes::addTheme(theme);
    return theme;
}

Theme Themes::importTheme(QString path){
    QFileInfo fi(path);
    Theme theme = *new Theme(fi.baseName(), path);
    addTheme(theme);
    return theme;
}
void Themes::saveAll(){
    foreach(Theme theme, Themes::getThemes()){
        theme.save();
    }
}

QList<Theme> Themes::importAll(){
    QDir directory(XMLReader::basePath);
    QStringList xml = directory.entryList(QStringList() << "*.xml" << "*.xml",QDir::Files);
    foreach(QString filename, xml) {
        QFileInfo fi(XMLReader::basePath + filename);
        addTheme(*new Theme(fi.baseName()));
    }
    return getThemes();
}

//Crée un thème à partir d'un fichier/dossier source
Theme Themes::createTheme(QString path){
    Theme theme = newTheme();
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
            ColorPair c = *new ColorPair("Id", ColorPair::fromRGBA(color), "#00000000");
            theme.addColorPair(c);
        }
    }
    return theme;
}
