#ifndef __ALU_H__
#define __ALU_H__
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
class ALU{
public:
	ALU();

	void setInputs(int first, int second);

	// Two calculate methods, with or without control signals
	void calculate(string _control);
	void calculate();

	string inputs();
	string outputs();
	string getZeroValue(){return zeroValue;};
	int getResult(){return result;};
	string getControlSignal(){return control;};
private:
	int input1;
	int input2;
	int result;
	string control;
	string zeroValue;

};
#endif