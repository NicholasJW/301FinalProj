#ifndef __PROCESSOR_H__
#define __PROCESSOR_H__

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream> 		// std::stringstream
#include <fstream>		// std::ofstream

#include "InstructionMem.h"
#include "DataMem.h"
#include "Registers.h"
// #include "FileWriter.h"

#include "ControlLine.h"
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

	ControlLine regDst;
	ControlLine jump;
	ControlLine memRead;
	ControlLine memtoReg;
	// This line has lengh 2
	ControlLine ALUOp;
	ControlLine memWrite;
	ControlLine ALUSrc;
	ControlLine regWrite;
	// This line is the 4-digit line from ALUControl to ALU, lenght 4.
	ControlLine ALUline;
	// This line is the zero line from ALU for branching
	ControlLine zeroLine;

	// To build the string to print or write to file
	stringstream ss;
	// open the output file if needed
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



	void initializeLines();

	// Write to file or cout
	void printOut(bool write_to_file, string output_file);

};
#endif