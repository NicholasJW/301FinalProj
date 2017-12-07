#include "ALUControl.h"

/* This class computes the output signal of the ALU based on either a control signal
 * or a function code and returns the values for ALUOp1, ALUOp2, and the function code
 */

// Set up ALU Control
void ALUControl::setControl(string op1, string op2){
    control = op1.substr(2) + op2.substr(2);
}


// Compute output signal based on the control signal (I-type) or opcode (R-Type)
void ALUControl::compute(){
    // LW and SW == ADD
    if(control == "00"){
        output = "0x2";

    // BEQ == SUB
    }else if(control == "01"){
        output = "0x6";

    // R-type
    }else{
        // ADD
        if (funcCode == "100000"){
            output = "0x2";

        // SUB
        }else if(funcCode == "100010"){
            output = "0x6";

        // AND
        }else if(funcCode == "100100"){
            output = "0x0";
        // OR
        }else if(funcCode == "100101"){
            output = "0x1";

        // SLT
        }else if(funcCode == "101010"){
            output = "0x9";
        }
    }
}



string ALUControl::inputs(){
    // testing
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