#include "ALUControl.h"

void ALUControl::setControl(string op1, string op2){
    control = op1.substr(2) + op2.substr(2);
}

void ALUControl::compute(){
    if(control == "00"){
        // LW and SW == add
        output = "0x2";
    }else if(control == "01"){
        // Beq == sub
        output = "0x6";
    }else{
        // R-type
        if (funcCode == "100000"){
            // add
            output = "0x2";
        }else if(funcCode == "100010"){
            // sub
            output = "0x6";
        }else if(funcCode == "100100"){
            // and
            output = "0x0";
        }else if(funcCode == "100101"){
            // or
            output = "0x1";
        }else if(funcCode == "101010"){
            // set on less than
            output = "0x9";
        }
    }
}

string ALUControl::inputs(){
    // cout << control << ' ' << funcCode << ' ' << output;
    stringstream ss;
    ss << "Inputs: ";
    ss << "\n ALUOp1: 0x" << control.at(0);
    ss << "\n ALUOp2: 0x" << control.at(1);
    ss << "\n Function code: " << funcCode;
    return ss.str();
}

string ALUControl::outputs(){
    return output;
}