#include "MUX.h"

// void MUX::setInput0(int _value){
//     input0.value = _value;
//     input0.type = 0;
// }

// void MUX::setInput1(int _value){
//     input1.value = _value;
//     input1.type = 0;
// }

void MUX::setInput0(string _content){
    input0.content = _content;
    input0.type = 1;
}

void MUX::setInput1(string _content){
    input1.content = _content;
    input1.type = 1;
}

void MUX::compute(int choose){
    stringstream out;
    if (choose == 0){
        if (input0.type == 0){
            out << "0x" << std::hex << input0.value;
        }else{
            out << input0.content;
        }
    } else if (choose == 1){
        if (input1.type == 0){
            out << "0x" << std::hex << input1.value;
        }else{
            out << input0.content;
        }
    }
    output = out.str();
}

// string MUX::getStringOutput(int choose){
//     outType = 1;
//     if (choose == 0){
//         outStr = input0.content;
//         return outStr;
//     } else if (choose == 1){
//         outStr = input1.content;
//         return outStr;
//     }

//     return "Wrong index for this mux.";
// }

// int MUX::getIntOutput(int choose){
//     outType = 1;
//     if (choose == 0){
//         outInt = input0.value;
//         return outInt;
//     } else if (choose == 1){
//         outInt = input1.value;
//         return outInt;
//     }

//     return -1;
// }

string MUX::inputs(){
    stringstream toHex;
    toHex << "Inputs: ";
    toHex << "\n  Input 0: ";
    if (input0.type == 0){
        toHex << "0x" << std::hex << input0.value;
    }else{
        toHex << input0.content;
    }
    toHex << "\n  Input 1: ";
    if (input1.type == 0){
        toHex << "0x" << std::hex << input1.value;
    }else{
        toHex << input1.content;
    }
    return toHex.str();
}

string MUX::outputs(){
    return output;
}