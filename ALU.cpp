#include "ALU.h"

ALU::ALU(){
    input1 = -1;
	input2 = -1;
	result = -1;
}

void ALU::setInputs(int first, int second){
    input1 = first;
    input2 = second;
}

void ALU::calculate(string control){
    // TODO different calculation based on different OPCODE
    // return result;
}

void ALU::calculate(){
    result = input1 + input2;
    // return result;
}

string ALU::inputs(){
    stringstream toHex;
    toHex << "First input: 0x";
    toHex << std::hex << (input1);
    toHex << '\n';
    toHex << "Second input: 0x";
    toHex << std::hex << (input2);
    toHex << '\n';
    return toHex.str();
}

string ALU::outputs(){
    stringstream toHex;
    toHex << "Output: 0x";
    toHex << std::hex << (result);
    toHex << '\n';
    return toHex.str();
}