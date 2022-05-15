#include <QInputDialog>

#include "importwindow.h"
#include "ui_importwindow.h"
#include "mainwindow.h"

//Constructeur
Import_window::Import_window(QWidget *parent, Themes* themes) :QDialog(parent),ui(new Ui::Import_window){
    m_themes = themes;
    ui->setupUi(this);

    connect(ui->div_import_file, SIGNAL(mouseReleased()), this, SLOT(import_file_clicked()));
    connect(ui->div_import_source, SIGNAL(mouseReleased()), this, SLOT(import_source_clicked()));
    connect(ui->div_link, SIGNAL(mouseReleased()), this, SLOT(import_link_clicked()));
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

//On importe à partir d'un lien
void Import_window::import_link_clicked(){
    QInputDialog *id = new QInputDialog();
    this->setStyleSheet("QPushButton:hover{background-color: rgb(41, 105, 188); }");
    bool ok;
    QString text = id->getText(this, "URL", "Entrez l'url du thème", QLineEdit::Normal, "", &ok);

    if((QString::compare("", text)!=0)&&ok){
        emit addThemeUrl(QUrl(text));
        this->close();
    }
}
