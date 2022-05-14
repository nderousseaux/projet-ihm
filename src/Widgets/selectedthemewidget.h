#ifndef SELECTEDTHEMEWIDGET_H
#define SELECTEDTHEMEWIDGET_H

#include <QWidget>
#include "../theme.h"

namespace Ui {
class SelectedThemeWidget;
}

class SelectedThemeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectedThemeWidget(QWidget *parent = nullptr, Theme *theme = nullptr);
    ~SelectedThemeWidget();

public slots:
    void update(Theme *t);

private:
    Ui::SelectedThemeWidget *ui;
    Theme* m_theme;
};

#endif // SELECTEDTHEMEWIDGET_H
