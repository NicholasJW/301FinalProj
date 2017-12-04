#ifndef __ALU_H__
#define __ALU_H__
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
class ALU{
public:
	ALU();

	// void setInputs(int first, int second);
	void setInputs(string first, string second);

	// Two calculate methods, with or without control signals
	void calculate(string _control);
	void calculate();

	string inputs();
	string outputs();
	string getZeroValue(){return zeroValue;};
	string getResult(){return result;};
	string getControlSignal(){return control;};
private:
	string input1;
	string input2;
	long one;
    long two;
	string result;
	long calc;
	string control;
	string zeroValue;

};
#endif