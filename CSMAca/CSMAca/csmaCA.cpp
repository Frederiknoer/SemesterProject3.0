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
		cout << "Fejl! - intastede ID overskrider maximum længde på 2 x 4bits" << endl;
	else
		ID = newID;

}

csmaCA::csmaCA(vector<int> newID, vector<int> TagetID)
{
	if (newID.size() > 2)
		cout << "Fejl! - intastede (ID) overskrider maximum længde på 2 x 4bits" << endl;
	else
		ID = newID;

	if (TagetID.size() > 2)
		cout << "Fejl! - intastede (Taget ID) overskrider maximum længde på 2 x 4bits" << endl;
	else
		tagetID = TagetID;

}

void csmaCA::setTagetID(vector<int> tID)
{
	if (tID.size() > 2)
		cout << "Fejl! - intastede ID overskrider maximum længde på 2 x 4bits" << endl;
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
		cout << "Fejl! - intastede ID overskrider maximum længde på 2 x 4bits" << endl;
	else
		ID = newID;
}

vector<int> csmaCA::getID()
{
	return ID;
}

bool csmaCA::sendData(vector<int> Data)
{
	if (!makeHandShake())				//retunere false hvis handshake fejler
		return false;
	Frame csmaCAframer(Data);			//Opretter frame objekt
	csmaCAframer.makeFrame();			//framer data

	bool ackModtaget = false;		//hvis "ACT" modtages siddes denne variabel til "true"

									//vent på at et ack modtages
	for (int dataAttempts = 1; dataAttempts <= 3; dataAttempts++)	//forsøger data 3 gange
	{
		//stop recorder
		sendSound(csmaCAframer.getFrame());						//sender framet data
		Sleep(playTimeCal(csmaCAframer.getFrame()));				//udregner og udføre delay
		//start recorder
		for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
		{
			Sleep(10);											//venter 10 ms
			if (ackModtaget)									//hvis ack modtages
			{
				busy = false;									//signalere at maskinen er klar til ny forbindelse
				ackModtaget = false;							//nulstiller "flag"
				return true;									//retunere true
			}

		}
		cout << "csmaCA.cpp [sendData()] - " << dataAttempts << ". sendData fejlet.." << endl;
	}
	//hvis ACK ikke modtages
	cout << endl << "csmaCA.cpp [sendData()] -  ingen ACK er modtaget efter 3 * Data attempts... troede jeg havde fået en ven.. )-; " << endl << endl;
	return false;
}

bool csmaCA::makeHandShake()
{
	int x = 1;												//bruges så der kun sendes en "vente besked"
	while (busy)											//venter på enheden ikke længere har travlt
	{
		if (x == 1)											//sørger for "vente" besked kun vises 1 gang i terminalen
		{
			cout << "csmaCA.cpp [makeHandShake()] -  enheden har travlt, besked lagt i kø" << endl; //vente besked
			x = 0;
		}
	}
	Frame csmaCAframer(RTS);			//Opretter frame objekt
	csmaCAframer.makeFrame();			//Frame RTS

									// vent på at et svar modtages
	bool ctsModtaget = true;		//hvis "CTS" modtages siddes denne variabel til "true"

	for (int rtsAttempts = 1; rtsAttempts <= 3; rtsAttempts++)	//forsøger RTS 3 gange
	{
		sendSound(csmaCAframer.getFrame());						//sender framet Rts
		for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
		{
			Sleep(10);											//venter 10 ms
			if (ctsModtaget)									//hvis CTS modtages
			{
				ctsModtaget = false;							//nulstiller "flag"
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
	cout << endl << "=========== LYD Start ===========" << endl;
	for (int i = 0; i < d.size(); i++)
	{
		cout << d[i] << " ";
	}
	cout << endl << "=========== LYD Slut ============" << endl << endl;
}

void csmaCA::sendACK()
{
	Frame csmaCAframer(ACK);						//Opretter frame objekt
	csmaCAframer.makeFrame();						//Frame ACK
	//stop recorder
	sendSound(csmaCAframer.getFrame());				//afspiller framet ACK
	Sleep(playTimeCal(csmaCAframer.getFrame()));	//udregner og udføre delay
	//start recorder
}

int csmaCA::playTimeCal(vector<int> enV)
{
	return enV.size()*soundPlayTime;				//retunere afspildningstid i ms
}

bool csmaCA::checkForRTS()
{
	bool rtsModtaget = true;						//hvis "RTS" modtages siddes denne variabel til "true"
	bool dataModtaget = true;						//hvis "data" modtages siddes denne variabel til "true"

	if (rtsModtaget)
	{
		Frame csmaCAframer(CTS);						//opretter framing objekt
		csmaCAframer.makeFrame();						//Frame CTS
		


		for (int DataTimeouts = 1; DataTimeouts <= 3; DataTimeouts++)	//venter på data 3 gange
		{

			//stop recorder
			sendSound(csmaCAframer.getFrame());						//sender framet CTS
			Sleep(playTimeCal(csmaCAframer.getFrame()));			//udregner og udføre delay
			//start recorder
			for (int time = 1; time <= 700; time++)					//polling timer 700*10ms =  7sek
			{
				Sleep(10);											//venter 10 ms
				if (dataModtaget)									//hvis data modtages
				{
					dataModtaget = false;							//nulstiller "flag"
					return true;									//retunere true
				}

			}
			cout << "csmaCA.cpp [checkForRTS()] - " << DataTimeouts << ". 3 timeout's for data" << endl;
		}

	}
	return false;
}

csmaCA::~csmaCA()
{
}
