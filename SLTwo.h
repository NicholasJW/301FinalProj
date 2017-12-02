#ifndef __SLTWO_H__
#define __SLTWO_H__
#include <string>

using namespace std;
class SLTwo{
public:
	SLTwo(){};

	void setInput(string s){input = s;};
	void compute();
	string inputs(){return input;};
	string outputs(){return output;};

private:
	string input;
	string output;
};
#endif