#include "FileReader.h"  // Header file
#include <fstream>       // For parsing input file (ifstream)
#include <unordered_map> // For making the hash map of settings

FileReader::FileReader(string filename){ // Create the fstream with the target file (No default constructor)

// VARIABLES
//=========================================================================================================//
    unordered_map<string,string> vars; // Unordered map (Hash map) of settings
    ifstream ifs;                      // Input filestream (for config file)
    string line;                       // String for holding lines
    int character;                     // Char for finding the equals character
    int index;                         // Int for holding index being checked
    string key;                        // String for holding the key
    string value;                      // String for holding the value
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
}

// GET SETTING METHODS
//=========================================================================================================//
string FileReader::getInstMem(){
    return imem;
}

string FileReader::getDataMem(){
    return dmem;
}

string FileReader::getRegFile(){
    return regf;
}

string FileReader::getOutFile(){
    return oputf;
}

bool FileReader::getOutMode(){
    return is_single_step;
}

bool FileReader::getDebugMode(){
    return is_debug;
}

bool FileReader::getPrintMem(){
    return print_memory;
}

bool FileReader::writeToFile(){
    return write_to_file;
}
//=========================================================================================================//