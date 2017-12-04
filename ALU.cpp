#include "ALU.h"

ALU::ALU(){
    input1 = "0x00000000";
	input2 = "0x00000000";
	result = "0x00000000";
}

// void ALU::setInputs(int first, int second){
//     input1 = first;
//     input2 = second;
// }

void ALU::setInputs(string first, string second){
    input1 = first;
    input2 = second;
}

void ALU::calculate(string _control){
    control = _control;
    stringstream ss;
    if(control == "0x2"){
        one = stol(input1.substr(2), nullptr, 16);
        two = stol(input2.substr(2), nullptr, 16);
        calc = one + two;
        ss.str("");
        ss.clear();
        ss << std::hex << calc;
        if (ss.str().size()>8){
            result = "0x" + ss.str().substr(ss.str().size()-8);
        }else{
            result = "0x" + ss.str();
        }
    }else if(control == "0x6"){
        one = stol(input1.substr(2), nullptr, 16);
        two = stol(input2.substr(2), nullptr, 16);
        calc = one - two;
        ss.str("");
        ss.clear();
        ss << std::hex << calc;
        if (ss.str().size()>8){
            result = "0x" + ss.str().substr(ss.str().size()-8);
        }else{
            result = "0x" + ss.str();
        }
    }else if(control == "0x9"){
        one = stol(input1.substr(2), nullptr, 16);
        two = stol(input2.substr(2), nullptr, 16);
        calc = one - two;
        if(calc<0){
            result = "0x1";
        }else{
            result = "0x0";
        }
        // ss << std::hex << calc;
        // if (ss.str().size()>8){
        //     result = "0x" + ss.str().substr(ss.str().size()-8);
        // }else{
        //     result = "0x" + ss.str();
        // }
    }else{
        cout << control << endl;
        cerr << "Wrong ALU Control signal" << endl;
        exit(1);
    }
    // stringstream toHex;
    // toHex << std::hex << result;
    // string s = toHex.str();
    // if (s.size()>8){
    //     s = s.substr(s.size()-8);
    // }
    // result = stoi(s, nullptr, 16);
    if(calc == 0){
        zeroValue = "0x1";
    }else{
        zeroValue = "0x0";
    }
    
}

void ALU::calculate(){
    stringstream ss;
    one = stol(input1.substr(2), nullptr, 16);
    two = stol(input2.substr(2), nullptr, 16);
    calc = one + two;
    ss << std::hex << calc;
    if (ss.str().size()>8){
        result = "0x" + ss.str().substr(ss.str().size()-8);
    }else{
        result = "0x" + ss.str();
    }
    // result = input1 + input2;
    // stringstream toHex;
    // toHex << std::hex << result;
    // string s = toHex.str();
    // if (s.size()>8){
    //     s = s.substr(s.size()-8);
    // }
    // result = stoi(s, nullptr, 16);
    if(calc == 0){
        zeroValue = "0x1";
    }else{
        zeroValue = "0x0";
    }
}

string ALU::inputs(){
    stringstream toHex;
    toHex << "First input: ";
    toHex << (input1);
    toHex << '\n';
    toHex << "Second input: ";
    toHex << (input2);
    toHex << '\n';
    return toHex.str();
}

string ALU::outputs(){
    stringstream toHex;
    toHex << "Output: ";
    toHex << (result);
    toHex << '\n';
    return toHex.str();
}
