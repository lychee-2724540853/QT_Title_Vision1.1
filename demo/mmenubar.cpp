#include "mmenubar.h"
#include <QFile>

MMenuBar::MMenuBar(QWidget *parent) : QMenuBar(parent)
{
    setStyleSheet("background-color: rgb(200, 200, 200)");
    setGeometry(QRect(0,30,parent->width(),28));
    setSheet("../sheet/MenuBar.qss");
}
void MMenuBar::setSheet(QString path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        setStyleSheet(QLatin1String(file.readAll()));
    }
}
