#include "../../View/CView.h"

#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CView w;
    w.show();
    return a.exec();
}
