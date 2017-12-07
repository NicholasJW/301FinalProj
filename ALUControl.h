#ifndef __ALUCONTROL_H__
#define __ALUCONTROL_H__
#include <string>
// #include <iostream>
#include <sstream>

using namespace std;

/* This class computes the output signal of the ALU based on either a control signal
 * or a function code and returns the values for ALUOp1, ALUOp2, and the function code
 */

class ALUControl{
public:
	ALUControl(){};

	// Set up ALU Control
	void setControl(string op1, string op2);

	// Compute output signal based on the control signal (I-type) or function code (R-Type)
	void compute();

	// Sets function code based on given string of numbers
	void setFuncCode(string f){funcCode = f;};

	// Returns values for ALUOp1, ALUOp2, and the function code
	string inputs();
	// Returns output
	string outputs();

private:
// All strings with 0x except func code
	string funcCode;
	string control;
	string output = "0xe";

};
#endif