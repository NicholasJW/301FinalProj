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
 * line by line.
 */

class InstructionMem{

public:
	InstructionMem(){};

	// Contructor that build a Instruction memory out of an assembly file
	InstructionMem(string program_input);

	// Get the size of the Instruction Memory with an int
	int getSize(){return ins.size();};

	// Get the binary instruction 
	string getIns(string insAddress);

	// Get the instruction in assembly language
	string getInsMips(string insAddress);

	// Check if there is an instruction at this address
	bool hasIns(string insAddress);

	// This function returns the string representing the inputs of Instruction Memory
	string inputs();
	// This function returns the string representing the outputs of Instruction Memory
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

	// Helper function that adds an instruction to the corresponding address
	void add(string insAddress, Instruction i);

};


#endif 