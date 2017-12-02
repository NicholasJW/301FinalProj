#ifndef __MUX_H__
#define __MUX_H__
#include <string>
#include <sstream>

using namespace std;
class MUX{

struct input{
	// 0 for int, 1 for string
	int type = -1;
	
	int value = 0;
	string content = "N/A";
};

public:

	MUX(){};
	void setInput0(int _value);
	void setInput1(int _value);
	void setInput0(string _content);
	void setInput1(string _content);
	void compute(int choose);
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
	string output = "FLORA";
};

#endif