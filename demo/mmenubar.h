#ifndef MMENUBAR_H
#define MMENUBAR_H

#include <QWidget>
#include <QMenuBar>

class MMenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MMenuBar(QWidget *parent = nullptr);

private:
    void setSheet(QString path);
signals:

};

#endif // MMENUBAR_H
