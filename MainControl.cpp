#include "MainControl.h"

MainControl::MainControl(){
    signals.resize(9);
    for(int i=0; i<9;i++){
        signals[i] = "666";
    }
}

// TODO: add corresponding output
void MainControl::setOpcode(string _opcode){
    if (_opcode.size()!=6){
        cerr << "Wrong opcode" << endl;
        exit(1);
    }
    opcode = _opcode;

    if (opcode == "000000"){

    }else if(opcode == "100011"){

    }else if(opcode == "101011"){

    }else if(opcode == "000100"){

    }
    
}