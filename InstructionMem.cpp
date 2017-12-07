#include "InstructionMem.h"
// #include "InstrucMem/ASMParser.h"

/* This class will read in the Instruction Memory file and convert them into binary
 * line by line.
 */

// Contructor that build a Instruction memory out of an assembly file
InstructionMem::InstructionMem(string program_input){
    ASMParser *parser;

    parser = new ASMParser(program_input);

    if(parser->isFormatCorrect() == false){
        cerr << "Format of input file is incorrect " << endl;
        exit(1);
    }

    Instruction i;

    //Initial memory address at which instructions are stored
    string memAddress = "0x40000"; 

    //Iterate through instructions, printing each encoding.
    i = parser->getNextInstruction();

    string instruction;

    while( i.getOpcode() != UNDEFINED){
        // instruction = i.getEncoding(); //instruction from assembly file
        add(memAddress, i); //add the instruction at corresponding memory location to hashtable
        long adLong = stol(memAddress.substr(2), nullptr, 16);
        adLong += 4;
        stringstream toHex;
        toHex << "0x" << std::hex << adLong;
        memAddress = toHex.str();
        // memAddress += 4; //incrememnt memAddress by 4 bytes
        i = parser->getNextInstruction();
    }
    delete parser;
}


// Get the binary instruction 
string InstructionMem::getIns(string insAddress){
    currentIn = insAddress;
    currentOut = ins.at(insAddress);
    return currentOut;
}


// Get the instruction in assembly language
string InstructionMem::getInsMips(string insAddress){
    currentIn = insAddress;
    currentOut = ins.at(insAddress);
    return insMips.at(insAddress);
}


// Check if there is an instruction at this address
bool InstructionMem::hasIns(string insAddress){
    if(ins.count(insAddress)){
        return true;
    }
    return false;
}


// This function returns the string representing the inputs of Instruction Memory
string InstructionMem::inputs(){
    // stringstream toHex;
    // toHex << std::hex << currentIn;
    return currentIn;
}


// Function to print out the whole content of instruction memory
string InstructionMem::toString(){
    string s = "\n\n======================================\n";
    s += "Instruction Memmory:\n(All value in hex)\n";
    for(map<string, string>::iterator it = ins.begin(); it!=ins.end();++it){
        // address  = it->first;
        // ss << std::hex << address;
        s += it -> first;
        // s += ss.str();
        s += " : ";
        s += it -> second;
        s += " (";
        s += insMips.at(it -> first);
        s += ')';
        s += "\n";
        // ss.it -> firstr();
        // ss.str("");
    }
    return s;
}


// Helper function that adds an instruction to the corresponding address
void InstructionMem::add(string insAddress, Instruction i){
    // cout<<"check"<<endl;
    ins[insAddress] = i.getEncoding();
    insMips[insAddress] = i.getPlain();
}