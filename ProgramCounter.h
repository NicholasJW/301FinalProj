#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__
#include <string>
#include <sstream>

using namespace std;

class ProgramCounter{
public:

	ProgramCounter();

	int getCurrentAddress(){return cr;};

	void setCurrentAddress(int _cr){cr = _cr;};

	string inputs();

	string outputs();

private:

	std::stringstream toHex;
	int cr;

};
#endif