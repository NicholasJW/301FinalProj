#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string> //for receiving input file
#include <fstream> //for parsing input file
#include <iostream>
#include <stdexcept> 

using namespace std;

/* This class reads in a Proj2 Config File from the constructor.
 * If the config file is improperly formatted, or the ASM doesn't compile,
 *   an exception will be thrown.
 */

class FileReader{
    public:
        // Constructs a FileReader with the path of a config file
        // May throw an exception
        FileReader(string filename);

        // Returns a string containing the name of the program_input file
        string getInstructionMem();

        // Returns a string containing the name of the memory_contents_input file
        string getDataMem();

        // Returns a string containing the name of the register_file_input file
        string getRegFile();

        // Returns a string containing the name of the output_file
        string getOutputFile();

        // Returns the boolean variable representing if the output mode is single 
        // step or batch. If it is single_step, true is returned, else false is returned
        bool getOutputMode();

        // Returns the boolean variable representing if the program is in debug mode
        bool getDebugMode();

        // Returns the boolean variable representing if the program prints the
        // memory contents
        bool getPrintMemoryContents();

        // Returns the boolean variable representing if the output is wriiten to the output file
        bool writeToFile();


    private:
	  // int MAX_CHARS_PER_LINE;
        string imem;
        string dmem;
        string regf;
        string oputf;        
        bool is_single_step;
        bool is_debug;
        bool print_memory;
        bool write_to_file;
};

#endif