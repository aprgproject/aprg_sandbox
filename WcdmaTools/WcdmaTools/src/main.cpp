#include "WcdmaTools.h"

#include <ProgressCounters.hpp>
#include <String/AlbaStringHelper.hpp>

#include <QApplication>


#include <Debug/AlbaDebug.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    ALBA_PRINT1("DAAN1");
    QApplication a(argc, argv);
    ALBA_PRINT1("DAAN2");
    WcdmaTools w;
    ALBA_PRINT1("DAAN3");
    if(argc==2)
    {
        ALBA_PRINT1("DAAN4");
        w.setInputFileOrDirectory(alba::stringHelper::getStringWithoutCharAtTheEnd(string(argv[1]), '"'));
    }
    ALBA_PRINT1("DAAN5");
    w.show();
    ALBA_PRINT1("DAAN6");

    ALBA_PRINT1("DAAN7");
    return a.exec();
}