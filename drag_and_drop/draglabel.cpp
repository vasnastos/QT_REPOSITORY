#include "draglabel.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


draglabel::draglabel(QString text)
{
    this->setText(text);
}

void draglabel::dragEnterEvent(QDragEnterEvent *event)
{
  event->acceptProposedAction();
}


void draglabel::dropEvent(QDropEvent *event)
{
   QString file=event->mimeData()->text();
   if(file.startsWith("file:///"))
   {
       file=file.remove(0,QString("file:///").size());
   }
   QFile fp(file);
   qDebug()<<file;
   fp.open(QIODevice::ReadOnly);
   QTextStream st(&fp);
   QString msg="<html><h2>FileDetector</h2><ul>";
   while(!st.atEnd())
   {
     msg+="<li>"+st.readLine()+"</li>";
   }
   fp.close();
   msg+="</ul></html>";
   QMessageBox::information(nullptr,"File Detect",msg);
}

void draglabel::mouseMoveEvent(QMouseEvent *ev)
{
  ev->
}
