#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application properties
    QApplication::setApplicationName("Taggleos");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Your Organization");

    MainWindow window;
    window.show();

    return app.exec();
}
