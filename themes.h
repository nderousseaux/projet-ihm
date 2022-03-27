#ifndef THEMES_H
#define THEMES_H

#include "theme.h"
#include <QDir>
class Themes{
    public:
        Themes();

        //Accesseurs
        QList<Theme> getThemes();
        void addTheme(Theme theme);

        Theme newTheme();
        Theme importTheme(QString path);

        void saveAll();
        QList<Theme> importAll();
        Theme createTheme(QString path);

    private:
        QList<Theme> m_themes;
};

#endif // THEMES_H
