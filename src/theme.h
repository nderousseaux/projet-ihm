#ifndef THEME_H
#define THEME_H
#include <QList>
#include <QFileInfo>
#include "colorpair.h"

class Theme{
    public:
        Theme(QString name); //On crée un nouveau thème.
        Theme(QString name, QString file_path); //Theme a partir d'un fichier source
        Theme(QString name, QString file_path, bool isInterne); //Theme a partir d'un xml

        //Accesseurs
        QList<ColorPair*> getColorsPair();
        void setColorsPair(QList<ColorPair*> cp);
        void addColorPair(ColorPair *colorPair);
        QString getName();
        void setName(QString name);
        QString getLink();
        void setLink(QString link);
        bool getIsSave();
        void setIsSave(bool save);
        bool getSelected();
        void setSelected(bool selected);

        //Méthodes d'instances
        void save();


        static bool isPresent(QList<ColorPair*>res, QString color);
    private:
        QList<ColorPair*> m_colorsPair;
        QString m_name;
        QString m_link;
        bool m_isSave;
        bool m_selected;
};

#endif // THEME_H
