#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(resources); // loads icons

    Window window;
    window.show();

    return app.exec();
}