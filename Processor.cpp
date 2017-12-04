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
        // Get current instruction address
        currentInsAddress = pc.getCurrentAddress();
        // ALU 1
        alu1.setInputs(currentInsAddress, 4);
        alu1.calculate();
        // Instruction memory
        currentIns = imem.getIns(currentInsAddress);
        // SLTwo 1:
        slt1.setInput(currentIns.substr(6));
        slt1.compute();
        // Get control signals from main control
        mc.setOpcode(currentIns.substr(0,6));
        setMainSignals(mc.getControlSignals());
        // Mux 1:
        mux1.setInput0(currentIns.substr(11,5));
        // cout << "CHECK HERE " <<currentIns.substr(11,5);
        mux1.setInput1(currentIns.substr(16,5));
        mux1.compute(stoi(regDst.getValue().substr(2), nullptr, 16));
        // Read from register memory:
        regs.setRead(std::stoi(currentIns.substr(6,5), nullptr, 2), std::stoi(currentIns.substr(11,5), nullptr, 2));
        regs.read();
        // Sign extend
        se.setInput(currentIns.substr(16));
        se.compute();
        // SLTwo 2:
        slt2.setInput(se.outputs());
        slt2.compute();
        // ALU 2:
        alu2.setInputs(alu1.getResult(), std::stoi(slt2.outputs(), nullptr, 2));
        alu2.calculate();
        // MUX 2:
        mux2.setInput0(regs.getRead2());
        mux2.setInput1("0x" + std::to_string(::stoi(se.outputs(), nullptr, 2)));
        mux2.compute(stoi(ALUSrc.getValue().substr(2), nullptr, 16));
        // ALU Control:
        ac.setControl(ALUOp1.getValue(), ALUOp2.getValue());
        ac.setFuncCode(currentIns.substr(26));
        ac.compute();
        ALUline.setValue(ac.outputs());
        // ALU 3:
        alu3.setInputs(stoi(regs.getRead1(), nullptr, 16), stoi(mux2.outputs(), nullptr, 16));
        alu3.calculate(ALUline.getValue());
        zeroLine.setValue(alu3.getZeroValue());

        // Writing back to Registers
        // Debugging DELETE!!!!!!!
        // regWrite.setValue("0x1");
        regs.setSignal(regWrite.getValue());
        regs.setWrite(std::stoi(mux1.outputs(), nullptr, 2), mux3.outputs());
        regs.write();

        // Some printing jobs
        ss << "\n============================\n\n";
        // For debugging 
        // cout << currentIns << endl;
        ss << std::to_string(insNum) << " : " << imem.getInsMips(currentInsAddress) << '\n' << currentIns << '\n';

        titleLine = ss.str();
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

        // Manually get new address, only debugging
        // currentInsAddress += 4;
    }

    ofs.close();
     
}

void Processor::initializeLines(){
    regDst.setName("regDst");
    jump.setName("jump");
    branch.setName("branch");
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

void Processor::setMainSignals(vector<string> list){
    regDst.setValue(list.at(0));
    jump.setValue(list.at(1));
    branch.setValue(list.at(2));
    memRead.setValue(list.at(3));
    memtoReg.setValue(list.at(4));
    ALUOp1.setValue(list.at(5));
    ALUOp2.setValue(list.at(6));
    memWrite.setValue(list.at(7));
    ALUSrc.setValue(list.at(8));
    regWrite.setValue(list.at(9));
}

void Processor::linesOutput(){
    ss << "\n==========================\n";
    ss << "value of all control lines:\n";
    ss << regDst.getName() << " : " << regDst.getValue() << '\n';
    ss << jump.getName() << " : " << jump.getValue() << '\n';
    ss << branch.getName() << " : " << branch.getValue() << '\n';
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
    ss << "Input and output of all units:\n\n";
    ss << "ProgramCounter :\n" << "Input (instruction address): "<< pc.inputs() << '\n' << "Output (instruction address): "<< pc.outputs() << "\n\n";
    ss << "Instruction Memory:\n" << "Input (instruction address): "<< imem.inputs() << '\n' << "Output (Binary instruction): "<< imem.outputs() << "\n\n";
    ss << "ALU 1:\n" << "Inputs: \n"<< alu1.inputs() << "Output: \n"<< alu1.outputs() << "\n";
    ss << "Shift left two 1:\n" << "Input : " << slt1.inputs() << '\n' << "Output: "<< slt1.outputs() << "\n\n";
    ss << "Main Contral: \n" << "Input: opcode " << mc.inputs() << "\nOuput: please see the first 10 lines of control lines value. "<<"\n\n";
    ss << "Mux 1:\n" << mux1.inputs() << '\n' << "Output: "<< mux1.outputs() << "\n\n";
    ss << "Registers memory: \n" << regs.inputs() << '\n' << regs.outputs() << "\n\n";
    ss << "Sign Extend unit: \n" << "Input: " << se.inputs() << '\n' << "Output: " << se.outputs() << "\n\n";
    ss << "Shift left two 2:\n" << "Input : " << slt2.inputs() << '\n' << "Output: "<< slt2.outputs() << "\n\n";
    ss << "ALU 2:\n" << "Inputs: \n"<< alu2.inputs() << "Output: \n"<< alu2.outputs() << "\n";
    ss << "Mux 2:\n" << mux2.inputs() << '\n' << "Output: 0x"<< mux2.outputs() << "\n\n";
    ss << "ALU Control: \n" << ac.inputs() << '\n' << ac.outputs() <<"\n\n";
    ss << "ALU 3:\n" << "Inputs: \n"<< alu3.inputs() << "Control signal: " << alu3.getControlSignal() << '\n' << alu3.outputs() << "Zero Value: "<< alu3.getZeroValue() << "\n\n";

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
        cout << titleLine << '\n';
    }else{
        cout<<ss.str()<<endl;
    }

    ss.str("");
    ss.clear();
}
