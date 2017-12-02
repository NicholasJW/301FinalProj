#ifndef __MAINCONTROL_H__
#define __MAINCONTROL_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MainControl{
public:

	MainControl(){signals.resize(9);};

	void setOpcode(string _opcode);

	vector<string> getControlSignals(){return signals;};

	string inputs(){return opcode;};

private:

	string opcode;
	vector<string> signals;

};
#endif