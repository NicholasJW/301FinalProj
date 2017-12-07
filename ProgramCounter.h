#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__
#include <string>
// #include <sstream>

using namespace std;

// This class sets the program counter for the processor

class ProgramCounter{
public:

	ProgramCounter();

	string getCurrentAddress(){return cr;};

	void setCurrentAddress(string _cr){cr = _cr;};

	string inputs();

	string outputs();

private:

	// std::stringstream toHex;
	string cr;

};
#endif