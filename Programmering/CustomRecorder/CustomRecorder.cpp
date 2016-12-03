#include "CustomRecorder.h"



CustomRecorder::CustomRecorder()
{
}


bool CustomRecorder::onStart() {

        setProcessingInterval(sf::milliseconds(50));
        return true;

}

bool CustomRecorder::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount) {

    int samplingFreq = sf::SoundRecorder::getSampleRate();
    double N = sampleCount;
    int numberOfProcessingSamples = 0;
    int samplePointer = 0;

    /////// Vi tjekker først antallet af samles + eventuelt tidligere samles //////

    if ((N + leftOverSamples.size()) > samplesPrDFT){
        numberOfProcessingSamples = (int)(N + leftOverSamples.size())/(samplesPrDFT);
    }else{
        cout << "Count error" << endl;
    }

    // cout << endl << sampleCount << "/" << samplesPrDFT << " = " << sampleCount/samplesPrDFT << endl;

    ///////////////////////////////////////////////////////////////////////////////

    ///// Vi starter med at bruge de tidligere samples fra sidste onProcess call /////

    for (int l = 0; l < leftOverSamples.size() ; ++l) {
        dataToProcess.push_back(leftOverSamples[l]);
    }
    leftOverSamples.clear();
    //////////////////////////////////////////////////////////////////////////////////


    for (int k = 0; k < numberOfProcessingSamples; ++k) {

        /////////////////// Vi fylder herefter op med de nye samples ///////////////////
        while(samplesPrDFT > dataToProcess.size()){
            dataToProcess.push_back(samples[samplePointer]);
            samplePointer++;
        }
        //////////////////////////////////////////////////////////////////////////////////

        DFT DiskretFourierTrans;
        DiskretFourierTrans.DFTrans8(dataToProcess, samplesPrDFT, samplingFreq);

        vector<double> freqSpek;
        freqSpek = DiskretFourierTrans.getFreqSpek8();

        for(int i = 0; i < freqSpek.size(); i++)
            cout << freqSpek[i] << ",";
        cout << endl;
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


            if (unframing.validataFrame() == true) {
                unframing.unFrame();
                TextHandler outputText;
                cout << outputText.OutputText(unframing.getFrame()) << endl;
            } else {
                cout << "Error" << endl;
            }


            findTones.clearDTMFbuffer();
            udData.clear();
            lyddata.clearFinalData();
        }

        freqSpek.clear();
        DiskretFourierTrans.clearFreqSpek8();
        dataToProcess.clear();

    }

    // cout << samplePointer << endl;

    ///// Vi tjekker om alle samples er blevet brugt eller om der er en rest /////

    if (samplePointer < sampleCount){
        for (int i = 0; i < (sampleCount-samplePointer); ++i) {
            leftOverSamples.push_back(samples[samplePointer]);
        }
     //   cout << "Left over samples: " << leftOverSamples.size() << endl;
    }else{
        if(samplePointer == sampleCount){
            // cout << "No leftovers" << endl;
        }else{
            cout << "Sampling count error - samples leftover error" << endl;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    return true;
}


void CustomRecorder::setSamplesPrDFT(int SamplesPerDTF) {
    samplesPrDFT = SamplesPerDTF;
}

void CustomRecorder::onStop() {

}

CustomRecorder::~CustomRecorder()
{
    stop();
}

