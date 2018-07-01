#include "MainWindow.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication polybend(argc, argv);
    MainWindow mw;
    mw.show();
    return polybend.exec();
}
