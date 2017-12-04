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

void ALU::calculate(string _control){
    control = _control;
    if(control == "0x2"){
        result = input1 + input2;
    }else if(control == "0x6"){
        result = input1 - input2;
    }else{
        cerr << "Wrong ALU Control signal" << endl;
        exit(1);
    }

    stringstream toHex;
    toHex << std::hex << result;
    string s = toHex.str();
    if (s.size()>8){
        s = s.substr(s.size()-8);
    }
    result = stoi(s, nullptr, 16);
    if(result == 0){
        zeroValue = "0x1";
    }else{
        zeroValue = "0x0";
    }
    
}

void ALU::calculate(){
    result = input1 + input2;
    stringstream toHex;
    toHex << std::hex << result;
    string s = toHex.str();
    if (s.size()>8){
        s = s.substr(s.size()-8);
    }
    result = stoi(s, nullptr, 16);
    if(result == 0){
        zeroValue = "0x1";
    }else{
        zeroValue = "0x0";
    }
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
