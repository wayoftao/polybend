#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication polybend(argc, argv);
    MainWindow mw;
    mw.show();
    return polybend.exec();
}
