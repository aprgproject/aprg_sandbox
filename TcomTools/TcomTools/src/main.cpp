#include "TcomTools.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    TcomTools w;
    w.show();
    return a.exec();
}
