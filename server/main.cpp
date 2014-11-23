#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create application main window
    MainWindow w;
    w.show();

    // Enter main event loop
    return a.exec();
}
