#include <iostream>
#include "FileReader.h"
#include "InstructionMem.h"
#include "DataMem.h"
#include "Registers.h"
#include "Processor.h"

using namespace std;

/*  This program runs by creating FileReader to read in the config file and 
 *  constructing a processor and run it.
 */

int main(int argc, char *argv[]){

	// Debugging makefile
	// cout << "Makefile works fine!" << endl;
	if(argc < 2){
		cerr << "PLease specify the config file." << endl;
		exit(1);
	}

	// Build the File Reader to read the config file
	FileReader *fr = new FileReader(argv[1]);
	if (fr->getDebugMode()){
		cout << "Instruction Mem Start.\n";
	}

	// Build the Instruction Memory
	InstructionMem imem(fr->getInstMem());
	if (fr->getDebugMode()){
		cout << "Instruction Mem Done.\n";
	}

	// Build the Data Mem
	if (fr->getDebugMode()){
		cout << "Data Mem Start.\n";
	}

	DataMem dmem(fr->getDataMem());
	if (fr->getDebugMode()){
		cout << "Data Mem Done.\n";
	}

	// Build Registers
	if (fr->getDebugMode()){
		cout << "Registers Start.\n";
	}

	Registers regs(fr->getRegFile());
	if (fr->getDebugMode()){
		cout << "Registers Done.\n";
	}

	// Debugging
	// cout << imem.toString() << dmem.toString() << regs.toString();

	// Build Processor
	if (fr->getDebugMode()){
		cout << "Processor Setup start\n";
	}
	Processor p(imem, dmem, regs, fr->getOutMode(), fr->getDebugMode(), fr->getPrintMem(), fr->writeToFile(), fr->getOutFile());
	
	if (fr->getDebugMode()){
		cout << "Processor Setup Done\n";
		cout << "All files check out, ready to run\n\n";
	}
	// Actually run the Processer
	p.run();


	delete fr;
	return 0;
}