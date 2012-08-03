#include <QtGui/QApplication>
#include "mainwindow.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString t1 = "hello";
    QString t2 = t1;
    t1 = "test";
    cout << t2.toStdString() << endl; // hello


    cout << "START!" << endl;

    return a.exec();
}
