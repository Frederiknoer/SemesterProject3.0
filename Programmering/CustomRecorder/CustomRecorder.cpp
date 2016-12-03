#include "CustomRecorder.h"
#include "fstream"


CustomRecorder::CustomRecorder()
{

}

//CustomRecorder::CustomRecorder(csmaCA etO)
CustomRecorder::CustomRecorder(csmaCA * enP)
{
    csmaHandler = enP;
}

csmaCA * CustomRecorder::getcsmaCA()
{
    return csmaHandler;
}


bool CustomRecorder::onStart() {

        setProcessingInterval(sf::milliseconds(10));
        return true;

}

bool CustomRecorder::onProcessSamples(const sf::Int16 *samples, std::size_t sampleCount)
{

    //===================== Eksperimentalt =========================
    (*csmaHandler).setCtsFlag();                                          //snyder customrecorder til at tro at CTS er modtaget
    (*csmaHandler).setAckFlag();                                          //snyder customrecorder til at tro at ACK er modtaget
    //(*csmaHandler).setBusy();                                             //snyder customrecorder til at tro at busy er sat
    //==============================================================

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

CustomRecorder::~CustomRecorder()
{
    stop();
}

