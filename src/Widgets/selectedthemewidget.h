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

private slots:
    void on_save_btn_clicked();
    void on_delete_btn_clicked();

    void on_apply_btn_clicked();

private:
    Ui::SelectedThemeWidget *ui;
    Theme* m_theme;
    int idx_next_column = 0;

    void addColorPair(ColorPair* cp);
    void clearLayout(QLayout* l);

signals:
    void updateTheme();
    void deleteTheme(Theme* t);
};

#endif // SELECTEDTHEMEWIDGET_H
