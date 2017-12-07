#include "SignExtend.h"

/*	This class extends the number of bits in a binary number while preserving the
 *  number's positive/negative sign and value
 */

// Sets the input given a string of binary numbers
void SignExtend::setInput(string s){
    input = s;
}


// Computes the sign extension of the given input
void SignExtend::compute(){
    char sign = input[0];
    output = input;
    for (int i=0; i<16; i++){
        output = sign + output;
    }
    // cout << output << endl;
}