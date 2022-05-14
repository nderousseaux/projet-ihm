#ifndef CLICKABLEWIDGET_H
#define CLICKABLEWIDGET_H

#include <QWidget>

class ClickableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ClickableWidget(QWidget *parent = nullptr);
    ~ClickableWidget();
protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    //Mettre à jour la liste des thèmes
    void mouseReleased();

};
#endif // CLICKABLEWIDGET_H
