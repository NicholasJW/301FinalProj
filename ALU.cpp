#include "ALU.h"

/* This class functions as the Arithmetic Logic Unit by performing arithmetic and
 * logical operations based on a given hex input value and outputs the result of the
 * operation performed.
 */

// Set-up ALU with default values
ALU::ALU(){
    input1 = "0x00000000";
	input2 = "0x00000000";
	result = "0x00000000";
}


// testing
// void ALU::setInputs(int first, int second){
//     input1 = first;
//     input2 = second;
// }


// Set string values as inputs for ALU
void ALU::setInputs(string first, string second){
    input1 = first;
    input2 = second;
}


// First calculation method for ALU given a control signal
void ALU::calculate(string _control){
    control = _control;
    stringstream ss;

    // Control signal = 2
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

    // Control signal = 6
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

    // Control signal = 9
    }else if(control == "0x9"){
        one = stol(input1.substr(2), nullptr, 16);
        two = stol(input2.substr(2), nullptr, 16);
        calc = one - two;
        if(calc<0){
            result = "0x1";
        }else{
            result = "0x0";
        }

        // testing
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

    // testing
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


// Second calulation method for ALU without a given control signal
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

    // testing
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


// Returns the input values to the ALU in hexadecimal
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


// Returns the output values to the ALU in hexadecimal
string ALU::outputs(){
    stringstream toHex;
    toHex << "Output: ";
    toHex << (result);
    toHex << '\n';
    return toHex.str();
}
