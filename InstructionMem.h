#ifndef __INSTRUCTIONMEM_H__
#define __INSTRUCTIONMEM_H__
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

#include "ASMParser.h"

using namespace std;

/* This class will read in the Instruction Memory file and convert them into binary
 * line by line. All code are complete in lab 5, just take whatever we need.
 *
 */

class InstructionMem{

public:
	InstructionMem(){};

	InstructionMem(string program_input);

	int getSize(){return ins.size();};

	string getIns(string insAddress);

	string getInsMips(string insAddress);

	bool hasIns(string insAddress);

	string inputs();
	string outputs(){return currentOut;};

	// Function to print out the whole content of instruction memory
	string toString();

private:
	string currentIn;
	string currentOut;
	// Need a data structure here to strore all the address and instructions, not sure yet, 
	// Let's use HashMap
	// This is for binary
	map<string, string> ins;

	// This is for MIPS Ins
	map<string, string> insMips;

	void add(string insAddress, Instruction i);

};


#endif 