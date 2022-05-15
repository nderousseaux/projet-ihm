#ifndef THEMES_H
#define THEMES_H

#include "theme.h"
#include <QDir>
class Themes{
    public:
        Themes();

        //Accesseurs
        QList<Theme *> getThemes();

        Theme * newTheme();
        Theme * newThemeFromXML(QString file, QString name=nullptr, bool isSave=false);
        Theme * newThemeFromXMLPath(QString path, bool isSave=false);
        Theme * newThemeFromFile(QString path);

        QString newName(); //On renvoie un nom inédit

        void saveAll();
        QList<Theme *> importAll();
        void deleteTheme(Theme* t);

    private:
        QList<Theme *> m_themes;
};

#endif // THEMES_H
