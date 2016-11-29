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
	Sound mySound;						//opretter sound objekt (til delay)
	if (!makeHandShake())				//retunere false hvis handshake fejler
		return false;
	Frame csmaCAframer(Data);			//Opretter frame objekt
	csmaCAframer.makeFrame();			//framer data

									//vent p� at et ack modtages
	for (int dataAttempts = 1; dataAttempts <= 3; dataAttempts++)	//fors�ger data 3 gange
	{
		sendSound(csmaCAframer.getFrame());						//sender framet data
		for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
		{
			mySound.delay(10);									//venter 10 ms
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



bool csmaCA::makeHandShake()
{
	Sound mySound;											//opretter soundobjekt (brugt til delay)
	int x = 1;												//bruges s� der kun sendes en "vente besked"
	while (busy)											//venter p� enheden ikke l�ngere har travlt
	{
		if (x == 1)											//s�rger for "vente" besked kun vises 1 gang i terminalen
		{
			cout << "csmaCA.cpp [makeHandShake()] -  enheden har travlt, besked lagt i ko" << endl; //vente besked
			x = 0;
		}
	}

										// vent p� at et svar modtages

	for (int rtsAttempts = 1; rtsAttempts <= 3; rtsAttempts++)	//fors�ger RTS 3 gange
	{
		sendSound(RTS);						//sender framet Rts
		for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
		{
			mySound.delay(10);									//venter 10 ms

			if (ctsFlag)										//hvis CTS modtages
			{
				ctsFlag = false;								//nulstiller "flag"
				return true;									//retunere true
			}

		}
		cout << "csmaCA.cpp [makeHandShake()] - " << rtsAttempts << ". RTS fejlet.." << endl;
	}
																//hvis CTS ikke modtages
	cout << endl << "csmaCA.cpp [makeHandShake()] -  ingen CTS er modtagfet efter 3 RTS... er jeg helt alene i verden? :/ " << endl << endl;
	return false;												//retunere false
}



void csmaCA::sendSound(vector<int> d)
{
	//============== ini ====================
	unsigned int playSampleRate = 44100;        // play sample rate
	vector<sf::Int16> inputSamples;
	vector<int> frammedHex;
	Sound mySound;                              //opretter mysound objekt
	mySound.setSamplingRate(playSampleRate);    //sætter afspildnings sample rate

	TextHandler myTest;                         //opretter texthandler objekt
	Frame framming(ID);                         //Opretter frame objekt
	sf::SoundBuffer bufferInput;                //laver lydboffer objekt
	sf::Sound sound;                            //opretter sound objekt
	//=======================================

	framming.setData(d);                            //ligger hexbuffer ind i framing
	framming.makeFrame();                           //framer hexbuffer

	frammedHex = framming.getFrame();          		//gemmer framet data i "framedHex"

	//================ Udskriver framed data =========================
	cout << endl << "csmaCA.cpp [sendSound()]  -  Data played: ";	//
	for (int j = 0; j < frammedHex.size(); ++j)             		//udskriver frameHex til skermen
	{                                                       		//
		cout << frammedHex[j] << " ";                       		//
	}                                                       		//
	cout << endl;                                           		//
	//================================================================

	mySound.makeSound(frammedHex);                          //klargøre framed data "framedHex" til afspildning

	inputSamples = mySound.getSound();    					//gemmer klargjordte samples i vektor "inputSamples"

	bufferInput.loadFromSamples(&inputSamples[0], inputSamples.size(), 1, playSampleRate);  //loadersamples ind i lydbuffer objekt

	sound.setBuffer(bufferInput);                           //initalisere bufferInput i sound klasse

	txFlag = true;											//indikere at denne enhed sender (spiller lyd)
	sound.play();                                           //afspiller bufferInput
	mySound.delay(playTimeCal(frammedHex));    				//laver delay mens lyd spilelr
	txFlag = false;											//indikere at denne enhed ikke længere sender

}



void csmaCA::sendACK()
{
	sendSound(ACK);										//afspiller framet ACK
}


void csmaCA::sendCTS()
{
	sendSound(CTS);										//afspiller CTS
}


int csmaCA::playTimeCal(vector<int> enV)
{
	return enV.size()*soundPlayTime;					//retunere afspildningstid i ms
}



bool csmaCA::checkForRTS()
{
	Sound mySound;										//opretter sound objekt (bruges til delay)

	if (rtsFlag)
	{
		Frame csmaCAframer(CTS);						//opretter framing objekt
		csmaCAframer.makeFrame();						//Frame CTS

		for (int DataTimeouts = 1; DataTimeouts <= 3; DataTimeouts++)	//venter paa data 3 gange
		{
			sendSound(csmaCAframer.getFrame());						//sender framet CTS
			for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
			{
				mySound.delay(10);									//venter 10 ms
				if (dataFlag)										//hvis data modtages
				{
					dataFlag = false;								//nulstiller "flag"
					return true;										//retunere true
				}

			}
			cout << "csmaCA.cpp [checkForRTS()]  -  " << DataTimeouts << ". 3 timeout's for data" << endl;
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


csmaCA::~csmaCA()
{
}
