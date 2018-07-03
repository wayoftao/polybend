#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char** argv)
{
    QApplication polybend(argc, argv);
    ObjectManager om;
    MainWindow mw(&om);
    mw.show();
    return polybend.exec();
}
