#ifndef __ALUCONTROL_H__
#define __ALUCONTROL_H__
#include <string>
// #include <iostream>
#include <sstream>

using namespace std;
class ALUControl{
public:
	ALUControl(){};

	void setControl(string op1, string op2);
	void compute();
	void setFuncCode(string f){funcCode = f;};
	string inputs();
	string outputs();

private:
// All strings with 0x except func code
	string funcCode;
	string control;
	string output = "0xe";

};
#endif