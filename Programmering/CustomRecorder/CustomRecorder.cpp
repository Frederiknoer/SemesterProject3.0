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

        DtmfFinder lyddata;
        vector< vector<int> > udData;
        vector<int> DTMFbuffer = findTones.getDTMFBuffer();


         if (lyddata.pairFinder(DTMFbuffer) == true)
         {
                udData = lyddata.pairGetter(DTMFbuffer);
                for (int i = 0; i < udData.size(); i++)
                {
                    for (int j = 0; j < udData[i].size(); j++)
                    {
                        cout << udData[i][j] << endl;
                    }
                    cout << endl;
        }

    }

    return true;
    }

void CustomRecorder::onStop() {


}

CustomRecorder::~CustomRecorder()
{
    stop();
}

