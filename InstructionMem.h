#ifndef __INSTRUCTIONMEM_H__
#define __INSTRUCTIONMEM_H__
#include <string>

// TODO include files such as ASMParser and Instruction, details are in lab 5.
using namespace std;


/* This class will read in the Instruction Memory file and convert them into binary
 * line by line. All code are complete in lab 5, just take whatever we need.
 *
 */

class InstructionMem{
public:
	InstructionMem();

	InstructionMem(string fileName);

private:
	// Need a data structure here to strore all the address and instructions, not sure yet, 
	// but HashTable?
};


#endif 