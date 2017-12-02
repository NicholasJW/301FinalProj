#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__
#include <string>
// #include <iostream>

using namespace std;
class SignExtend{
public:
	SignExtend(){};
	void setInput(string s);
	void compute();

	string inputs(){return input;};
	string outputs(){return output;};

private:
	string input;
	string output;

};
#endif