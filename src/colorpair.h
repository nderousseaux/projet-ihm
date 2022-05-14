#ifndef COLORPAIR_H
#define COLORPAIR_H

#include <QString>
#include <QColor>
#include <string>

class ColorPair
{
   public:
        //Constructeurs
        ColorPair(); //constructeur vide
        ColorPair(const ColorPair &color); //con. par copie
        ColorPair(const QString &id, const QColor &source, const QColor &target);
        ColorPair(const QString &id); //con. initialisant uniquement l’identifiant

        //Accesseurs
        QString getId();
        QColor getSource();
        QColor getTarget();
        void setId(QString id);
        void setSource(QColor source);
        void setTarget(QColor target);

        //Méthodes statiques
        static QString toRGBA(const QColor &color);
        static QString toRGB(const QColor &color);
        static QColor fromRGBA(const QString &colorStr);
        QString m_id;

    private:
        QColor m_source;
        QColor m_target;
};

#endif // COLORPAIR_H
