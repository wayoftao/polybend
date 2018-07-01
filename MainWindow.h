#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <memory>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT;
    public:
        MainWindow();
        bool poll();
        void update();

    private:
};

#endif
