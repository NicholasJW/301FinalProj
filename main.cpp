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
	InstructionMem imem(fr->getInstMem());
	DataMem dmem(fr->getDataMem());
	Registers regs(fr->getRegFile());
	// Debugging
	cout << imem.toString() << dmem.toString() << regs.toString();
	Processor p(imem, dmem, regs);
	// p.run(true, true, true, true, "hahahah");

	delete fr;
	return 0;
}