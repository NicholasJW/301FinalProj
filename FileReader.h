#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string> //for receiving input file
//#include <fstream> //for parsing input file
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

        //Do we need to make a deconstructor to close ifstream?

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
        string   imem;           // program_input
        string   dmem;           // memory_contents_input
        string   regf;           // register_file_input
        string   oputf;          // output_file        
        bool     is_single_step; // output_mode
        bool     is_debug;       // debug_mode
        bool     print_memory;   // print_memory_contents
        bool     write_to_file;  // write_to_file
        //ifstream  configFile;    // the filestream to read the config
};

#endif