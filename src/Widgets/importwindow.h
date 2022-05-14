#ifndef IMPORT_WINDOW_H
#define IMPORT_WINDOW_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Import_window;
}

class Import_window : public QDialog
{
    Q_OBJECT

public:
    explicit Import_window(QWidget *parent = nullptr, Themes* themes = nullptr);
    ~Import_window();
public slots:
    void import_file_clicked();
    void import_source_clicked();
private:
    Ui::Import_window *ui;
    Themes *m_themes;
    MainWindow m_parent;
signals:
    //Mettre à jour la liste des thèmes
    void addTheme(QString path);
    void addThemeSrc(QString path);
};
#endif // IMPORT_WINDOW_H
