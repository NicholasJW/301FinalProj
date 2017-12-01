#include "InstructionMem.h"
// #include "InstrucMem/ASMParser.h"

InstructionMem::InstructionMem(string program_input){
    ASMParser *parser;

    parser = new ASMParser(program_input);

    if(parser->isFormatCorrect() == false){
        cerr << "Format of input file is incorrect " << endl;
        exit(1);
    }

    Instruction i;

    //Initial memory address at which instructions are stored
    int memAddress = 0x40000; 

    //Iterate through instructions, printing each encoding.
    i = parser->getNextInstruction();

    string instruction;

    while( i.getOpcode() != UNDEFINED){
        // instruction = i.getEncoding(); //instruction from assembly file
        add(memAddress, i); //add the instruction at corresponding memory location to hashtable
        memAddress += 4; //incrememnt memAddress by 4 bytes
        i = parser->getNextInstruction();
    }
    
    delete parser;
}

string InstructionMem::toString(){
    string s = "\n\n======================================\n";
    s += "Instruction Memmory:\n\n";
    // cout<<ins.size()<<endl;
    // s += "hahahah";
    stringstream ss;
    int address;
    for(map<int, string>::iterator it = ins.begin(); it!=ins.end();++it){
        address  = it->first;
        ss << std::hex << address;
        s += "0x";
        s += ss.str();
        s += " : ";
        s += insMips.at(address);
        s += " : ";
        s += it->second;
        s += "\n";
        ss.clear();
        ss.str("");
    }
    return s;
}

void InstructionMem::add(int insAddress, Instruction i){
    // cout<<"check"<<endl;
    ins[insAddress] = i.getEncoding();
    insMips[insAddress] = i.getPlain();
}