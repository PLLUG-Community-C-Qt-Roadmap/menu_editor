#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Menu Editor");
    a.setApplicationVersion(QString("%1.%2").arg(MAJOR_VERSION).arg(MINOR_VERSION));

    MainWindow w;
    w.setWindowTitle("Menu Editor");
    w.show();

    return a.exec();
}
