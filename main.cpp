#include "MainWindow.h"
#include "DisplayWidget.h"
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication polybend(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow mw;
    auto disp = new DisplayWidget(nullptr);
    mw.setCentralWidget(disp);
    mw.show();
    return polybend.exec();
}
