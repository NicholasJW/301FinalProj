#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include "InstructionMem.h"
#include "DataMem.h"
#include "Registers.h"
#include "FileWriter.h"

#include "ProgramCounter.h"
#include "ALU.h"
#include "MUX.h"
#include "SLTwo.h"
#include "MainControl.h"
#include "ALUControl.h"
#include "SignExtend.h"
// TODO include more classes/hearders files

using namespace std;
class Processor{
public:
	Processor(InstructionMem iMem, DataMem dMem, Registers registers);

	// The method to run the object by knowing the information in the prantecies.
	void run(bool is_single_step, bool is_debug, bool print_memory, bool write_to_file);
private:
	// I/o and memmory
	InstructionMem iMem;
	DataMem dMem;
	Registers registers;
	FileWriter fileWriter;

	// functional units
	ProgramCounter pc;
	ALU alu1; //Has only add
	ALU alu2; //Has add and alu result
	ALU alu3; //Has alu result and alu 
	MUX mux1; //Mux for the third register
	MUX mux2; //Mux for the second input of the alu3
	MUX mux3; //Mux after DataMem
	MUX mux4; //top right
	MUX mux5; //top left
	SLTwo slt1; //top
	SLTwo slt2; //middle
	MainControl mc;
	ALUControl ac;
	SignExtend se;

};
#endif