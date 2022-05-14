#ifndef COLORPAIRWIDGET_H
#define COLORPAIRWIDGET_H

#include <QWidget>
#include "../colorpair.h"

namespace Ui {
class Colorpairwidget;
}

class Colorpairwidget : public QWidget
{
    Q_OBJECT

public:
    explicit Colorpairwidget(QWidget *parent = nullptr, ColorPair *cp = nullptr);
    ~Colorpairwidget();

public slots:
    void update();

private:
    Ui::Colorpairwidget *ui;
    ColorPair * m_colorpair;
};

#endif // COLORPAIRWIDGET_H
