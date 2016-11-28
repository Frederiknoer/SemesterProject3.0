#pragma once
#include <iostream>
#include <string>

using namespace std;

class csmaCA
{
public:
	csmaCA();						//Sidder ID til en af de 5 "default ID's"
	csmaCA(int ID);
	csmaCA(int ID, int TagetID);

	void setTagetID(int tID);
	int getTagetID();
	void setID(int newID);
	int getID();
	void sendData(int data);
	void checkData(int modtagedeData)

	~csmaCA();
private:
	int tagetID = 0;
	int ID = 0;

	int RTS = 0xff32;
	int CTS = 0xb86a;
	int ack = 0x114c;
	int nack = 0x4811;
};


