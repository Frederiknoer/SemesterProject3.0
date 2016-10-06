#include <iostream>
#include"Frame.h"
using namespace std;

int main() {
    Frame a(15);
    a.setFlag();
    a.setParitybit();
    cout << "Data in frame   : 0000 1111" << endl<<endl;
    cout << "Data from frame : " << a.getFrame() << endl;
    cout << "Data should be  : 2114912382" << endl << endl;

    cout << "________________________________________________________________" << endl << endl;

    Frame b(126);
    b.setFlag();
    b.setParitybit();
    cout << "Data in frame   : 01111110" << endl<<endl;
    cout << "Data from frame : " << b.getFrame() << endl;
    cout << "Data should be  : 2122170494" << endl << endl;

    cout << "________________________________________________________________" << endl << endl;

    return 0;
}