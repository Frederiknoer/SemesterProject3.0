#include "CustomRecorder.h"



CustomRecorder::CustomRecorder()
{
}

CustomRecorder::CustomRecorder(csmaCA etO)
{
    csmaHandler = etO;
}

csmaCA CustomRecorder::getcsmaCA()
{
    return csmaHandler;
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

<<<<<<< HEAD
    if (lyddata.pairFinder(DTMFbuffer) == true)
    {
=======
    ///// Vi starter med at bruge de tidligere samples fra sidste onProcess call /////

    for (int l = 0; l < leftOverSamples.size() ; ++l) {
        dataToProcess.push_back(leftOverSamples[l]);
    }
    leftOverSamples.clear();
    //////////////////////////////////////////////////////////////////////////////////

>>>>>>> windowsTestEnvironment

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

        /*for(int i = 0; i < freqSpek.size(); i++)
            cout << freqSpek[i] << ",";
        cout << endl;*/
        findTones.findDtmfTones(freqSpek);

        vector<int> DTMFbuffer;
        DTMFbuffer = findTones.getDTMFBuffer();



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


<<<<<<< HEAD
        if(unframing.validataFrame() == true)                             //tjekker modtaget lyde igennem for bestemte frekvenser
        {
            unframing.unFrame();
			if (unframing.getFrame() == csmaHandler.getRTSverdi())        // Tjekker for RTS
            {
                csmaHandler.setRtsFlag();                                   //sidder RTS modtaget flag
                cout << "CustomRecorder.cpp [onProcessSamples]  -  RTS flag sat" << endl;
                csmaHandler.sendCTS();                                      //sender CTS
                cout << "CustomRecorder.cpp [onProcessSamples]  -  CTS sendt" << endl;
            }
			else if (unframing.getFrame() == csmaHandler.getCTSverdi())     //tjekker for CTS
            {
                csmaHandler.setCtsFlag();                                   //sidder CTS modtaget flag
                cout << "CustomRecorder.cpp [onProcessSamples]  -  CTS flag sat" << endl;
            }
			else if (unframing.getFrame() == csmaHandler.getACKverdi())     //tjekker for ACK
            {
                csmaHandler.setAckFlag();                                   //sidder ACK modtaget flag
                cout << "CustomRecorder.cpp [onProcessSamples]  -  ACK flag sat" << endl;
            }
			else                                                            //ellers er det data
			{
				csmaHandler.setDataFlag();                                  //sidder Data modtaget flag
                cout << "CustomRecorder.cpp [onProcessSamples]  -  DATA flag sat" << endl;
				TextHandler outputText;                                     //opretter texthandler onjekt
				cout << outputText.OutputText(unframing.getFrame()) << endl;
                csmaHandler.sendACK();                                      //sender ACK
                cout << "CustomRecorder.cpp [onProcessSamples]  -  ACK sendt" << endl;
			}
        } else{
            cout << "Error" << endl;
=======
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
>>>>>>> windowsTestEnvironment
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

<<<<<<< HEAD
void CustomRecorder::onStop() 
{
=======
>>>>>>> windowsTestEnvironment

void CustomRecorder::setSamplesPrDFT(int SamplesPerDTF) {
    samplesPrDFT = SamplesPerDTF;
}

void CustomRecorder::onStop() {

}

CustomRecorder::~CustomRecorder()
{
    stop();
}

