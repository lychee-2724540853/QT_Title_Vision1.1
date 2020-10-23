#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <title.h>
#include <mmenubar.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    initMenuBar();
    initTitle();
    initConnect();
}
/*************************Connections************************/
void MainWindow::initConnect()
{
    connect(my_Title, &Title::signalWindowSizeChanged, this, &MainWindow::setMenuSize);
}
/************************************************************/

/*********************initialize the MenuBar*****************/
void MainWindow::initMenuBar()
{
    my_MenueBar = new MMenuBar(this);
    QMenu * File = my_MenueBar->addMenu("文件(F)");
    File->addAction("Open");
}
/************************************************************/

/*********************inittialize the Title******************/
void MainWindow::initTitle()
{
    my_Title = new Title(this);
    my_Title->TitleContent->setText("  我的标题助手");
}
/************************************************************/

void MainWindow::setMenuSize()
{
    QRect desktopRect = QApplication::desktop()->availableGeometry();
    QRect FactRect = QRect(0, 30, desktopRect.width()-3, 28);
    my_MenueBar->setGeometry(FactRect);
}
MainWindow::~MainWindow()
{
    delete ui;
}

