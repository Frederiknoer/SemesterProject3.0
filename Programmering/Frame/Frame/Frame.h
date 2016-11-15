#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

class Frame
{
public:
	Frame();
	Frame(vector<int>); // Atributten "data" bliver defineret som en vektortabel. 
	void makeFrame(); // Start-/stop-bit og tjek-summen bliver tilf�jet.
	bool validataFrame(); //Validerer en modtaget frame.
	void unFrame(); // Fjerner start-/stop-bit og tjek-summen.
	Frame getFrame(); // Retunerer vektortabellen "data"
	int getFirst(); // Retunerer det f�rste element i vektortabellem.
	int getElement(int); // Retunerer elementet p� parameterets plads. 
	int getLength(); // Retunerer l�ngden af vektortabellen 
	~Frame();
private:
	vector<int> data; 
};

