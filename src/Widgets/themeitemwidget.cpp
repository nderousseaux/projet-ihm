#include <QMessageBox>

#include "themeitemwidget.h"
#include "ui_themeitemwidget.h"

//Constructeur
themeItemWidget::themeItemWidget(QWidget *parent, Theme* theme) :QWidget(parent),ui(new Ui::themeItemWidget){
    m_theme = theme;
    ui->setupUi(this);
    update();
    connect(ui->widget, SIGNAL(mouseReleased()), this, SLOT(click()));
}

//Destructeur
themeItemWidget::~themeItemWidget(){
    delete ui;
}

//On update le visuel du widget
void themeItemWidget::update(){
    //On règle le label
    ui->label->setText(m_theme->getName());
    QFont font = ui->label->font();
    font.setItalic(!m_theme->getIsSave());
    ui->label->setFont(font);

    if(m_theme->getSelected()){
        ui->widget->setStyleSheet("\
            border-left: 4px solid rgb(41,105,188);\
            background-color:rgb(205,205,205);\
        ");
    }
    else{
        ui->widget->setStyleSheet("");
    }
}

//Click sur le widget
void themeItemWidget::click(){
    emit(theme_selected(m_theme));
}
