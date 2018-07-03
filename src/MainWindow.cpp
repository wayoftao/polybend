#include "MainWindow.hpp"
#include "../ui/ui_MainWindow.h"

MainWindow::MainWindow(ObjectManager* om)
    : _ui(Ui::MainWindow())
    , _om(om)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    _ui.setupUi(this);
    _ui.displayWidget->setObjectManager(om);
}
