#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>

/* This class returns registers read in and their values
 */

using namespace std;

class Registers{
public:
	// Default constructor
	Registers();

	// Constructor that takes a file name as input and construct the Registers
	Registers(string register_file_input){readFile(register_file_input);};

	// Reading process
	void setRead(int reg1, int reg2){readReg1 = reg1; readReg2 = reg2;};
	void read();
	string getRead1(){return readData1;};
	string getRead2(){return readData2;};

	// Writing process
	void setSignal(string _regWrite){regWrite = _regWrite;};
	void setWrite(int reg, string data){writeReg = reg; writeData = data;};
	void write();

	// Presenting inputs
	string inputs();
	// Presenting output
	string outputs();

	// Print out the registers
	string toString();

private:
	// All inputs
	int readReg1 = -1;
	int readReg2 = -1;
	int writeReg = -1;
	string writeData;
	// Control signals
	string regWrite;
	// All outputs
	string readData1;
	string readData2;
	// Hashmap to represent the registers
	string regs[32];

	// Returns register number
	string get(int num);
	// Sets register number
	void set(int num, string value);

	// Initialize registers from a file
	void readFile(string filename);

	// Private helper method to remove (possible) 0x before hex
	string remove0x(string str);
};

#endif