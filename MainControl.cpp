
#include "MainControl.h"

/* This class is the main control unit, which takes a 6-bit opcode as input an
 * output 9 control signals each of which is represented as a string.
 */

// Sets up control signal vector
MainControl::MainControl(){
    signals.resize(10);
    for(int i=0; i<10;i++){
        signals[i] = "0x0";
    }
}

// Given an opcode, sets 9 control signals (in hex) as strings stored in a vector
void MainControl::setOpcode(string _opcode){

    if (_opcode.size()!=6){
        cerr << "Wrong opcode" << endl;
        exit(1);
    }
    opcode = _opcode;

    if (opcode == "000000"){            // R-FORMAT

        signals[0] = "0x1";             // RegDst
        signals[1] = "0x0";             // Jump
        signals[2] = "0x0";             // brach
        signals[3] = "0x0";             // memRead
        signals[4] = "0x0";             // memToReg
        signals[5] = "0x1";             // ALUOp1
        signals[6] = "0x0";             // ALUOp2
        signals[7] = "0x0";             // memWrite
        signals[8] = "0x0";             // ALUSrc
        signals[9] = "0x1";             // regWrite

    }else if(opcode == "100011"){       // LW

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x0";             // Jump
        signals[2] = "0x0";             // brach
        signals[3] = "0x1";             // memRead
        signals[4] = "0x1";             // memToReg
        signals[5] = "0x0";             // ALUOp1
        signals[6] = "0x0";             // ALUOp2
        signals[7] = "0x0";             // memWrite
        signals[8] = "0x1";             // ALUSrc
        signals[9] = "0x1";             // regWrite

    }else if(opcode == "101011"){       // SW

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x0";             // Jump
        signals[2] = "0x0";             // brach
        signals[3] = "0x0";             // memRead
        signals[4] = "0x0";             // memToReg
        signals[5] = "0x0";             // ALUOp1
        signals[6] = "0x0";             // ALUOp2
        signals[7] = "0x1";             // memWrite
        signals[8] = "0x1";             // ALUSrc
        signals[9] = "0x0";             // regWrite

    }else if(opcode == "000100"){       // BEQ

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x0";             // Jump
        signals[2] = "0x1";             // brach
        signals[3] = "0x0";             // memRead
        signals[4] = "0x0";             // memToReg
        signals[5] = "0x0";             // ALUOp1
        signals[6] = "0x1";             // ALUOp2
        signals[7] = "0x0";             // memWrite
        signals[8] = "0x0";             // ALUSrc
        signals[9] = "0x0";             // regWrite

    }else if(opcode == "000010"){       // J

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x1";             // Jump
        signals[2] = "0x0";             // brach
        signals[3] = "0x0";             // memRead
        signals[4] = "0x0";             // memToReg
        signals[5] = "0x0";             // ALUOp1
        signals[6] = "0x0";             // ALUOp2
        signals[7] = "0x0";             // memWrite
        signals[8] = "0x0";             // ALUSrc
        signals[9] = "0x0";             // regWrite

    }else if(opcode == "001000"){       // Addi

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x0";             // Jump
        signals[2] = "0x0";             // brach
        signals[3] = "0x0";             // memRead
        signals[4] = "0x0";             // memToReg
        signals[5] = "0x0";             // ALUOp1
        signals[6] = "0x0";             // ALUOp2
        signals[7] = "0x0";             // memWrite
        signals[8] = "0x1";             // ALUSrc
        signals[9] = "0x1";             // regWrite

    }else{
        cerr << "Error: incorrect opcode: " << opcode << endl;
        exit(1);
    }
    
}