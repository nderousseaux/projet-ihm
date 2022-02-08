#include "../include/ColorPair.h"

ColorPair::ColorPair(){}

ColorPair::ColorPair(const ColorPair &color){ m_id = color.m_id; m_source = color.m_source; m_target = color.m_target; }
ColorPair::ColorPair(const QString &id, const QColor &color1, const QColor &color2){ m_id = id; m_source = color1; m_target = color2; }
ColorPair::ColorPair(const QString &id){ m_id = id; }

QString ColorPair::toRGBA(const QColor &color)
{
    QString rgb = color.name();
    QString alpha = QString::number(color.alpha());
    return rgb + alpha;
}

QColor ColorPair::fromRGBA(const QString &colorStr)
{
    return QColor(colorStr);
}
