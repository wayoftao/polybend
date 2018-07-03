#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "../ui/ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
        MainWindow();

private:
        Ui::MainWindow _ui;
};

#endif
