//#include "view.h"
#include <QApplication>
//#include <Windows.h>
//#include <WTypes.h>
//#include "CManagerObjs.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    //CView w;
    //w.show();
	// This will cause the application to exit when
    // the signals finished.    
    //QObject::connect(&w, SIGNAL(finished()), &a, SLOT(quit()));
    int ret = a.exec();
	return ret;
}
