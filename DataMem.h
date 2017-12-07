#ifndef __DATAMEM_H__
#define __DATAMEM_H__

#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm> // To convert string to all lower case

using namespace std;

/* This class returns the value of the memory address and the data to read/write
 * when given an input file
 */

class DataMem{
public:
	// Default constructor
	DataMem();

	// Constructor that takes a file name as input and construct the DataMem 
	DataMem(string memory_contents_input){readFile(memory_contents_input);};

	// Sets up memory address and read/write data
	void setAddress(string a){address = a;};
	void setWriteData(string w){writeData = w;};
	void readMem(){readData = read(address);};
	void writeMem(){write(address, writeData);};

	// Returns the value of the memory address and the data to write
	string inputs();
	// Returns the read data in hex
	string outputs();

	// Read corresponding content from address
	string read(string address);

	// Write content to address 
	void write(string address, string content);

	// Print out the whole data memory
	string toString();

private:
	// testing
	// string fileName; 
	
	// Inputs
	string address;
	string writeData;
	string readData = "N/A";
	// Control signals
	string isMemRead;
	string isMemWrite;

	// Hashmap to store addresses and their contents
	map<string, string> data;

	// Method to open the memory_contents_input file
	void readFile(string filename);

	// Private helper method to remove (possible) 0x before hex
	string remove0x(string str);

};

#endif