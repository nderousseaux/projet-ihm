#include "clickablewidget.h"

//Constructeur
ClickableWidget::ClickableWidget(QWidget *parent):QWidget(parent){}

//Destructeur
ClickableWidget::~ClickableWidget(){}

void ClickableWidget::mouseReleaseEvent(QMouseEvent *event){
    (void)event;
    emit mouseReleased();
}
