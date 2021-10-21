#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setPalette(QPalette(QColor(49,52,59)));
    return a.exec();
}
