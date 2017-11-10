#ifndef __DATAMEM_H__
#define __DATAMEM_H__

#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <algorithm> // To convert string to all lower case

using namespace std;

class DataMem{
public:
	// Default constructor
	DataMem();

	// Constructor that takes a file name as input and construct the DataMem 
	DataMem(string memory_contents_input){readFile(memory_contents_input);};

	// Read corresponding content from address
	string read(string address);

	// Write content to address 
	void write(string address, string content);

	// Print out the whole data memory
	void print();

private:
	// string fileName;

	// Hashmap to store addresses and their contents
	map<string, string> data;

	void readFile(string filename);

	string remove0x(string str);

	
};

#endif