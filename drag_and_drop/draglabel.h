#ifndef DRAGLABEL_H
#define DRAGLABEL_H
#include <QLabel>
#include <QString>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QDebug>

class draglabel:public QLabel
{
public:
    draglabel(QString text);
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dropLeaveEvent(QDropEvent *ev);
    void dropEvent(QDropEvent *event)override;
    void mouseMoveEvent(QMouseEvent *ev) override;
};

#endif // DRAGLABEL_H
