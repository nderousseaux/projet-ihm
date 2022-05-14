#ifndef THEMEITEMWIDGET_H
#define THEMEITEMWIDGET_H
#include "../themes.h"
#include <QWidget>

namespace Ui {
class themeItemWidget;
}

class themeItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit themeItemWidget(QWidget *parent = nullptr, Theme* theme = nullptr);
    ~themeItemWidget();

public slots:
    void update();
    void click();

private:
    Ui::themeItemWidget *ui;
    Theme * m_theme; //Thème représenté

signals:
    void theme_selected(Theme *t);
};


#endif // THEMEITEMWIDGET_H
