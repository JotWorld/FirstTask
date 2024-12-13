#include "mainwindow.h"
#include "Qtransformfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Qtransformfile qtf;
    QApplication a(argc, argv);
    QString pathFile = "C:/Users/acer/Documents/qgraph/qtgraph.txt";
    qtf.buildmatrix(qtf.read(pathFile));
    MainWindow w;
    w.show();
    return a.exec();
}
