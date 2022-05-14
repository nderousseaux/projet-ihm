#include <QMenu>
#include <QToolButton>
#include <QScrollBar>

#include "selectedthemewidget.h"
#include "ui_selectedthemewidget.h"
#include "../colorpair.h"
#include "colorpairwidget.h"
#include "mainwindow.h"

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
    }
}


void SelectedThemeWidget::on_save_btn_clicked()
{
    m_theme->save();
    emit updateTheme();
}

//Suppression du thème
void SelectedThemeWidget::on_delete_btn_clicked(){
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

//Appliquer le thème
void SelectedThemeWidget::on_apply_btn_clicked(){
}

