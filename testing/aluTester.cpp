#include "../ALU.h"

int main(){
    ALU at;
    at.setInputs("0xffffffff", "0xeeeeeeee");
    at.calculate();
    cout << at.inputs() << '\n' << at.outputs() << endl;
    
    ALU at2;
    at2.setInputs("0x1", "0x1");
    at2.calculate("0x6");
    cout << "\n\n\n" << at2.inputs() << '\n' << at2.outputs() << at2.getZeroValue() << '\n' << at2.getControlSignal() << endl;
}