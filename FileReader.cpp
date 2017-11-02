#include "FileReader.h"
#include <cstdlib>                                             // For putenv()
#include <fstream>                                             // For parsing input file
#include <cstring>

FileReader::FileReader(string filename){                       // Create the fstream with the target file

    putenv("java=shit");
    cout << getenv("java") << endl;
    ifstream ifs;

// OPEN FSTREAM
//=======================================================================================================//
    try{                                                       // Try to open fstream with the file
        ifs.open(filename);
    }catch(...){                                               // Catch any error...
        throw;                                                 // Throw
    }
//=======================================================================================================//

// SET ENVIRONMENT VARIABLES
//=======================================================================================================//

    string line;                                               // Declare the string for holding lines
    char env[256];                                             // Declare char array for holding environment pairs

    while(true){                                               // Run loop until it is broken
        getline(ifs, line);                                    // Get the next line and store it
        if(!ifs.eof() && (line[0] == '#' || line[0] == '\0')){ // If the line is a comment or whitespace
            //do nothing (loop again)
        }else if(!ifs.eof()){                                  // If the line isn't an eof...
            strncpy(env, line.c_str(), line.length());         // Get a char* from the getline
            env[line.length()] = '\0';                         // Append a null terminator
            cout << env << endl;
            putenv(env);                                       // Use putenv to set the variable
        }else{                                                 // Else...
            break;                                             // Break the loop (Finish reading the file)
        }
    }
//=======================================================================================================//

    ifs.close();                                               // Close the fstream
}