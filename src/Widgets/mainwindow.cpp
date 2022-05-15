#include <QListWidgetItem>
#include <QDir>
#include <QScrollBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>

#include "importwindow.h"
#include "themeitemwidget.h"
#include "../xmlreader.h"
#include "../filedownloader.h"
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
    connect(st, &SelectedThemeWidget::notification, this, &MainWindow::notification);

    ui->statusBar->addPermanentWidget(ui->label_2);
    ui->statusBar->addPermanentWidget(ui->progressBar);
    ui->progressBar->setMaximum(0);
    ui->progressBar->setMinimum(0);
    ui->label_2->setVisible(false);
    ui->progressBar->setVisible(false);
}

//Destructeur
MainWindow::~MainWindow(){
    delete ui;
}

//Importer un theme à partir d'un xml
void MainWindow::import_theme_xml(QString path){
    Theme* t = m_themes->newThemeFromXMLPath(path);
    addTheme(t);

    ui->statusBar->showMessage("L'import du fichier XML \""+t->getName()+"\" est terminé.", 5000);
}

//Importer un theme à partir d'un fichier source
void MainWindow::import_theme_src(QString path){
    Theme* t = m_themes->newThemeFromFile(path);
    addTheme(t);
    ui->statusBar->showMessage("L'import du thème venant du fichier \""+path+"\" est terminé.", 5000);
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

    ui->statusBar->showMessage("Tout les thèmes ont été sauvegardés.", 5000);
}

//Importer un nouveau thème
void MainWindow::on_btn_import_theme_clicked(){
    Import_window *im = new Import_window(this, m_themes);
    connect(im, &Import_window::addTheme, this, &MainWindow::import_theme_xml);
    connect(im, &Import_window::addThemeSrc, this, &MainWindow::import_theme_src);
    connect(im, &Import_window::addThemeUrl, this, &MainWindow::import_theme_url);
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

void MainWindow::notification(QString notif){
    ui->statusBar->showMessage(notif, 5000);
}

void MainWindow::import_theme_url(QUrl url){
    m_downloader= new FileDownloader(url, this);
    connect(m_downloader, &FileDownloader::downloaded, this, &MainWindow::download_finish);
    ui->statusBar->showMessage("Le téléchargement du thème à commencé", 5000);
    ui->label_2->setText("Téléchargement en cours...");
    ui->label_2->setVisible(true);
    ui->progressBar->setVisible(true);
}

void MainWindow::download_finish(){
    try{
        QString file = m_downloader->downloadedData();
        if(file.isEmpty()){
            throw std::invalid_argument("Invalid url");
        }
        Theme* t = m_themes->newThemeFromXML(file);
        t->setLink(m_downloader->getUrl().toString());
        addTheme(t);
        ui->statusBar->showMessage("Le téléchargement du thème est terminé", 5000);
    }
    catch(...){
        ui->statusBar->showMessage("Impossible télécharger le thème", 5000);

    }
    ui->label_2->setVisible(false);
    ui->progressBar->setVisible(false);
}

void MainWindow::closeEvent (QCloseEvent *event){
    bool allSave = true;
    foreach(Theme *t, m_themes->getThemes()){
        if(!t->getIsSave()){
            allSave = false;
            break;
        }
    }
    if(!allSave){
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Sûr ?",tr("Vous avez encore des thèmes non sauvegardés, voulez-vous quiter ?\n"),QMessageBox::No | QMessageBox::Yes,QMessageBox::Yes);
            if (resBtn != QMessageBox::Yes) {
                event->ignore();
            } else {
                event->accept();
            }
    }
    else{
        event->accept();
    }


}
