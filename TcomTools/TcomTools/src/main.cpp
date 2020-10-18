#include <AlbaStringHelper.hpp>
#include <ProgressCounters.hpp>
#include <QApplication>
#include "TcomTools.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcomTools w;
    if(argc==2)
    {
        w.setInputFileOrDirectory(alba::stringHelper::getStringWithoutCharAtTheEnd(string(argv[1]), '"'));
    }
    w.show();

    return a.exec();
}
