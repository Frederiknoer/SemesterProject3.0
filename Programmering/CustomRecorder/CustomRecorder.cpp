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

    vector<int> DTMFbuffer;
    DTMFbuffer = findTones.getDTMFBuffer();



    if (lyddata.pairFinder(DTMFbuffer) == true)
    {

        udData = lyddata.pairGetter(DTMFbuffer);

        for (int i = 0; i < udData.size(); ++i) {
            for (int j = 0; j < udData[i].size(); j++) {
                cout << udData[i][j];
            }
        }
        cout << endl;


        Frame unframing(udData[0]);

        vector<int> RTS = {15,15,3,2};
        vector<int> CTS = {11,8,6,10};
        vector<int> ACK = {1,1,4,12};


        if(unframing.validataFrame() == true) {
            unframing.unFrame();
			if (unframing.getFrame() == RTS)
				rtsFlag = 1;
			else if (unframing.getFrame() == CTS)
				ctsFlag = 1;
			else if (unframing.getFrame() == ACK)
				ackFlag;
			else
			{
				dataFlag = 1;
				TextHandler outputText;
				cout << outputText.OutputText(unframing.getFrame()) << endl;
			}
        } else{
            cout << "Error" << endl;
        }


        findTones.clearDTMFbuffer();
        udData.clear();
        lyddata.clearFinalData();
    }

    return true;
}

void CustomRecorder::onStop() 
{


}
void CustomRecorder::resetRTS()
{
	rtsFlag = 0;
}
void CustomRecorder::resetCTS()
{
	ctsFlag = 0;
}
void CustomRecorder::resetACK()
{
	ackFlag = 0;
}
void CustomRecorder::resetDATA()
{
	dataFlag = 0;
}

CustomRecorder::~CustomRecorder()
{
    stop();
}

