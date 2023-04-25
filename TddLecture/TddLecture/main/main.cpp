#include <TddLecture.hpp>

#include <iostream>

using namespace alba;
using namespace std;

int main() {
    TddLecture tddLecture;
    TddLecture::UnsignedInts oneToTen(tddLecture.getUnsignedIntsOneToTen());

    cout << "The first element is: " << oneToTen[0] << "\n";

    return 0;
}
