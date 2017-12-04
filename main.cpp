#include <iostream>
#include "FileReader.h"
#include "InstructionMem.h"
#include "DataMem.h"
#include "Registers.h"
#include "Processor.h"

// TODO : Keep adding header file connecting with the first layer.

using namespace std;

/*  This program runs by creating FileReader to read in the config file and 
 *  constructing a processor and run it.
 */
int main(int argc, char *argv[]){

	// Debugging makefile
	// cout << "Makefile works fine!" << endl;

	FileReader *fr = new FileReader("sample_inputs/config.cfg");

	cout << "Instruction Mem Start.\n";
	InstructionMem imem(fr->getInstMem());
	cout << "Instruction Mem Done.\n";

	cout << "Data Mem Start.\n";
	DataMem dmem(fr->getDataMem());
	cout << "Data Mem Done.\n";

	cout << "Registers Start.\n";
	Registers regs(fr->getRegFile());
	cout << "Registers Done.\n";
	// Debugging
	// cout << imem.toString() << dmem.toString() << regs.toString();
	
	cout << "Processor Setup Start.\n";
	Processor p(imem, dmem, regs, fr->getOutMode(), fr->getDebugMode(), fr->getPrintMem(), fr->writeToFile(), fr->getOutFile());
	cout << "Processor Setup Done.\n";

	p.run();


	delete fr;
	return 0;
}