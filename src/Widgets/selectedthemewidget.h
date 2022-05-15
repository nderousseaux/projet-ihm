#ifndef SELECTEDTHEMEWIDGET_H
#define SELECTEDTHEMEWIDGET_H

#include <QWidget>
#include "../theme.h"
#include "../filedownloader.h"

namespace Ui {
class SelectedThemeWidget;
}

class SelectedThemeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SelectedThemeWidget(QWidget *parent = nullptr, Theme *theme = nullptr);
    ~SelectedThemeWidget();
    FileDownloader* m_downloader;

public slots:
    void update(Theme *t);
    void download_finish();

private slots:
    void on_save_btn_clicked();
    void on_delete_btn_clicked();
    void on_update_btn_clicked();

private:
    Ui::SelectedThemeWidget *ui;
    Theme* m_theme;
    int idx_next_column = 0;

    void addColorPair(ColorPair* cp);
    void clearLayout(QLayout* l);

signals:
    void updateTheme();
    void deleteTheme(Theme* t);
    void notification(QString notif);
};

#endif // SELECTEDTHEMEWIDGET_H
