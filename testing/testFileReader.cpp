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
        FileReader configTest("config.cfg");
    }catch(...){
        cout << fail;
        throw;
        return 1;
    }
    FileReader config("config.cfg");
    cout << pass;
    cout << br;
    cout << "Listing Environment Variables (get Methods)\n";
    cout << br;
    cout << "program_input = "         << config.getInstMem()   << endl;
    cout << "memory_contents_input = " << config.getDataMem()   << endl;
    cout << "register_file_input = "   << config.getRegFile()   << endl;
    cout << "output_file = "           << config.getOutFile()   << endl;
    cout << "output_mode = "           << config.getOutMode()   << endl;
    cout << "debug_mode = "            << config.getDebugMode() << endl;
    cout << "print_memory_contents = " << config.getPrintMem()  << endl;
    cout << "write_to_file = "         << config.writeToFile()  << endl;
    cout << br;
    cout << pass;
    cout << br;
    cout << "Testing complete\n";
    cout << br;
//===============================================================================================//

	return 0;
}