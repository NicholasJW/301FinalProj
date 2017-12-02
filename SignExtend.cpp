#include "SignExtend.h"

void SignExtend::setInput(string s){
    input = s;
}

void SignExtend::compute(){
    char sign = input[0];
    output = input;
    for (int i=0; i<16; i++){
        output = sign + output;
    }
    // cout << output << endl;
}