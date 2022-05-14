#include <QMessageBox>

#include "importwindow.h"
#include "ui_importwindow.h"
#include "mainwindow.h"

//Constructeur
Import_window::Import_window(QWidget *parent, Themes* themes) :QDialog(parent),ui(new Ui::Import_window){
    m_themes = themes;
    ui->setupUi(this);

    connect(ui->div_import_file, SIGNAL(mouseReleased()), this, SLOT(import_file_clicked()));
    connect(ui->div_import_source, SIGNAL(mouseReleased()), this, SLOT(import_source_clicked()));
}

//Destructeur
Import_window::~Import_window(){
    delete ui;
}

//Choisi un fichier xml à importer
void Import_window::import_file_clicked(){
    QString path = QFileDialog::getOpenFileName(
        this,
        tr("Select file to import"),
        nullptr,
        "XML Files (*.xml)"
    );
    if(path != ""){
        emit addTheme(path);
        this->close();
    }
}

//Choisi un theme source
void Import_window::import_source_clicked(){
    QString path = QFileDialog::getOpenFileName(
        this,
        tr("Select file to import"),
        nullptr,
        "All files (*.*)"
    );
    if(path != ""){
        emit addThemeSrc(path);
        this->close();
    }
}
