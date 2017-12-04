#include "../InstructionMem.h"
#include <iostream>

int main(){
    InstructionMem tt("../sample_inputs/prog1.asm");
    cout << tt.getSize() << endl;
    cout << tt.toString() << endl;
}
