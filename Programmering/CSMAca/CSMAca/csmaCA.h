#include "../../Frame/Frame/Frame.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>			//random gen
#include <ctime>			//random gen
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
    bool sendData(vector<int> data);				//	done!	(enkelt data vektor)retunere true hvis data sendt og ACK modtaget
    bool sendPakker(vector <vector<int> > data);	//			(2D data vektor)retunere true hvis alle pakker bliver sendt korekt
    bool makeHandShake();							//	done!	sender RTS og retunere true n�r cts modtages
    void sendACK();									//	done! 	sender ACK
    void sendCTS();									//			sender CTS
    int playTimeCal(vector<int> enV);				//	done!	beregner afspildnings (at lave til lyd) tid for vector [ms]
    bool checkForRTS();								//	done!	tjekker om et "RTS" er modtager
    bool getTxFlag();								//	done!	retunere tur hvis denne pc afspiller lyd (sender)
    void setRtsFlag();								//	done!	sidder rtsFlag til true
    void setCtsFlag();								//	done!	sidder ctsFlag til true
    void setAckFlag();								//	done!	sidder ackFlag til true
    void setDataFlag();								//	done!	siddes dataFlag til true
    void setPstopFlag();							//			sidder PstopFlag til true
    void setBusy();									//			sidder busy til true
    void clearBusy();								//			sidder busy til false
    bool getAckFlagStatus();                        //          retunere værdi af ACK flag
    bool getCtsFlagStatus();                        //          retunere værdi af CTS flag
    bool getRtsFlagStatus();                        //          retunere værdi af RTS flag
    bool isBusy();									//			retunere værdien af busy
    int getTest();									//			[eksperimental]	retunere værdi af variablen test
    void setTest(int etT);							//			[eksperimental]	ændre værdien af variablen tur
    vector<int> getACKverdi();                      //  done!   retunere ACK værdi (ikke status!)
    vector<int> getCTSverdi();                      //  done!   retunere CTS værdi (ikke status!)
    vector<int> getRTSverdi();                      //  done!   retunere RTS værdi (ikke status!)
    vector<int> getPSTOPverdi();                    // 			retunere RTS værdi (ikke status!)

    ~csmaCA();
private:
    void sendSound(vector<int>);					//	done!	indenholder bla. alex's lyd
    vector<int> tagetID = { 0 };					//Modtagerns bruger ID
    vector<int> ID = { 0 };							//Denne pc's bruger ID
    vector<int> RTS = { 1, 4, 1, 4 };		        //difinere RTS
    vector<int> CTS = { 1, 7, 1, 7 };		        //difinere CTS
    vector<int> ACK = { 1, 10, 1, 10 };		        //difinere ACK
    vector<int> NACK = { 1, 13, 1, 13 };		//difinere NACK
    vector<int> Pstop = { 1, 15, 1, 15 };				//difinere pakke stop væri
    vector<int> bufferTextIn;						//Buffer til data fra frede
    vector<int> bFramedData;						//Buffer hvor framet data gennes
    vector<int> pakkeHolder;						//holder pakken midlertidigt, imens elementet bliver poppet
    int soundPlayTime = 44;							//tiden hver inudviduelle lyde afspilles i ms
    bool busy = false;								//signalere om enheden komunikere med anden enhed
    bool ini = false;								//siddes true hvis initalisering har fundet sted
    bool playing = false;							//siddes true hvis denne pc afspiller lyd
    unsigned int recordSampleRate = 96000;      	//sample rate for recorder
    bool ackFlag = false;							//flag sætte til true hvsi er modtaget
    bool ctsFlag = false;							//flag sætte til true hvsi er modtaget
    bool rtsFlag = false;							//flag sætte til true hvsi er modtaget
    bool dataFlag = false;							//flag sættes til true hvis data er modtaget
    bool pstopFlag = false;							//flag sætte til true hvis "pakke stop" modtages
    bool txFlag = false;							//flag sættes til true hvis denne enhed afspiller lyd (transmitere)
    int test = 0;									//[eksperimental]
    int timeToResend = 100;
};


