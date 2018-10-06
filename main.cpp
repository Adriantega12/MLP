#include "mainwindow.h"
#include <QApplication>

#include "matrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    /*Matrix a(2, 3), b(3, 2), c;



    return 0;*/
}
