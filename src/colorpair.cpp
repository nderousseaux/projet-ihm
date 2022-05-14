#include "colorpair.h"

ColorPair::ColorPair(){}
ColorPair::ColorPair(const ColorPair &color){ m_id = color.m_id; m_source = color.m_source; m_target = color.m_target; }
ColorPair::ColorPair(const QString &id, const QColor &source, const QColor &target){ m_id = id; m_source = source; m_target = target; }
ColorPair::ColorPair(const QString &id){ m_id = id; }

QString ColorPair::getId(){ return m_id; }
QColor ColorPair::getSource(){ return m_source; }
QColor ColorPair::getTarget(){ return m_target; }

void ColorPair::setId(QString id){ m_id = id; }
void ColorPair::setSource(QColor source){ m_source = source; }
void ColorPair::setTarget(QColor target){ m_target = target; }

QString ColorPair::toRGBA(const QColor &color)
{
    return color.name();
}

QColor ColorPair::fromRGBA(const QString &colorStr)
{

    return QColor(colorStr);
}
