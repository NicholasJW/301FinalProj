#ifndef __MUX_H__
#define __MUX_H__
#include <string>
#include <sstream>

using namespace std;

/* This class functions as a multiplexer by forwarding two input signals
 * into a single line
 */

class MUX{

struct input{
	// 0 for int, 1 for string
	int type = -1;
	
	int value = 0;
	string content = "N/A";
};

public:

	MUX(){};
	// testing
	// void setInput0(int _value);
	// void setInput1(int _value);

	// Sets the input values for the MUX
	void setInput0(string _content);
	void setInput1(string _content);

	// Computes MUX value based on the choice on int or string
	void compute(int choose);

	// testing
	// string getStringOutput();
	// int getIntOutput();

	// Two toString methods
	string inputs();
	string outputs();

private:
	input input0;
	input input1;

	// int outType = -1;
	// int outInt = -304;
	string output = "ERROR";
};

#endif