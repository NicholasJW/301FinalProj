#include <iostream>
#include "../FileReader.h"
using namespace std;

int main(){

// Variables for simplifying printing
//===============================================================================================//
    string br = "=====================================================\n";
    string pass = "Result: Pass\n";
    string fail = "Result: Fail\n";
//===============================================================================================//

//Testing FileReader
//===============================================================================================//
    cout << br;
    cout << "Testing FileReader\n";
    cout << br;
    cout << "Testing FileReader(string filename)\n";
    cout << br;
    try{
        FileReader config("config.cfg");
    }catch(...){
        cout << fail;
        throw;
        return 1;
    }
    cout << pass;
    cout << br;
    cout << "Listing Environment Variables\n";
    cout << br;
    cout << getenv("program_input") << endl;
    cout << getenv("memory_contents_input") << endl;
    cout << getenv("register_file_input") << endl;
    cout << getenv("output_file") << endl;
    cout << getenv("output_mode") << endl;
    cout << getenv("debug_mode") << endl;
    cout << getenv("print_memory_contents") << endl;
    cout << getenv("write_to_file") << endl;
    cout << getenv("java") << endl;
    cout << br;
//===============================================================================================//

	return 0;
}