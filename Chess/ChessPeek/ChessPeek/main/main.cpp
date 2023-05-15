#include <ChessPeek/ChessPeek.hpp>

#include <iostream>

using namespace alba;
using namespace alba::chess::ChessPeek;
using namespace std;

int main() {
    ChessPeek chessPeek;

    cout << "Running chess peek." << endl;
    chessPeek.runForever();

    return 0;

}  // namespace alba::chess::ChessPeek
