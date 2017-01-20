#include "Frame.h"

Frame::Frame()
{
}
Frame::Frame(vector<int> d)
{
	data = d;
}
void Frame::makeFrame()
{
	//Hvis data ligner et flag, inds�ttes en plads med 0 imellem dem. 
	for (int i = 0;i < getLength()-1;i++)
	{
		if (getElement(i) == 0b0111)
		{
			data.insert(data.begin() + i + 1, 3);
		}
	}
	// Redundante bits tilf�jes, med generatiopolynomiet 10001001:
	unsigned long sum = 0;						// Variabel til summen af alle pladser p� vektortabellen
	int checkSum = 0;	
	bitset<8> checkSumBit = 0;					//F�lgende udregner tjeksummen og deler den op i nipples p� en noget besv�rlig m�de 
	bitset<4> checkSumHN = 0;					 
	bitset<4> checkSumLN = 0;
	int checkSumLNint = 0;
	int checkSumHNint = 0;
	for (int i = 0;i < getLength();i++)
	{
		sum = sum + data[i];
	}
	checkSum = sum % 0b10001001;				//Tjek-summen bestemmes ved at heltalsdividere med generatorpolynomiet og resten er den tjeksummen.
	checkSumBit = checkSum;
	checkSumLN[0] = checkSumBit[0];
	checkSumLN[1] = checkSumBit[1];
	checkSumLN[2] = checkSumBit[2];
	checkSumLN[3] = checkSumBit[3];
	checkSumHN[0] = checkSumBit[4];
	checkSumHN[1] = checkSumBit[5];
	checkSumHN[2] = checkSumBit[6];
	checkSumHN[3] = checkSumBit[7];
	checkSumHNint = (int)(checkSumHN.to_ulong());
	checkSumLNint = (int)(checkSumLN.to_ulong());
	data.push_back(checkSumHNint);
	data.push_back(checkSumLNint);
	//Startflaget inds�ttes:
	data.insert(data.begin(), 0b1110);			
	data.insert(data.begin(), 0b0111);
	//Slutflaget inds�ttes:
	data.push_back(0b0111);
	data.push_back(0b1110);
	return;
}
bool Frame::validataFrame()
{
	//F�rst kontrolleres start- og slut-flaget 
	if (data[0] != 0b0111 && data[1] != 0b1110 && data[data.size() - 2] != 0b0111 && data[data.size() - 1] != 0b1110)
		return false;
	//Herefter l�gges selve dataen sammen for at validere dataen med generatorpolynomiet.
	unsigned long sum = 0;
	int checkSum = (data[data.size() - 3] | (data[data.size() - 4] << 4));
	for (int i = 2;i < getLength()-4;i++)
	{
		sum = sum + data[i];
	}
	if ((sum - checkSum) % 0b10001001 != 0) // Hvis dataen ar valid, skal summen minus tjeksummen v�re dividerbart med generatorpolynomiet.
		return false;
	return true;




}
void Frame::unFrame()
{
	//Hvis framet er valid, kan flagene og tjeksummen fjernes:
	data.erase(data.begin());
	data.erase(data.begin());
	data.pop_back();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	// Hvis der blev tilf�jet en plads med v�rdien 0, for at data ikke kunne forst�s som et flag, fjernes det igen:
	for (int i = 0;i < getLength() - 2;i++)
	{
		if (getElement(i) == 0b0111)
		{
			data.erase(data.begin() + i + 1);
		}
	}

}
vector<int> Frame::getFrame()
{
	return data;
}
int Frame::getFirst()
{
	return data.front();
}
int Frame::getElement(int element)
{
	return data[element];
}
int Frame::getLength()
{
	return data.size();
}
void Frame::setData(vector<int> d)
{
	data = d;
}
Frame::~Frame()
{
}
