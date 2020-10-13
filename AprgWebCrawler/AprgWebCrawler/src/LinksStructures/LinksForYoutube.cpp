#include "LinksForYoutube.hpp"

#include <iostream>

using namespace std;

namespace alba
{

bool LinksForYoutube::isInvalid() const
{
    return linkForVideo.empty() || localPathForCurrentVideo.empty();
}

void LinksForYoutube::printLinks() const
{
    cout << "linkForVideo : " << linkForVideo << endl;
    cout << "videoFileName : " << localPathForCurrentVideo << endl;
}

}
