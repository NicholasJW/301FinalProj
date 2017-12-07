#ifndef __ALU_H__
#define __ALU_H__
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

/* This class functions as the Arithmetic Logic Unit by performing arithmetic and
 * logical operations based on a given hex input value and outputs the result of the
 * operation performed.
 */

class ALU{
public:
	// Set-up ALU with default values of hex 0
	ALU();

	// void setInputs(int first, int second);

	// Sets string values as inputs for ALU
	void setInputs(string first, string second);

	// Two calculate methods, with or without control signals
	void calculate(string _control);
	void calculate();

	// Returns the input values to the ALU in hexadecimal
	string inputs();
	// Returns the output values to the ALU in hexadecimal
	string outputs();

	// Getter methods
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