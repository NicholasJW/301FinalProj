#ifndef __MAINCONTROL_H__
#define __MAINCONTROL_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* This class is the main control unit, which takes a 6-bit opcode as input an
 * output 9 control signals each of which is represented as a string.
 */

class MainControl{
public:
	// Sets up control signal vector
	MainControl();

	// Given an opcode input, sets 9 control signals (in hex) as strings
	void setOpcode(string _opcode);

	// This function also used as outputs().
	vector<string> getControlSignals(){return signals;};

	string inputs(){return opcode;};

private:
	// Opcode to be used as input
	string opcode;

	// This is the output which is a string vector having length 9.
	vector<string> signals;

};
#endif