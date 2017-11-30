#include "Processor.h"

Processor::Processor(InstructionMem _iMem, DataMem _dMem, Registers _registers){
    imem = _iMem;
    dmem = _dMem;
    regs = _registers;

}

void Processor::run(bool is_single_step, bool is_debug, bool print_memory, bool write_to_file){

}

void Processor::printOut(bool write_to_file, string output_file){
    if(write_to_file){
        if(!ofs.is_open()){
            ofs.open(output_file, std::ofstream::out |  std::ofstream::app | std::ofstream::binary);
        }else{

        }
    }else{
        cout<<ss.str()<<endl;
    }

    ss.str("");
    ss.clear();
}