#include "SLTwo.h"

/*	This class shifts the bits of a given number two to the left
 */

// Shifts the number left by two
void SLTwo::compute(){
    output = input + "00";
    if (output.size() > 32){
        output = output.substr(output.size()-32);
    }
}