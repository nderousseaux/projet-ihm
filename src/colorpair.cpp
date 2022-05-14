#include "colorpair.h"

ColorPair::ColorPair(){}
ColorPair::ColorPair(const ColorPair &color){ m_id = color.m_id; m_source = color.m_source; m_target = color.m_target; }
ColorPair::ColorPair(const QString &id, const QColor &source, const QColor &target){m_id = id; m_source = source; m_target = target; }
ColorPair::ColorPair(const QString &id){ m_id = id; }

QString ColorPair::getId(){ return m_id; }
QColor ColorPair::getSource(){ return m_source; }
QColor ColorPair::getTarget(){ return m_target; }

void ColorPair::setId(QString id){ m_id = id; }
void ColorPair::setSource(QColor source){ m_source = source; }
void ColorPair::setTarget(QColor target){ m_target = target; }

QString ColorPair::toRGBA(const QColor &color)
{
    if(color != nullptr){
        int alpha = color.alpha();
        return ColorPair::toRGB(color) + QString("%1").arg(alpha, 2, 16, QLatin1Char( '0' ));
    }
    else{
        return "nullptr";
    }
}
QString ColorPair::toRGB(const QColor &color)
{
    return color.name();
}

QColor ColorPair::fromRGBA(const QString &colorStr)
{
    if(QString::compare("nullptr", colorStr)==0){
        return nullptr;
    }
    bool bStatus = false;
    QString r = colorStr.mid(1, 2);
    uint rh = r.toUInt(&bStatus,16);
    QString g = colorStr.mid(3, 2);
    uint gh = g.toUInt(&bStatus,16);
    QString b = colorStr.mid(5, 2);
    uint bh = b.toUInt(&bStatus,16);
    QString a = colorStr.mid(7, 2);
    uint ah = a.toUInt(&bStatus,16);
    return QColor(rh,gh,bh,ah);
}
