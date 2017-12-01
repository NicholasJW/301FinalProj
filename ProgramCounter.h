#ifndef __PROGRAMCOUNTER_H__
#define __PROGRAMCOUNTER_H__
#include <string>

using namespace std;

class ProgramCounter{
public:

	ProgramCounter();

	int getCurrentAddress(){return cr;};

	void setCurrentAddress(int _cr){cr = _cr;};

private:

	int cr;

};
#endif