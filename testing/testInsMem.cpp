#include "../InstructionMem.h"

int main(int argc, char *argv[]){

    InstructionMem i("../sample_inputs/prog1.asm");
	// Debugging makefile
    // cout << "Makefile works fine!" << endl;
    cout<<i.toString()<<endl;
	return 0;
}