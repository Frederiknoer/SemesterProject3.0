#ifndef PROJEKT_DTMFFINDER_H
#define PROJEKT_DTMFFINDER_H

#include <vector>
using namespace std;

class DtmfFinder {
public:
    DtmfFinder();
    void findDtmfTones(vector<double> freqencySpek);
    bool pairFinder(vector<int>);
    vector< vector<int> > pairGetter(vector<int>);
    vector<int> getDTMFBuffer();
    void clearDTMFbuffer();
    void clearFinalData();

    ~DtmfFinder();

private:
    vector <double> DTMFCounter;
    vector <int> DTMFbuffer;
    vector< vector<int> > finalData;
};


#endif //PROJEKT_DTMFFINDER_H
