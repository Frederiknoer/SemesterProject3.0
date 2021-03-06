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

        /*for(int i = 0; i < freqSpek.size(); i++)
            cout << freqSpek[i] << ",";
        cout << endl;*/
        findTones.findDtmfTones(freqSpek);

        vector<int> DTMFbuffer;
        DTMFbuffer = findTones.getDTMFBuffer();



        if (lyddata.pairFinder(DTMFbuffer) == true)
        {

            udData = lyddata.pairGetter(DTMFbuffer);
            cout << endl;
            for (int i = 0; i < udData.size(); ++i) {
                for (int j = 0; j < udData[i].size(); j++) {
                    cout << udData[i][j];
                }
            }

            Frame unframing(udData[0]);


            if(unframing.validataFrame() == true)                             //tjekker modtaget lyde igennem for bestemte frekvenser
            {
                unframing.unFrame();
                if (unframing.getFrame() == (*csmaHandler).getRTSverdi())        // Tjekker for RTS
                {
                    (*csmaHandler).setRtsFlag();                                   //sidder RTS modtaget flag
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  RTS flag sat" << endl;
                    (*csmaHandler).setBusy();                                      //indikere at pc er laver noget
                    (*csmaHandler).sendCTS();                                      //sender CTS
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  CTS sendt |" << endl;
                }
                else if (unframing.getFrame() == (*csmaHandler).getCTSverdi())     //tjekker for CTS
                {
                    (*csmaHandler).setCtsFlag();                                   //sidder CTS modtaget flag
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  CTS flag sat" << endl;
                }
                else if (unframing.getFrame() == (*csmaHandler).getACKverdi())     //tjekker for ACK
                {
                    (*csmaHandler).setAckFlag();                                   //sidder ACK modtaget flag
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  ACK flag sat" << endl;
                }
                else if(unframing.getFrame() == (*csmaHandler).getPSTOPverdi())     //tjekker for Pstop
                {
                    (*csmaHandler).setPstopFlag();                                  //sidder "pakke stop" modtaget flag
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  Pstop flag sat" << endl;

                    //Frede pakke handler på modtagetPakker (udskriv til skerment)

                    modtagetPakker = {};                                            //nulstiller pakke vektor
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  modtaget pakkeVector cleared" << endl;
                    (*csmaHandler).sendACK();                                      //sender ACK
                    (*csmaHandler).clearBusy();                                    //indikere at computeren ikke laver noget
                }
                else                                                               //ellers er det data
                {
                    (*csmaHandler).setDataFlag();                                  //sidder Data modtaget flag
                    TextHandler outputText;                                        //opretter texthandler objekt
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  data modtaget |" << endl;
                    cout << outputText.OutputText(unframing.getFrame()) << endl;
                    modtagetPakker.push_back(unframing.getFrame());                //ligger modtaget pakke ind i modtagetPakker vector
                    (*csmaHandler).sendACK();                                      //sender ACK
                    cout << "CustomRecorder.cpp [onProcessSamples]  -  ACK sendt |" << endl;
                }
            }
            else
            {
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