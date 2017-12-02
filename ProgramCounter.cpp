#include "ProgramCounter.h"

ProgramCounter::ProgramCounter(){
    cr = 0x40000;
}

string ProgramCounter::inputs(){
    toHex.str("");
    toHex << std::hex << cr;
    return "0x" + toHex.str();
}

string ProgramCounter::outputs(){
    toHex.str("");
    toHex << std::hex << cr;
    return "0x" + toHex.str();
}