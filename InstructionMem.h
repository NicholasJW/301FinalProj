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

	string getIns(int insAddress);

	string getInsMips(int insAddress);

	bool hasIns(int insAddress);

	string inputs();
	string outputs(){return currentOut;};

	// Function to print out the whole content of instruction memory
	string toString();

private:
	int currentIn;
	string currentOut;
	// Need a data structure here to strore all the address and instructions, not sure yet, 
	// Let's use HashMap
	// This is for binary
	map<int, string> ins;

	// This is for MIPS Ins
	map<int, string> insMips;

	void add(int insAddress, Instruction i);

};


#endif 