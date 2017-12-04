
#include "MainControl.h"

// Sets up control signal vector
MainControl::MainControl(){
    signals.resize(9);
    for(int i=0; i<9;i++){
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
        signals[1] = "0x0";             // ALUSrc
        signals[2] = "0x0";             // MemtoReg
        signals[3] = "0x1";             // RegWrite
        signals[4] = "0x0";             // MemRead
        signals[5] = "0x0";             // MemWrite
        signals[6] = "0x0";             // Branch
        signals[7] = "0x1";             // ALUOp1
        signals[8] = "0x0";             // ALUOp0

    }else if(opcode == "100011"){       // LW

        signals[0] = "0x0";             // RegDst
        signals[1] = "0x1";             // ALUSrc
        signals[2] = "0x1";             // MemtoReg
        signals[3] = "0x1";             // RegWrite
        signals[4] = "0x1";             // MemRead
        signals[5] = "0x0";             // MemWrite
        signals[6] = "0x0";             // Branch
        signals[7] = "0x0";             // ALUOp1
        signals[8] = "0x0";             // ALUOp0

    }else if(opcode == "101011"){       // SW

        signals[0] = "0x0";             // RegDst    (don't care)
        signals[1] = "0x1";             // ALUSrc
        signals[2] = "0x0";             // MemtoReg  (don't care)
        signals[3] = "0x0";             // RegWrite
        signals[4] = "0x0";             // MemRead
        signals[5] = "0x1";             // MemWrite
        signals[6] = "0x0";             // Branch
        signals[7] = "0x0";             // ALUOp1
        signals[8] = "0x0";             // ALUOp0

    }else if(opcode == "000100"){       // BEQ

        signals[0] = "0x0";             // RegDst    (don't care)
        signals[1] = "0x0";             // ALUSrc
        signals[2] = "0x0";             // MemtoReg  (don't care)
        signals[3] = "0x0";             // RegWrite
        signals[4] = "0x0";             // MemRead
        signals[5] = "0x0";             // MemWrite
        signals[6] = "0x1";             // Branch
        signals[7] = "0x0";             // ALUOp1
        signals[8] = "0x1";             // ALUOp0

    }else if(opcode == "000010"){

        signals[0] = "0x0";             // RegDst    (don't care)
        signals[1] = "0x0";             // ALUSrc
        signals[2] = "0x0";             // MemtoReg  (don't care)
        signals[3] = "0x0";             // RegWrite
        signals[4] = "0x0";             // MemRead
        signals[5] = "0x0";             // MemWrite
        signals[6] = "0x0";             // Branch
        signals[7] = "0x0";             // ALUOp1
        signals[8] = "0x0";             // ALUOp0

    }else {
        cerr << "Error: incorrect opcode: " << opcode << endl;
        exit(1);
    }
    
}