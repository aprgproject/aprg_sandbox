#include <AlbaWindowsPathHandler.hpp>
#include <AprgFileExtractor.hpp>
#include <iostream>
#include <string>

using namespace alba;
using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        cout<<"There is must be only 1 argument."<<endl;
        return 1;
    }
    string inputPath(argv[1]);
    AprgFileExtractor fileExtractor(R"([LRM] || [alarm] || [UDP] || [CPU] || [syslog] || [ccns] || [tcom] || [startup] || [runtime] || [system] || [radparam] || ([bts]&&([.log]||[.zip]||[.tar])) || [snapshot] || ([tech]&&[report]) || [BTSLogFiles])");
    fileExtractor.extractAllRelevantFiles(inputPath);
}
