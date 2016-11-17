#include "CustomRecorder.h"
#include "fstream"


CustomRecorder::CustomRecorder()
{

}


bool CustomRecorder::onStart() {

        setProcessingInterval(sf::milliseconds(10));
        return true;

}

bool CustomRecorder::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount) {


    int samplingFreq = sf::SoundRecorder::getSampleRate();
    double N = sampleCount;

    DFT DiskretFourierTrans;
    DiskretFourierTrans.DFTrans8(samples, N, samplingFreq);

    vector<double> freqSpek;
    freqSpek = DiskretFourierTrans.getFreqSpek8();

    for (int i = 0; i < 8; ++i) {
        cout << freqSpek[i] << ", ";
    }

    cout << endl;

  /*
    findTones.findDtmfTones(freqSpek);

    vector<int> DTMFbuffer;
    DTMFbuffer = findTones.getDTMFBuffer();


    if(DTMFbuffer.size() == 1)
    {
        cout << "Buffer size: " << sampleCount << endl;
        for (int i = 0; i < sampleCount; ++i) {
            cout << samples[i] << ", ";
        }
    }


    if (lyddata.pairFinder(DTMFbuffer) == true)
    {

        cout << endl;
        udData = lyddata.pairGetter(DTMFbuffer);

        for (int i = 0; i < udData.size(); ++i) {
            for (int j = 0; j < udData[i].size(); j++) {
                cout << udData[i][j];
            }
        }
        cout << endl;


        Frame unframing(udData[0]);


        if(unframing.validataFrame() == true) {
            unframing.unFrame();
            TextHandler outputText;
            cout << outputText.OutputText(unframing.getFrame()) << endl;
        } else{
            cout << "Error" << endl;
        }


        findTones.clearDTMFbuffer();
        udData.clear();
        lyddata.clearFinalData();
    }

    */
    freqSpek.clear();
    DiskretFourierTrans.clearFreqSpek8();

    return true;
}

void CustomRecorder::onStop() {


}

CustomRecorder::~CustomRecorder()
{
    stop();
}

