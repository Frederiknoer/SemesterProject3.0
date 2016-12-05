#include "csmaCA.h"

using namespace std;


csmaCA::csmaCA()
{
    srand(time(NULL));		//initalisere random gen seed

    switch (rand() % 4)		//Random ID
    {
        case 0:
            ID = { 0xf, 0xf };
            break;
        case 1:
            ID = { 0xb, 0x4 };
            break;
        case 2:
            ID = { 0xa, 0xa };
            break;
        case 3:
            ID = {0x3, 0x0};
            break;
        case 4:
            ID = { 0x2, 0xf };
            break;
    }
}



csmaCA::csmaCA(vector<int> newID)
{
    if (newID.size() > 2)
        cout << "Fejl! - intastede ID overskrider maximum l�ngde p� 2 x 4bits" << endl;
    else
        ID = newID;

}



csmaCA::csmaCA(vector<int> newID, vector<int> TagetID)
{
    if (newID.size() > 2)
        cout << "csmaCA.cpp [csmaCA(vector<int>, vector<int>)]  -  Fejl! intastede (ID) overskrider maximum l�ngde p� 2 x 4bits" << endl;
    else
        ID = newID;

    if (TagetID.size() > 2)
        cout << "csmaCA.cpp [csmaCA(vector<int>, vector<int>)]  -  Fejl! intastede (Taget ID) overskrider maximum l�ngde p� 2 x 4bits" << endl;
    else
        tagetID = TagetID;
}



void csmaCA::setTagetID(vector<int> tID)
{
    if (tID.size() > 2)
        cout << "csmaCA.cpp [setTagetID(vector<int>)]  -  Fejl! intastede ID overskrider maximum l�ngde p� 2 x 4bits" << endl;
    else
        tagetID = tID;
}



vector<int> csmaCA::getTagetID()
{
    return tagetID;
}



void csmaCA::setID(vector<int> newID)
{
    if (newID.size() > 2)
        cout << "csmaCA.cpp [setID()]  -  Fejl! intastede ID overskrider maximum l�ngde p� 2 x 4bits" << endl;
    else
        ID = newID;
}



vector<int> csmaCA::getID()
{
    return ID;
}



bool csmaCA::sendData(vector<int> Data)
{
    Sound mySound3;						//opretter sound objekt (til delay)
    if (!makeHandShake())				//retunere false hvis handshake fejler
        return false;

    Frame csmaCAframer(Data);			//Opretter frame objekt
 //   csmaCAframer.makeFrame();			//framer data

    //vent p� at et ack modtages
    for (int dataAttempts = 1; dataAttempts <= sendAttempts; dataAttempts++)	//fors�ger data 3 gange
    {
        cout << "csmaCA.cpp [sendData()]  -  sender Data |" << endl;
        sendSound(csmaCAframer.getFrame());						//sender framet data
        for (int time = 1; time <= timeToResend; time++)					//polling timer 700*10ms =  7sek
        {
            mySound3.delay(10);									//venter 10 ms
            if (ackFlag)									//hvis ack modtages
            {
                busy = false;									//signalere at maskinen er klar til ny forbindelse
                ackFlag = false;								//nulstiller "flag"
                return true;									//retunere true
            }

        }
        cout << "csmaCA.cpp [sendData()]  -  " << dataAttempts << ". sendData fejlet.." << endl;
    }
    //hvis ACK ikke modtages
    cout << endl << "csmaCA.cpp [sendData()]  -  ingen ACK er modtaget efter 3 * Data attempts... troede jeg havde faaet en ven.. )-; " << endl << endl;
    return false;
}

bool csmaCA::sendPakker(vector<vector<int> > Data)
{
    Sound mySound4;						//opretter sound objekt (til delay)
    if (!makeHandShake())				//retunere false hvis handshake fejler
        return false;
    int pakkeAntal = Data.size();			//gemmer størelsen af pakken, da den hele tiden bliver reduseret (.pop_back)
    for(int pakkeNr = 0; pakkeNr < pakkeAntal; pakkeNr++)	//køre alle pakker igennem
    {
        pakkeHolder = Data[0];			//gemmer øverste element fra Data vector
        Data.erase(Data.begin());					//sletter sidste element fra Data vector

        Frame csmaCAframer(pakkeHolder);	//Opretter frame objekt
     //   csmaCAframer.makeFrame();			//framer data


        bool pakkeSendtKorekt = false;								//siddes til true i polling loop hvis pakken er sendt korekt
        for (int dataAttempts = 1; dataAttempts <= sendAttempts; dataAttempts++)	//3 forsøg til at sende pakke korekt
        {
            //cout << "csmaCA.cpp [sendPakker()]  -  sender Pakke " << (pakkeNr + 1) << "/" << pakkeAntal << " |" << endl;
            sendSound(csmaCAframer.getFrame());						//sender framet data
            for (int time = 1; time <= timeToResend; time++)					//polling timer 700*10ms =  7sek
            {
                mySound4.delay(10);									//venter 10 ms
                if (ackFlag)										//hvis ack modtages
                {
                    busy = false;									//signalere at maskinen er klar til ny forbindelse
                    ackFlag = false;								//nulstiller ACK "flag"
                    pakkeSendtKorekt = true;						//indikere at pakke er sendt korekt
                    break;											//stopper ACK flag polling
                }

            }
            if(pakkeSendtKorekt)									//tjekker om pakke sendt korekt
                break;												//stopper gensendings loop
            //cout << "csmaCA.cpp [sendPakker()]  -  " << dataAttempts << ". send attempt brugt.." << endl;
        }
        if (!pakkeSendtKorekt)
        {
            //cout << "csmaCA.cpp [sendPakker()]  -  ingen ACK er modtaget efter 3 * pakke attempts... Fu*k julemanden.. " << endl;
            return false;
        }
        //cout << "csmaCA.cpp [sendPakker()]  -  pakke " << (pakkeNr+1) << " sendt korekt!" << endl;
    }
    return true;
}


bool csmaCA::makeHandShake()
{
    Sound mySound5;											//opretter soundobjekt (brugt til delay)

    for (int rtsAttempts = 1; rtsAttempts <= sendAttempts; rtsAttempts++)	//fors�ger RTS 3 gange
    {
        //cout << "csmaCA.cpp [makeHandShake]  -  sender RTS |" << endl;
        sendSound(RTS);						//sender framet Rts
        for (int time = 1; time <= timeToResend; time++)					//polling timer 700*10ms =  7sek
        {
            mySound5.delay(10);									//venter 10 ms
            if (ctsFlag)										//hvis CTS modtages
            {
                //cout << "csmaCA.cpp [makeHandShake]  -  ctsFlag er True" << endl;			//kan unkomenteres for debugging
                ctsFlag = false;								//nulstiller "flag"
                return true;									//retunere true
            }
            //cout << "csmaCA.cpp [makeHandShake]  -  ctsFlag er false" << endl;			//kan unkomenteres for debugging
        }
        //cout << "csmaCA.cpp [makeHandShake()] - " << rtsAttempts << ". RTS fejlet.." << endl;
    }
    //hvis CTS ikke modtages
    //cout << "csmaCA.cpp [makeHandShake()] -  ingen CTS er modtagfet efter 3 RTS... er jeg helt alene i verden? :/ " << endl;
    return false;												//retunere false
}



void csmaCA::sendSound(vector<int> d)
{
    txFlag = true;											//indikere at denne enhed sender (spiller lyd)

    //============== ini ====================
    unsigned int playSampleRate = 44100;        // play sample rate
    vector<sf::Int16> inputSamples;
    vector<int> frammedHex;
    Sound mySound1;                              //opretter mysound objekt
    mySound1.setSamplingRate(playSampleRate);    //sætter afspildnings sample rate

    TextHandler myTest;                         //opretter texthandler objekt
    Frame framming(ID);                         //Opretter frame objekt
    sf::SoundBuffer bufferInput;                //laver lydbuffer objekt
    sf::Sound sound1;                            //opretter sound objekt
    //=======================================
    framming.setData(d);                            //ligger hexbuffer ind i framing
    framming.makeFrame();                           //framer hexbuffer

    frammedHex = framming.getFrame();          		//gemmer framet data i "framedHex"

    //================ Udskriver framed data =========================
    //cout << "csmaCA.cpp [sendSound()]  -  Data played: ";			//
    /*for (int j = 0; j < frammedHex.size(); ++j)             		//udskriver frameHex til skermen
    {                                                       		//
        cout << frammedHex[j] << " ";                       		//
    }                                                       		//
    cout << endl;    */                                       		//
    //================================================================
    mySound1.setSamplePrTone(180);                           //
    mySound1.makeSound(frammedHex);                          //klargøre framed data "framedHex" til afspildning


    inputSamples = mySound1.getSound();    					//gemmer klargjordte samples i vektor "inputSamples"

    bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, playSampleRate);  //loadersamples ind i lydbuffer objekt

    sound1.setBuffer(bufferInput);                           //initalisere bufferInput i sound klasse

    mySound1.delay(100);

    sound1.play();                                           //afspiller bufferInput

    mySound1.delay(playTimeCal(frammedHex));    				//laver delay mens lyd spilelr
    txFlag = false;											//indikere at denne enhed ikke længere sender

}



void csmaCA::sendACK()
{
    sendSound(ACK);					//afspiller ACK
}


void csmaCA::sendCTS()
{
    sendSound(CTS);					//afspiller CTS
}


int csmaCA::playTimeCal(vector<int> enV)
{
    return enV.size()*soundPlayTime;					//retunere afspildningstid i ms
}



bool csmaCA::checkForRTS()
{
    Sound mySound2;										//opretter sound objekt (bruges til delay)

    if (rtsFlag)
    {
        Frame csmaCAframer(CTS);						//opretter framing objekt
        csmaCAframer.makeFrame();						//Frame CTS

        for (int DataTimeouts = 1; DataTimeouts <= sendAttempts; DataTimeouts++)	//venter paa data 3 gange
        {
            sendSound(csmaCAframer.getFrame());						//sender framet CTS
            for (int time = 1; time <= timeToResend; time++)					//polling timer 700*10ms =  7sek
            {
                mySound2.delay(10);									//venter 10 ms
                if (dataFlag)										//hvis data modtages
                {
                    dataFlag = false;								//nulstiller "flag"
                    return true;										//retunere true
                }

            }
            //cout << "csmaCA.cpp [checkForRTS()]  -  " << DataTimeouts << ". 3 timeout's for data" << endl;
        }

    }
    return false;
}


bool csmaCA::getTxFlag()
{
    return txFlag;
}


void csmaCA::setTest(int etT)				//[eksperimental]
{
    test = etT;
}


int csmaCA::getTest()					//[eksperimental]
{
    return test;
}

void csmaCA::setAckFlag()
{
    ackFlag = true;
}

void csmaCA::setCtsFlag()
{
    ctsFlag = true;
}

void csmaCA::setRtsFlag()
{
    rtsFlag = true;
}

void csmaCA::setDataFlag()
{
    dataFlag = true;
}


void csmaCA::setPstopFlag()
{
    pstopFlag = true;
}


void csmaCA::setBusy()
{
    busy = true;
}


void csmaCA::clearBusy()
{
    busy = false;
}


vector<int> csmaCA::getACKverdi()
{
    return ACK;
}


vector<int> csmaCA::getCTSverdi()
{
    return CTS;
}


vector<int> csmaCA::getRTSverdi()
{
    return RTS;
}


vector<int> csmaCA::getPSTOPverdi()
{
    return Pstop;
}


bool csmaCA::getAckFlagStatus()
{
    return ackFlag;
}


bool csmaCA::getCtsFlagStatus()
{
    return ctsFlag;
}


bool csmaCA::getRtsFlagStatus()
{
    return rtsFlag;
}


bool csmaCA::isBusy()
{
    return busy;
}


csmaCA::~csmaCA()
{
}
