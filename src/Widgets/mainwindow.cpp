#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QDir>
#include "xmlreader.h"

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //On initialise les variables
    themes = *new Themes();
    XMLReader::createSavePath();

    //On importe les thèmes
    themes.importAll();

    //On rempli la liste des themes
    foreach(Theme theme, themes.getThemes()){
        QListWidgetItem *item = new QListWidgetItem;
        item->setText("  "+theme.getName());
        ui->listWidget->addItem(item);
    }
}

MainWindow::~MainWindow()
{
	delete ui;
}

//On crée un nouveau theme
void MainWindow::on_pushButton_clicked()
{
    Theme theme = themes.newTheme();
    QListWidgetItem *item = new QListWidgetItem;
    item->setText("  "+theme.getName());
    ui->listWidget->addItem(item);
}

//On enregistre tout les themes
void MainWindow::on_pushButton_2_clicked()
{
    themes.saveAll();
}

//On passe sur la vue 'import'
void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//On ferme la vue import
void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//On importe depuis un fichier .xml
void MainWindow::on_pushButton_5_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Import Theme File","","Theme (*.xml)");
    if(path == "") return;
    Theme theme = themes.importTheme(path);

    //On l'ajoute à la liste
    QListWidgetItem *item = new QListWidgetItem;
    item->setText("  "+theme.getName());
    ui->listWidget->addItem(item);

    ui->stackedWidget->setCurrentIndex(0);
}

//On importe depuis un fichier/dossier source
void MainWindow::on_pushButton_6_clicked()
{
    QString path = QFileDialog::getOpenFileName(nullptr, "Import source File","","");
    if(path == "") return;
    Theme theme = themes.createTheme(path);

    //On l'ajoute à la liste
    QListWidgetItem *item = new QListWidgetItem;
    item->setText("  "+theme.getName());
    ui->listWidget->addItem(item);

    ui->stackedWidget->setCurrentIndex(0);
}

