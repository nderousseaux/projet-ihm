#ifndef THEME_H
#define THEME_H
#include <QList>
#include <QFileInfo>
#include "colorpair.h"

class Theme{
    public:
        Theme(QString name);
        Theme(QString name, QString file_path);

        //Accesseurs
        QList<ColorPair> getColorsPair();
        void addColorPair(ColorPair colorPair);
        QString getName();
        void setName(QString name);

        //Méthodes d'instances
        void save();

    private:
        QList<ColorPair> m_colorsPair;
        QString m_name;
};

#endif // THEME_H
