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

//===============================================================================================//
	return 0;
}