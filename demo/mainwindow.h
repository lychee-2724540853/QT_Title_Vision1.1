#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mmenubar.h>
#include <title.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Title * my_Title;
    MMenuBar * my_MenueBar;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initTitle();
    void initMenuBar();
    void setMenuSize();
    void initConnect();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
