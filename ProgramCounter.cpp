#include "ProgramCounter.h"

// This class sets the program counter for the processor

ProgramCounter::ProgramCounter(){
    cr = "0x40000";
}

string ProgramCounter::inputs(){
    // toHex.str("");
    // toHex << std::hex << cr;
    return cr;
}

string ProgramCounter::outputs(){
    // toHex.str("");
    // toHex << std::hex << cr;
    return cr;
}