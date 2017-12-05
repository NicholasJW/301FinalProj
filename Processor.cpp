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
    string currentInsAddress;
    string currentIns;
    stringstream toHex;
    while(true){
        // Get current instruction address
        // Write back to pc
        if (insNum != 1)
            pc.setCurrentAddress(mux4.outputs());
        currentInsAddress = pc.getCurrentAddress();
        if(!imem.hasIns(currentInsAddress)){
            if (is_debug){
                cout << "End of Instruction Memory" << endl;
                cout << currentInsAddress << endl;
            }
            break;
        }
        if(is_debug)
            cout << "ProgramCounter Done" << endl;
        // ALU 1
        alu1.setInputs(currentInsAddress, "0x4");
        alu1.calculate();
        if(is_debug)
            cout << "ALU 1" << endl;
        // Instruction memory
        currentIns = imem.getIns(currentInsAddress);
        if(is_debug)
            cout << "Instruction Memory Done" << endl;
        // SLTwo 1:
        slt1.setInput(currentIns.substr(6));
        slt1.compute();
        // cout << slt1.outputs() << endl;
        if(is_debug)
            cout << "Shift Left Two 1 Done" << endl;
        // Get control signals from main control
        mc.setOpcode(currentIns.substr(0,6));
        setMainSignals(mc.getControlSignals());
        if(is_debug)
            cout << "Main Control Done" << endl;
        // Mux 1:
        mux1.setInput0(currentIns.substr(11,5));
        // cout << "CHECK HERE " <<currentIns.substr(11,5);
        mux1.setInput1(currentIns.substr(16,5));
        mux1.compute(stoi(regDst.getValue().substr(2), nullptr, 16));
        if(is_debug)
            cout << "Mutiplexer 1 Done" << endl;
        // Read from register memory:
        regs.setRead(std::stoi(currentIns.substr(6,5), nullptr, 2), std::stoi(currentIns.substr(11,5), nullptr, 2));
        regs.read();
        // Sign extend
        se.setInput(currentIns.substr(16));
        se.compute();
        if(is_debug)
            cout << "Sign Extend Done" << endl;
        // SLTwo 2:
        slt2.setInput(se.outputs());
        slt2.compute();
        if(is_debug)
            cout << "Shift Left Two 2 Done" << endl;
        // cout << "Check" << endl;
        // ALU 2:
        // Get a hex str
        // cout << slt2.outputs() << endl;
        long alu2SecondInput = stol(slt2.outputs(), nullptr, 2);
        toHex.str("");
        toHex.clear();
        toHex << std::hex << alu2SecondInput;
        string alu2SeStr = "0x" + toHex.str();
        // cout << alu1.getResult() << endl;
        // cout << alu2SeStr << endl;
        // cout << "Check" << endl;
        alu2.setInputs(alu1.getResult(), alu2SeStr);
        alu2.calculate();
        if(is_debug)
            cout << "ALU 2 Done" << endl;
        // MUX 2:
        long mux2SecondInput = stol(se.outputs(), nullptr, 2);
        toHex.str("");
        toHex.clear();
        toHex << "0x" << std::hex << mux2SecondInput;
        string mux2SeStr = toHex.str();
        mux2.setInput0("0x" + regs.getRead2());
        mux2.setInput1(mux2SeStr);
        // cout << mux2SeStr << endl;
        // cout << "ALU SRC: " << ALUSrc.getValue()<< endl;
        mux2.compute(stoi(ALUSrc.getValue().substr(2), nullptr, 16));
        // cout << mux2.outputs() << endl;
        if(is_debug)
            cout << "Multiplexer 2 Done" << endl;

        // ALU Control:
        ac.setControl(ALUOp1.getValue(), ALUOp2.getValue());
        ac.setFuncCode(currentIns.substr(26));
        // cout << currentIns.substr(26) << endl;
        ac.compute();
        ALUline.setValue(ac.outputs());
        // cout << "Check" << endl;
        if(is_debug)
            cout << "ALU Control Done" << endl;
        // ALU 3:
        // cout << regs.getRead1() << "  " << regs.getRead2() << endl;
        // cout << mux2.outputs() << endl;
        // cout << regs.getRead1() << endl;
        alu3.setInputs("0x" + regs.getRead1(), "0x" + mux2.outputs());
        // cout << "check" << endl;
        alu3.calculate(ALUline.getValue());
        zeroLine.setValue(alu3.getZeroValue());
        if(is_debug)
            cout << "ALU 3 Done" << endl;
        // MUX 5:
        mux5.setInput0(alu1.getResult());
        mux5.setInput1(alu2.getResult());
        int mux5Control;
        // A small AND gate
        if(branch.getValue() == "0x1" && zeroLine.getValue() == "0x1"){
            mux5Control = 1;    
        }else{
            mux5Control = 0;
        }
        mux5.compute(mux5Control);
        if(is_debug)
            cout << "Multiplexer 5 Done" << endl;
        // MUX 4:
        // Convert to binary
        toHex.str("");
        toHex.clear();
        toHex << std::hex << alu1.getResult();
        // cout << toHex.str() << endl;
        unsigned toBinary;
        toHex >> toBinary;
        std::bitset <32> b(toBinary);
        string alu1Result = b.to_string();
        // cout << alu1Result << endl;
        alu1Result = alu1Result.substr(0,4)+slt1.outputs();
        // cout << alu1Result << endl;
        long mux4In1 = stol(alu1Result, nullptr, 2);
        toHex.str("");
        toHex.clear();
        toHex << "0x" << std::hex << mux4In1;
        // Need hex string
        mux4.setInput1(toHex.str());
        mux4.setInput0(mux5.outputs());
        mux4.compute(stoi(jump.getValue().substr(2), nullptr, 16));
        if(is_debug)
            cout << "Multiplexer 4 Done" << endl;
        // Memory
        // stringstream toHex;
        // toHex << "0x" << std::hex << alu3.getResult();
        dmem.setAddress(alu3.getResult());
        // cout << "ALU 3 REsult " << alu3.getResult() << endl;
        // toHex.str("");
        dmem.setWriteData("0x" + regs.getRead2());
        if (memRead.getValue() == "0x1"){
            dmem.readMem();
        }
        if (memWrite.getValue() == "0x1"){
            dmem.writeMem();
        }
        if(is_debug)
            cout << "Data Memory Done" << endl;
        // MUX 3
        // toHex << "0x" << std::hex << alu3.getResult();
        mux3.setInput0(alu3.getResult());
        // toHex.str("");
        mux3.setInput1(dmem.outputs());
        mux3.compute(stoi(memtoReg.getValue().substr(2), nullptr, 16));
        if(is_debug)
            cout << "Multiplexer 3 Done" << endl;
        // Writing back to Registers
        regs.setSignal(regWrite.getValue());
        regs.setWrite(std::stoi(mux1.outputs(), nullptr, 2), mux3.outputs());
        regs.write();
        if(is_debug)
            cout << "Register write back Done" << endl;

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
    ss << "Mux 2:\n" << mux2.inputs() << '\n' << "Output: "<< mux2.outputs() << "\n\n";
    ss << "ALU Control: \n" << ac.inputs() << '\n' << "Output: "<< ac.outputs() <<"\n\n";
    ss << "ALU 3:\n" << "Inputs: \n"<< alu3.inputs() << "Control signal: " << alu3.getControlSignal() << '\n' << alu3.outputs() << "Zero Value: "<< alu3.getZeroValue() << "\n\n";
    ss << "Mux 5:\n" << mux5.inputs() << '\n' << "Output: "<< mux5.outputs() << "\n\n";
    ss << "Mux 4:\n" << mux4.inputs() << '\n' << "Output: "<< mux4.outputs() << "\n\n";
    ss << "Data Memory: \n" << dmem.inputs() << "\n Control Signals: " << "\n MemRead: " << memRead.getValue() << "\n MemWrite: " << memWrite.getValue() << "\n Ouput: " << dmem.outputs() << "\n\n"; 
    ss << "Mux 3:\n" << mux3.inputs() << '\n' << "Output: "<< mux3.outputs() << "\n\n";
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
