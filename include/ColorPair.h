#ifndef COLORPAIR_H
#define COLORPAIR_H

#include <QString>
#include <QColor>
#include <string>

class ColorPair
{
   public:
        ColorPair(); //constructeur vide
        ColorPair(const ColorPair &color); //con. par copie
        ColorPair(const QString &id, const QColor &color1, const QColor &color2);
        ColorPair(const QString &id); //con. initialisant uniquement l’identifiant

        static QString toRGBA(const QColor &color);
        static QColor fromRGBA(const QString &colorStr);

    private:
        QString m_id;
        QColor m_source;
        QColor m_target;
};

#endif // COLORPAIR_H
