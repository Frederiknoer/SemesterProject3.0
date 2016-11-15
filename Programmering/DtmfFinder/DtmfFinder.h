#ifndef PROJEKT_DTMFFINDER_H
#define PROJEKT_DTMFFINDER_H

#include <vector>
using namespace std;

class DtmfFinder {
public:
    DtmfFinder();
    void findDtmfTones(vector<double> freqencySpek);

    ~DtmfFinder();

private:
    vector <double> DTMFCounter;
    vector <double> DTMFbuffer;
};


#endif //PROJEKT_DTMFFINDER_H
