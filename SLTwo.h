#ifndef __SLTWO_H__
#define __SLTWO_H__
#include <string>

using namespace std;

/*	This class shifts the bits of a given number two to the left
 */

class SLTwo{
public:
	SLTwo(){};

	void setInput(string s){input = s;};
	// Shifts the number left by two
	void compute();

	string inputs(){return input;};
	string outputs(){return output;};

private:
	string input;
	string output;
};
#endif