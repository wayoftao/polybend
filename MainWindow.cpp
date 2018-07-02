#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow()
    : _ui(Ui::MainWindow())
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    _ui.setupUi(this);
}
