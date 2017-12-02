#include "MainControl.h"

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