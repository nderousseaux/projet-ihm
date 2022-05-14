#include "colorpairwidget.h"
#include "ui_colorpairwidget.h"

Colorpairwidget::Colorpairwidget(QWidget *parent, ColorPair* cp) :QWidget(parent),ui(new Ui::Colorpairwidget)
{
    m_colorpair = cp;
    ui->setupUi(this);

    update();
}

Colorpairwidget::~Colorpairwidget(){
    delete ui;
}

//On update le visuel du widget
void Colorpairwidget::update(){
    if(m_colorpair->getTarget() == nullptr){
        ui->color_dst->setStyleSheet("border-image: url(:/icon/ressources/color_undefined.png) 0 0 0 0 stretch stretch;");
        ui->label_dst->setText("#000000");
    }
    else{
        ui->color_dst->setStyleSheet("background-color:"+ColorPair::toRGB(m_colorpair->getTarget()) + "; border:1px solid black;");
        ui->label_dst->setText(ColorPair::toRGB(m_colorpair->getTarget()));
    }
    ui->color_src->setStyleSheet("background-color:"+ColorPair::toRGB(m_colorpair->getSource()) + "; border:1px solid black;");
    ui->label_src->setText(ColorPair::toRGB(m_colorpair->getSource()));
}
