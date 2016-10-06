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
	Frame(vector<int>);
	void makeFrame();
	bool validataFrame();
	void unFrame();
	Frame getFrame();
	int getFirst();
	int getElement(int);
	int getLength();
	~Frame();
private:
	vector<int> data;
};

