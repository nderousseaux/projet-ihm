#include <QMenu>
#include <QToolButton>
#include <QScrollBar>

#include "selectedthemewidget.h"
#include "ui_selectedthemewidget.h"
#include "../colorpair.h"
#include "colorpairwidget.h"
#include "mainwindow.h"
#include <QInputDialog>

//Constructeur
SelectedThemeWidget::SelectedThemeWidget(QWidget *parent, Theme* theme) :QWidget(parent),ui(new Ui::SelectedThemeWidget){
    m_theme = theme;
    ui->setupUi(this);

    update(m_theme);
}

//Destructeur
SelectedThemeWidget::~SelectedThemeWidget(){
    delete ui;
}

//On update le visuel du widget
void SelectedThemeWidget::update(Theme * t){
    m_theme = t;
    if(m_theme == nullptr){ //Affichage -> Sélectionnez un thème
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{
        //On règle le titre
        ui->stackedWidget->setCurrentIndex(0);
        ui->title->setText(m_theme->getName());

        //On règle la scrollbar
        QScrollBar *s = new QScrollBar(Qt::Vertical);
        MainWindow::applyStyle(s);
        ui->scrollArea->setVerticalScrollBar(s);


        //On crée la liste des paires de couleurs
        idx_next_column = 0;
        clearLayout(ui->column_1);
        clearLayout(ui->column_2);
        clearLayout(ui->column_3);
        for(int i=0; i<m_theme->getColorsPair().count(); i++){
            addColorPair(m_theme->getColorsPair().at(i));
        }
        ui->column_1->addStretch(1);
        ui->column_2->addStretch(1);
        ui->column_3->addStretch(1);

        ui->update_btn->setVisible(!m_theme->getLink().isEmpty());
    }
}


void SelectedThemeWidget::on_save_btn_clicked()
{
    m_theme->save();
    emit updateTheme();

    emit notification("Le thème \""+m_theme->getName()+"\" à été sauvegardé.");
}

//Suppression du thème
void SelectedThemeWidget::on_delete_btn_clicked(){
    emit notification("Le thème \""+m_theme->getName()+"\" à été supprimé.");
    emit deleteTheme(m_theme);
}

//On ajoute la paire de couleur à l'écran
void SelectedThemeWidget::addColorPair(ColorPair* cp){
    Colorpairwidget *cpw = new Colorpairwidget(this, cp);

    QVBoxLayout *l;
    switch (idx_next_column%3) {
        case 0:
            l = ui->column_1;
            break;
        case 1:
            l = ui->column_2;
            break;
        case 2:
            l = ui->column_3;
            break;
        default:
            l = ui->column_1;
    }

    l->insertWidget(
        l->count()-1,
        cpw
    );
    idx_next_column++;
}

//Vider un layout
void SelectedThemeWidget::clearLayout(QLayout* l){
    while (QLayoutItem* item = l->takeAt(0))
    {
        if (QWidget* widget = item->widget())
            widget->deleteLater();
        if (QLayout* childLayout = item->layout())
            clearLayout(childLayout);
        delete item;
    }
}


void SelectedThemeWidget::on_update_btn_clicked(){
    QInputDialog *id = new QInputDialog();
    this->setStyleSheet("QPushButton:hover{background-color: rgb(41, 105, 188); }");
    bool ok;
    QString text = id->getText(this, "URL", "Entrez l'url du thème", QLineEdit::Normal, m_theme->getLink(), &ok);

    if(ok){
        m_downloader= new FileDownloader(text, this);
        connect(m_downloader, &FileDownloader::downloaded, this, &SelectedThemeWidget::download_finish);
        emit notification("Mise à jour du thème \"" + m_theme->getName() + "\"...");
    }
}

void SelectedThemeWidget::download_finish(){
    try{
        QString file = m_downloader->downloadedData();
        if(file.isEmpty()){
            throw std::invalid_argument("Invalid url");
        }
        Theme* t= new Theme("", file, true);

        m_theme->setLink(m_downloader->getUrl().toString());
        m_theme->setColorsPair(t->getColorsPair());
        m_theme->setIsSave(false);
        emit updateTheme();
        update(m_theme);
        emit notification("La mise à jour du thème est terminé");
    }
    catch(...){
        emit notification("Impossible télécharger le thème");

    }
}

