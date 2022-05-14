#include "selectedthemewidget.h"
#include "ui_selectedthemewidget.h"

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
    }



}

