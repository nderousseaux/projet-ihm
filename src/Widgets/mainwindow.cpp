#include <QListWidgetItem>
#include <QDir>
#include <QScrollBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "importwindow.h"
#include "themeitemwidget.h"
#include "../xmlreader.h"
#include "selectedthemewidget.h"

//Constructeur
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    m_selected_theme = nullptr;
    ui->setupUi(this); 
    //On affiche la liste des thèmes
    m_themes = new Themes();
    foreach(Theme *theme, m_themes->importAll()){
        addTheme(theme);
    }
    ui->layout_list_theme->addStretch(1);

    //On règle la scrollbar
    QScrollBar *s = new QScrollBar(Qt::Vertical);
    applyStyle(s);
    ui->listTheme->setVerticalScrollBar(s);

    //On règle la zone theme sélectionné
    SelectedThemeWidget *st = new SelectedThemeWidget(this, m_selected_theme);
    ui->selected_theme->layout()->addWidget(st);
    connect(this, &MainWindow::new_theme_selected, st, &SelectedThemeWidget::update);
    connect(st, &SelectedThemeWidget::updateTheme, this, &MainWindow::selected_theme_update);
    connect(st, &SelectedThemeWidget::deleteTheme, this, &MainWindow::delete_theme);
}

//Destructeur
MainWindow::~MainWindow(){
    delete ui;
}

//Importer un theme à partir d'un xml
void MainWindow::import_theme_xml(QString path){
    Theme* t = m_themes->newThemeFromXML(path);
    addTheme(t);
}

//Importer un theme à partir d'un fichier source
void MainWindow::import_theme_src(QString path){
    Theme* t = m_themes->newThemeFromFile(path);
    addTheme(t);
}

//On ajoute un thème à la liste (visuelle)
void MainWindow::addTheme(Theme * t){
    themeItemWidget *theme = new themeItemWidget(this, t);
    QObject::connect(this, &MainWindow::update_themes_list, theme, &themeItemWidget::update);
    connect(theme, &themeItemWidget::theme_selected, this, &MainWindow::select_theme);
    ui->layout_list_theme->insertWidget(
        ui->layout_list_theme->count()-1,
        theme
    );
}

//L'utilisateur clique sur un thème
void MainWindow::select_theme(Theme *t){
    if(m_selected_theme != nullptr)
        m_selected_theme->setSelected(false);
    m_selected_theme = t;
    if(m_selected_theme != nullptr)
        m_selected_theme->setSelected(true);

    emit update_themes_list();
    emit new_theme_selected(m_selected_theme);
}

// BOUTONS

//Ajoute un nouveau thème à la liste (visuelle)
void MainWindow::on_btn_new_theme_clicked(){
    addTheme(m_themes->newTheme());
}

//Enregistrer tout
void MainWindow::on_btn_save_all_clicked(){
    m_themes->saveAll();
    emit update_themes_list();
}

//Importer un nouveau thème
void MainWindow::on_btn_import_theme_clicked(){
    Import_window *im = new Import_window(this, m_themes);
    connect(im, &Import_window::addTheme, this, &MainWindow::import_theme_xml);
    connect(im, &Import_window::addThemeSrc, this, &MainWindow::import_theme_src);
    im->setModal(true);
    ui->centralwidget->setEnabled(false);
    im->exec();
    ui->centralwidget->setEnabled(true);
}

//Le thème sélectionné à été changé
void MainWindow::selected_theme_update(){
    emit update_themes_list();
}

//Appliquer un style
void MainWindow::applyStyle(QScrollBar* scrollBar){
    QString style;
    QFile file(":/css/ressources/scrollbar.css");
    if(file.open(QIODevice::ReadOnly))
        style= file.readAll();
    file.close();
    scrollBar->setStyleSheet(style);
}

//Supprimer un thème
void MainWindow::delete_theme(Theme *t){
    m_themes->deleteTheme(t); //On le supprime logiquement

    //On le supprime visuellement
    for(int i =0; i<ui->layout_list_theme->count()-1; i++){
        themeItemWidget* it = (themeItemWidget*)ui->layout_list_theme->itemAt(i)->widget();

        if(t == it->getTheme()){
            it->close();
            delete it;
            break;
        }
    }

    emit new_theme_selected(nullptr);

}
