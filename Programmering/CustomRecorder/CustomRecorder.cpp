#include "CustomRecorder.h"


CustomRecorder::CustomRecorder()
{

}


bool CustomRecorder::onStart() {

        setProcessingInterval(sf::milliseconds(20));
        return true;

}

bool CustomRecorder::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount) {

        int samplingFreq = sf::SoundRecorder::getSampleRate();
        double N = sampleCount;

        DFT DiskretFourierTrans;
        DiskretFourierTrans.DFTrans(samples, N, samplingFreq);

        vector<double> freqSpek;
        freqSpek = DiskretFourierTrans.getFreqSpek8();

        int DTMFtable[4][4];

        DTMFtable[0][0] = 0;
        DTMFtable[0][1] = 1;
        DTMFtable[0][2] = 2;
        DTMFtable[0][3] = 3;
        DTMFtable[1][0] = 4;
        DTMFtable[1][1] = 5;
        DTMFtable[1][2] = 6;
        DTMFtable[1][3] = 7;
        DTMFtable[2][0] = 8;
        DTMFtable[2][1] = 9;
        DTMFtable[2][2] = 10;
        DTMFtable[2][3] = 11;
        DTMFtable[3][0] = 12;
        DTMFtable[3][1] = 13;
        DTMFtable[3][2] = 14;
        DTMFtable[3][3] = 15;



        // Gennemsnit metoden

        double avg = 0;
        int counter = 0;
        double freqs[2];
        int numberConst[2];



        for (int i = 0; i < 8; ++i) {
            avg = avg + freqSpek[i];
        }

        avg = avg / 8;

        int freqScale [] = {1, 1, 1, 1, 1, 1, 1, 1};

        for (int j = 0; j < 8; ++j) {
            if (((freqSpek[j] * freqScale[j]) > avg && avg > 100000))
            {
                freqs[counter] = freqSpek[j];
                numberConst[counter] = j;
                counter++;
            }

        }

        if(counter == 2) {
            if (numberConst[0] < 4 && numberConst[0] >= 0 && numberConst[1] > 3 && numberConst[1] <=7)
            {
                cout << DTMFtable[numberConst[0]] [numberConst[1]-4];
                //    cout << "Avg: " << avg << endl;
                //    cout << "Freq " << freqTable[jay[0]] << " : " << freqSpek[jay[0]] << endl;
                //    cout << "Freq " << freqTable[jay[1]] << " : " << freqSpek[jay[1]] <<  endl;

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

