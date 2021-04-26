#include "WcdmaTools.h"

#include <ProgressCounters.hpp>
#include <String/AlbaStringHelper.hpp>

#include <QApplication>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"WcdmaTools created by ARPG"<<endl;
    cout<<"APRG_CODE_VERSION: "<<APRG_CODE_VERSION<<endl;
    QApplication a(argc, argv);
    WcdmaTools w;
    if(argc==2)    {
        w.setInputFileOrDirectory(alba::stringHelper::getStringWithoutCharAtTheEnd(string(argv[1]), '"'));
    }
    w.show();
    return a.exec();
}
