#include "title.h"

#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QFile>

Title::Title(QWidget *parent) : QWidget(parent)
{
    title_parent = parent;
    initButon();
    initConnect();
    setGeometry(0,0,parent->width(),28);
    setStyleSheet("background-color: rgb(255, 255, 255)");
}
/*******************initialize buttons and title content properties************/
void Title::initButon()
{
    CloseButton = new QPushButton(this);
    MaxButton = new QPushButton(this);
    MinButton = new QPushButton(this);

    TitleContent = new QLabel(this);
    TitleIcon = new QLabel(this);
    TitleContent->setText("标题");

    QHBoxLayout* mylayout = new QHBoxLayout(this);

    mylayout->addWidget(TitleIcon);
    mylayout->addWidget(TitleContent);
    mylayout->addWidget(MinButton);
    mylayout->addWidget(MaxButton);
    mylayout->addWidget(CloseButton);

    CloseButton->setFixedSize(QSize(ButtonWidth,ButtonHeight));
    MinButton->setFixedSize(QSize(ButtonWidth,ButtonHeight));
    MaxButton->setFixedSize(QSize(ButtonWidth,ButtonHeight));

    /************************set Buttons' tips***********************/
    MinButton->setToolTip(QStringLiteral("最小化"));
    MaxButton->setToolTip(QStringLiteral("最大化"));
    CloseButton->setToolTip(QStringLiteral("关闭"));

    /**********************set Buttons' styleSheets******************/
    setSheet("../demo/sheet/closeButton.qss",CloseButton);
    setSheet("../demo/sheet/Button.qss",MinButton);
    setSheet("../demo/sheet/Button.qss",MaxButton);

    QPixmap titleIcon("../demo/Img/title.jpg");
    TitleIcon->setPixmap(titleIcon.scaled(25,25));
    TitleIcon->setFixedSize(QSize(26,26));
    CloseButton->setIcon((QIcon)"../demo/Img/Close.png");
    MaxButton->setIcon((QIcon)"../demo/Img/Max0.png");
    MinButton->setIcon((QIcon)"../demo/Img/Min.png");

    mylayout->setContentsMargins(5, 0, 0, 0);
    mylayout->setSpacing(0);
}
/******************************************************************************/

/************************initialize the connections of TitleBar****************/
void Title::initConnect()
{
    connect(CloseButton, &QPushButton::clicked, this, &Title::ButtonClose);
    connect(MinButton, &QPushButton::clicked, this, &Title::ButtonMin);
    connect(MaxButton, &QPushButton::clicked, this, &Title::ButtonMax);
    connect(this,&Title::signalWindowSizeChanged, this, &Title::setTitleSize);
    connect(this, &Title::signalWindowSizeRestore, this, &Title::restoreWindowSize);
   // connect(this, &Title::mouseDoubleClickEvent, this, &Title::mouseDoubleClicked);
}
/******************************************************************************/

/*****************************Connections**************************************/
void Title::ButtonClose()
{
    title_parent->close();
}
void Title::ButtonMin()
{
    title_parent->showMinimized();
}
void Title::ButtonMax()
{
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    //Restored Window
    if(title_parent->pos().x()==0)
    {
        MaxButton->setToolTip(QStringLiteral("最大化"));
        MaxButton->setIcon((QIcon)"../demo/Img/Max0.png");
        emit signalWindowSizeRestore();
    }
    //Max Window now
    else
    {
        MaxButton->setToolTip(QStringLiteral("还原"));
        MaxButton->setIcon((QIcon)"../demo/Img/Max.png");
        old_point = title_parent->pos();
        old_size = title_parent->size();
       // title_parent->showMaximized();
        emit signalWindowSizeChanged();
    }
}
void Title::setTitleSize()
{
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(0, 0, desktopRect.width()-3, 28);
    this->setGeometry(FactRect);
    title_parent->setGeometry(QRect(0, 0, desktopRect.width(), desktopRect.height()));
}
void Title::restoreWindowSize()
{
    title_parent->setGeometry(old_point.x(),old_point.y(),old_size.width(),old_size.height());
    setParent(title_parent);
    setGeometry(0,0,title_parent->width(),28);
}
/************Double Click the TitleBar to Max or Restore Window**********/
void Title::mouseDoubleClickEvent(QMouseEvent * event)
{
    ButtonMax();
    //return Title::mouseDoubleClickEvent(event);
}
/***************************Holding Press Titl***************************/
void Title::mousePressEvent(QMouseEvent * event)
{
    if(title_parent->pos().x()!=0)
    {
        last_point = event->globalPos();
        isPressed = true;
    }
    else
        isPressed = false;
}
/***************************Move Title/Window***************************/
void Title::mouseMoveEvent(QMouseEvent * event)
{
    if(isPressed)
    {
        last_point = event->globalPos()-last_point;
        QPoint widget_pos = this->parentWidget()->pos();
        this->parentWidget()->move(widget_pos.x()+last_point.x(),widget_pos.y()+last_point.y());
        last_point = event->globalPos();
    }
}
/**************************Release Title/Window*************************/
void Title::mouseReleaseEvent(QMouseEvent * event)
{
    isPressed = false;
}

void Title::setSheet(QString path, QPushButton * button)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    if(file.isOpen())
    {
        button->setStyleSheet(QLatin1String(file.readAll()));
    }
}
