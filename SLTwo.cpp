#include "SLTwo.h"

void SLTwo::compute(){
    output = input + "00";
    if (output.size() > 32){
        output = output.substr(output.size()-32);
    }
}