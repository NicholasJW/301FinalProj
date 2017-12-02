#include "Processor.h"

Processor::Processor(InstructionMem _iMem, DataMem _dMem, Registers _registers, bool _is_single_step, bool _is_debug, bool _print_memory, bool _write_to_file, string _output_file){
    // Set up the corresponging parameter
    is_single_step = _is_single_step;
    is_debug = _is_debug;
    print_memory = _print_memory;
    write_to_file = _write_to_file;
    output_file = _output_file;
    imem = _iMem;
    dmem = _dMem;
    regs = _registers;
}

void Processor::run(){
    
    initializeLines();
    int insNum = 1; //Indicating which instruction we are running
    int currentInsAddress = pc.getCurrentAddress();
    string currentIns;
    while(imem.hasIns(currentInsAddress)){
        currentInsAddress = pc.getCurrentAddress();
        currentIns = imem.getIns(currentInsAddress);

        // Some printing jobs
        ss << "\n============================\n\n";
        // For debugging 
        // cout << currentIns << endl;
        ss << std::to_string(insNum) << " : " << imem.getInsMips(currentInsAddress) << '\n' << currentIns << '\n';

        // Appending all the outputs
        linesOutput();
        unitOutput();
        if (print_memory){
            dataOutput();
        }

        printOut();

        // Debugging counter
        insNum++;

        if(is_single_step){
            cin.get();
        }

        currentInsAddress += 4;
    }

    ofs.close();
     
}

void Processor::initializeLines(){
    regDst.setName("regDst");
    jump.setName("jump");
    memRead.setName("memRead");
    memtoReg.setName("memtoReg");
    ALUOp1.setName("ALUOp1");
    ALUOp2.setName("ALUOp2");
    memWrite.setName("memWrite");
    ALUSrc.setName("ALUSrc");
    regWrite.setName("regWrite");
    ALUline.setName("ALUline");
    zeroLine.setName("zeroLine");
}

void Processor::linesOutput(){
    ss << "\n==========================\n";
    ss << "value of all control lines:\n";
    ss << regDst.getName() << " : " << regDst.getValue() << '\n';
    ss << jump.getName() << " : " << jump.getValue() << '\n';
    ss << memRead.getName() << " : " << memRead.getValue() << '\n';
    ss << memtoReg.getName() << " : " << memtoReg.getValue() << '\n';
    ss << ALUOp1.getName() << " : " << ALUOp1.getValue() << '\n';
    ss << ALUOp2.getName() << " : " << ALUOp2.getValue() << '\n';
    ss << memWrite.getName() << " : " << memWrite.getValue() << '\n';
    ss << ALUSrc.getName() << " : " << ALUSrc.getValue() << '\n';
    ss << regWrite.getName() << " : " << regWrite.getValue() << '\n';
    ss << ALUline.getName() << " : " << ALUline.getValue() << '\n';
    ss << zeroLine.getName() << " : " << zeroLine.getValue() << "\n\n";
}

void Processor::unitOutput(){
    ss << "==========================\n";
    ss << "Input and output of all units:\n";
    ss << "ProgramCounter :\n" << "Input (instruction address): "<< pc.inputs() << '\n' << "Output (instruction address): "<< pc.outputs() << "\n\n";
    ss << "Instruction Memory:\n" << "Input (instruction address): "<< imem.inputs() << '\n' << "Output (Binary instruction): "<< imem.outputs() << "\n\n";

}

void Processor::dataOutput(){
    ss << "==========================\n";
    ss << "All memory content:\n";
    ss << imem.toString();
    ss << dmem.toString();
    ss << regs.toString();
}

void Processor::printOut(){
    if(write_to_file){
        if(!ofs.is_open()){
            // Clear the file for any previous content
            ofs.open(output_file, std::ofstream::out |  std::ofstream::trunc | std::ofstream::binary);
            ofs << "";
            ofs.close();
            // Open the file
            ofs.open(output_file, std::ofstream::out |  std::ofstream::app | std::ofstream::binary);
        }
        ofs << ss.str();
        // TODO: As follow!!!
        // cout << "This line will be replaced be a instruction in InsMem." << endl;
    }else{
        cout<<ss.str()<<endl;
    }

    ss.str("");
    ss.clear();
}
