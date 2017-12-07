#include "FileReader.h"  // Header file
#include <fstream>       // For parsing input file (ifstream)
#include <cctype>        // For checking for whitespace
#include <unordered_map> // For making the hash map of settings

/* This class reads in a Proj2 Config File from the constructor.
 * If the config file is improperly formatted, or the ASM doesn't compile,
 * an exception will be thrown.
 */

// Create the fstream with the target file (No default constructor)
FileReader::FileReader(string filename){

// Debug Line
// std::cout << "Filereader started.\n";

// VARIABLES
//=========================================================================================================//
    unordered_map<string,string> vars; // Unordered map (Hash map) of settings
    ifstream ifs;                      // Input filestream (for config file)
    string line;                       // String for holding lines
    int character;                     // Char for finding the equals character
    int index;                         // Int for holding index being checked
    string key;                        // String for holding the key
    string value;                      // String for holding the value
    bool whitespaceIsPresent;          // Boolean representing the presence of whitespace
//=========================================================================================================//

// OPEN FSTREAM
//=========================================================================================================//
    try{                                                       // Try to open stream with the file
        ifs.open(filename);
    }catch(...){                                               // Catch any error...
        throw;                                                 // Throw
    }
//=========================================================================================================//

// GET SETTING VARIABLES
//=========================================================================================================//
    while(true){                                               // Run loop until it is broken
        getline(ifs, line);                                    // Get the next line and store it

        // Clean whitespace from line
        whitespaceIsPresent = true;                            // Reset so check will run
        while(whitespaceIsPresent){                            // While there is still whitespace
            if(!isspace(line[0]) || line[0] == '\0'){          // If the first char is not whitespace
                whitespaceIsPresent = false;                   // or is a newline end the loop
            }else{                                             // Else...
                line.erase(0,1);                               // Erase the first char and run again
            }
        }

        if(!ifs.eof() && (line[0] == '#' || line[0] == '\0')){ // If the line is a comment or whitespace
            //do nothing (loop again)
        }else if(!ifs.eof()){                                  // If the line isn't an eof...
            index = 0;                                         // Set index back to 0
            character = 'x';                                   // Set the character back to a non '=' value
            while(character != '='){                           // While character isn't '='...
                character = line[index];                       // Get the character at index
                index++;                                       // Iterate index
            }
            key = line.substr(0,index - 1);                    // Get the key (first half) of the line
            value = line.substr(index, line.length() - index); // Get the values (second half) of the line
            vars.emplace(key, value);                          // Place the key, value pair in the map
        }else{                                                 // Else...
            break;                                             // Break the loop and continue setting up
        }
    }
    ifs.close();                                               // Close the fstream
//=========================================================================================================//

// SET SETTING VARIABLES
//=========================================================================================================//

    // String variables
    imem  = vars.at("program_input");
    dmem  = vars.at("memory_contents_input");
    regf  = vars.at("register_file_input");
    oputf = vars.at("output_file");

    // Boolean variables
    if(vars.at("output_mode") == "single_step"){is_single_step = true;}else{is_single_step = false;};
    if(vars.at("debug_mode") == "true"){is_debug = true;}else{is_debug = false;};
    if(vars.at("print_memory_contents") == "true"){print_memory = true;}else{print_memory = false;};
    if(vars.at("write_to_file") == "true"){write_to_file = true;}else{write_to_file = false;};
    

//=========================================================================================================//

// Debug Line
// std::cout << "Filereader finished.\n";

}

// GET SETTING METHODS
//=========================================================================================================//
// Returns a string containing the name of the program_input file
string FileReader::getInstMem(){
    return imem;
}

// Returns a string containing the name of the memory_contents_input file
string FileReader::getDataMem(){
    return dmem;
}

// Returns a string containing the name of the register_file_input file
string FileReader::getRegFile(){
    return regf;
}

// Returns a string containing the name of the output_file
string FileReader::getOutFile(){
    return oputf;
}

// Returns the boolean variable representing if the output mode is single
// step or batch. If it is single_step, true is returned, else false is returned
bool FileReader::getOutMode(){
    return is_single_step;
}

// Returns the boolean variable representing if the program is in debug mode
bool FileReader::getDebugMode(){
    return is_debug;
}

// Returns the boolean variable representing if the program prints the
// memory contents
bool FileReader::getPrintMem(){
    return print_memory;
}

// Returns the boolean variable representing if the output is written to the output file
bool FileReader::writeToFile(){
    return write_to_file;
}
//=========================================================================================================//