#ifndef __ALU_H__
#define __ALU_H__
#include <string>
#include <sstream>

using namespace std;
class ALU{
public:
	ALU();

	void setInputs(int first, int second);

	// Two calculate methods, with or without control signals
	void calculate(string control);
	void calculate();

	string inputs();
	string outputs();

private:
	int input1;
	int input2;
	int result;

};
#endif