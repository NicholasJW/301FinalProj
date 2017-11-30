#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream> 		// std::stringstream
#include <fstream>		// std::ofstream

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
	Processor(InstructionMem _iMem, DataMem _dMem, Registers _registers);

	// The method to run the object by knowing the information in the prantecies.
	void run(bool is_single_step, bool is_debug, bool print_memory, bool write_to_file);

private:
	// I/o and memmory
	InstructionMem imem;
	DataMem dmem;
	Registers regs;
	// Think about this, do we really need a file writer?
	// FileWriter fileWriter;

	stringstream ss;
	ofstream ofs;
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

	void printOut(bool write_to_file, string output_file);

};
#endif