#include "csmaCA.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<int> ID = { 14, 15 };
	vector<int> tagetID = { 10, 12 };
	vector<int> payload = { 14, 15 };

	csmaCA csmaHandler(ID, tagetID);

	csmaHandler.sendACK();

	/*if (csmaHandler.checkForRTS())
		cout << "RTS modtaget" << endl;
	else
		cout << "RTS ikke modtaget" << endl;*/


	system("pause");
	return 0;
}