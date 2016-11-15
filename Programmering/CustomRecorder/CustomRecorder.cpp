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

        findTones.findDtmfTones(freqSpek);

    return true;
    }

void CustomRecorder::onStop() {


}

CustomRecorder::~CustomRecorder()
{
    stop();
}

