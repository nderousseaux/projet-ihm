#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "../themes.h"
#include "../theme.h"
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

    static void applyStyle(QScrollBar* scrollBar);

public slots:
    //Importer un thème à partir d'un XML
    void import_theme_xml(QString path);
    void import_theme_src(QString path);

    //On clique sur un thème
    void select_theme(Theme* t);
    void selected_theme_update();
    void delete_theme(Theme *t);

private:
	Ui::MainWindow *ui;
    Themes* m_themes; //Liste de tout les thèmes
    Theme* m_selected_theme; //Thème sélectionné

    //On ajoute un thème à la liste (visuelle uniquement)
    void addTheme(Theme * t);

private slots:
    void on_btn_new_theme_clicked(); //On ajoute un thème vierge à la liste
    void on_btn_save_all_clicked(); //On enregistre tout
    void on_btn_import_theme_clicked(); //On importe un thème


signals:
    //Mettre à jour la liste des thèmes
    void update_themes_list();
    void new_theme_selected(Theme *);
};
#endif // MAINWINDOW_H
