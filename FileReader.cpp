#include "FileReader.h"
#include <cstdlib>                       // For putenv()

FileReader::FileReader(string filename){ // Create the fstream with the target file
    
// OPEN FSTREAM
//===============================================================================================//
    try{                                 // Try to open fstream with the file
        configFile.open(filename);
    }catch(...){                         // Catch any error...
        throw;                           // Throw
    }
//===============================================================================================//

// SET ENVIRONMENT VARIABLES
//===============================================================================================//
    string line;                         // Declare the string for holding lines

    while(true){                         // Run loop until it is broken
        line = configFile.getline();     // Get the next line and store it
        if(line[0] == '#'){              // If the line is a comment...
            //do nothing
        }else if(line.eof() != true)     // If the line isn't an eof...
        {
            putenv(line);                // Use putenv to set the variable
        }else{                           // Else...
            break;                       // Break the loop (Finish reading the file)
        }
    }
//===============================================================================================//

    configFile.close();                  // Close the fstream
}