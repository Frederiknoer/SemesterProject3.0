#include "../../Frame/Frame/Frame.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>			//random gen
#include <ctime>			//random gen
#include <windows.h>		//delay "makeHandShake()"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../../Sound/sound.h"
#include "../../TextHandler/TextHandler.h"
//#include "../../CustomRecorder/CustomRecorder.h"
#pragma once
using namespace std;
class csmaCA


{
public:
	csmaCA();										//	done!	Sidder ID til en af de 5 "default ID's"
	csmaCA(vector<int> ID);							//	done!	sideer �D til ID
	csmaCA(vector<int> ID, vector<int> TagetID);	//	done!	sidder ID og taget ID

	void setTagetID(vector<int> tID);				//	done!
	vector<int> getTagetID();						//	done!
	void setID(vector<int> newID);					//	done!
	vector<int> getID();							//	done!
	bool sendData(vector<int> data);				//	done!	retunere true hvis data sendt og ACK modtaget
	bool makeHandShake();							//	done!	sender RTS og retunere true n�r cts modtages
	void sendACK();									//	done! 	sender ACK
	void sendCTS();									//			sender CTS
	int playTimeCal(vector<int> enV);				//	done!	beregner afspildnings (at lave til lyd) tid for vector [ms]
	bool checkForRTS();								//	done!	tjekker om et "RTS" er modtager
	bool getTxFlag();								//	done!	retunere tur hvis denne pc afspiller lyd (sender)
	void setRtsFlag();								//			sidder rtsFlag til true
	void setCtsFlag();								//			sidder ctsFlag til true
	void setAckFlag();								//			sidder ackFlag til true
	void setDataFlag();								//			siddes dataFlag til true
	int getTest();									//			[eksperimental]	retunere værdi af variablen test
	void setTest(int etT);							//			[eksperimental]	ændre værdien af variablen tur

	~csmaCA();
private:
	void sendSound(vector<int>);					//	done!	indenholder bla. alex's lyd
	vector<int> tagetID = { 0 };					//Modtagerns bruger ID
	vector<int> ID = { 0 };							//Denne pc's bruger ID
	vector<int> RTS = { 0xf, 0xf, 0x3, 0x2 };		//difinere RTS
	vector<int> CTS = { 0xb, 0x8, 0x6, 0xa };		//difinere CTS
	vector<int> ACK = { 0x1, 0x1, 0x4, 0xc };		//difinere ACK
	vector<int> NACK = { 0x4, 0x8, 0x1, 0x1 };		//difinere NACK
	vector<int> bufferTextIn;						//Buffer til data fra frede
	vector<int> bFramedData;						//Buffer hvor framet data gennes
	int dataAttempts = 0;							//antal DATA fors�gt
	int nackAttempt = 0;							//antal NAC fors�gt
	int soundPlayTime = 30;							//tiden hver inudviduelle lyde afspilles i ms
	bool busy = false;								//signalere om enheden komunikere med anden enhed
	bool ini = false;								//siddes true hvis initalisering har fundet sted
	bool playing = false;							//siddes true hvis denne pc afspiller lyd
	unsigned int recordSampleRate = 96000;      	//sample rate for recorder
	bool ackFlag = false;							//flag sætte til true hvsi er modtaget
	bool ctsFlag = false;							//flag sætte til true hvsi er modtaget
	bool rtsFlag = false;							//flag sætte til true hvsi er modtaget
	bool dataFlag = false;							//flag sættes til true hvis data er modtaget
	bool txFlag = false;							//flag sættes til true hvis denne enhed afspiller lyd (transmitere)
	int test = 0;									//[eksperimental]
};


