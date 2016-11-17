#pragma once
#include "Frame.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>			//random gen
#include <ctime>			//random gen
#include <windows.h>		//delay "makeHandShake()"

using namespace std;
class csmaCA
{
public:
	csmaCA();										//	done!	Sidder ID til en af de 5 "default ID's"
	csmaCA(vector<int> ID);							//	done!	sideer ÍD til ID
	csmaCA(vector<int> ID, vector<int> TagetID);	//	done!	sidder ID og taget ID

	void setTagetID(vector<int> tID);				//	done!
	vector<int> getTagetID();						//	done!
	void setID(vector<int> newID);					//	done!
	vector<int> getID();							//	done!
	bool sendData(vector<int> data);				//	done!	retunere true hvis data sendt og ACK modtaget
	void sendSound(vector<int>);					//	done!	skal erstattes af alex's lyd klasse
	bool makeHandShake();							//	done!	sender RTS og retunere true når cts modtages
	void sendACK();									//	done! 	sender NACK
	int playTimeCal(vector<int> enV);				//	done!	beregner afspildnings (at lave til lyd) tid for vector [ms]
	bool checkForRTS();								//	done!	tjekker om et "RTS" er modtager

	~csmaCA();
private:
	vector<int> tagetID = { 0 };					//Modtagerns bruger ID
	vector<int> ID = { 0 };							//Denne pc's bruger ID
	vector<int> RTS = { 0xf, 0xf, 0x3, 0x2 };		//difinere RTS
	vector<int> CTS = { 0xb, 0x8, 0x6, 0xa };		//difinere CTS
	vector<int> ACK = { 0x1, 0x1, 0x4, 0xc };		//difinere ACK
	vector<int> NACK = { 0x4, 0x8, 0x1, 0x1 };		//difinere NACK
	vector<int> bufferTextIn;						//Buffer til data fra frede
	vector<int> bFramedData;						//Buffer hvor framet data gennes
	int dataAttempts = 0;							//antal DATA forsøgt
	int nackAttempt = 0;							//antal NAC forsøgt
	int soundPlayTime = 100;						//tiden hver inudviduelle lyde afspilles i ms
	bool busy = false;								//signalere om enheden komunikere med anden enhed
};


