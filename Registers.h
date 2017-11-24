#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
// #include <array> // Pointless to use this data structure, basic array would work

using namespace std;

class Registers{
public:
	// Default constructor
	Registers();

	// Constructor that takes a file name as input and construct the Registers
	Registers(string register_file_input){readFile(register_file_input);};

	string get(int num);

	void set(int num, string value);

	// Print out the registers
	void print();

private:
	// Hashmap to represent the registers
	string regs[32];

	// Initialize registers from a file
	void readFile(string filename);

	// Private helper method to remove (possible) 0x before hex
	string remove0x(string str);
};

#endif