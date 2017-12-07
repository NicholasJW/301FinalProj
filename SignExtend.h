#ifndef __SIGNEXTEND_H__
#define __SIGNEXTEND_H__
#include <string>
// #include <iostream>

using namespace std;

/*	This class extends the number of bits in a binary number while preserving the
 *  number's positive/negative sign and value
 */

class SignExtend{
public:
	SignExtend(){};

	// Sets the input given a string of binary numbers
	void setInput(string s);

	// Computes the sign extension of the given input
	void compute();

	string inputs(){return input;};
	string outputs(){return output;};

private:
	string input;
	string output;

};
#endif