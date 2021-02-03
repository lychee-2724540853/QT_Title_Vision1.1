#ifndef TITLE_H
#define TITLE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>

#define ButtonHeight 31
#define ButtonWidth 65

class Title : public QWidget
{
    Q_OBJECT
    QWidget * title_parent;
    QSize old_size;
    //restore window
    QPoint old_point;
    //move window
    QPoint last_point;
public:
    explicit Title(QWidget *parent = nullptr,bool isSizeFixed=false);
    void initButon();
    void initConnect();

    QPushButton * MinButton;
    QPushButton * MaxButton;
    QPushButton * CloseButton;

    QLabel * TitleContent;
    QLabel * TitleIcon;

private:
    bool parentSizeFixed;
    bool isPressed=false;
    void ButtonClose();
    void ButtonMin();
    void ButtonMax();
    void setTitleSize();
    void saveWindowPosInfo();
    void restoreWindowSize();
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setSheet(QString path, QPushButton * button);
    void addFrameBorder();
signals:
    void signalWindowSizeChanged();
    void signalWindowSizeRestore();

};

#endif // TITLE_H
