#include "Registers.h"

/* This class returns registers read in and their values
 */

// Default constructor
Registers::Registers(){

}


// Reading process
void Registers::read(){
    if (readReg1 > -1 && readReg1 < 32){
        readData1 = get(readReg1);
    }
    if (readReg2 > -1 && readReg2 < 32){
        readData2 = get(readReg2);
    }
}


// Writing process
void Registers::write(){
    if (regWrite == "0x1"){
        if (writeReg > -1 && writeReg < 32){
            set(writeReg, writeData);
        }
    }
}


// Presenting inputs
string Registers::inputs(){
    stringstream ss;
    ss << "Inputs: ";
    ss << "\nFirst read register: $" << std::to_string(readReg1);
    ss << "\nSecond read register: $" << std::to_string(readReg2);
    ss << "\nWrite register: $" << std::to_string(writeReg);
    ss << "\nWrite data: " << writeData;
    ss << "\nControl signal (regWrite): " << regWrite;
    return ss.str();
}


// Presenting outputs
string Registers::outputs(){
    stringstream ss;
    ss << "Outputs: ";
    ss << "\nFirst reading data: " << "0x" << readData1;
    ss << "\nSecond reading data: " << "0x" << readData2;
    return ss.str();
}


// Returns register number
string Registers::get(int num){
    if(num>-1 || num<32){
        return regs[num];
    }else{
        throw invalid_argument("register_not_found");
    }
}


// Sets register number
void Registers::set(int num, string value){
    if(num>-1 || num<32){
        value = remove0x(value);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        regs[num] = value;
    }else{
        throw invalid_argument("register_not_found");
    }
}


// Prints out the registers
string Registers::toString(){
    string s = "\n\n======================================\n";
    s += "Registers:\n(All value in hex)\n";
    for(std::size_t i=0; i<(sizeof(regs)/sizeof(*regs)); i++){
        s += std::to_string(i) + ":" + regs[i] + '\n';
    }
    return s;
    // cout<<(sizeof(regs)/sizeof(*regs))<<endl;
}


// Initializes registers from an input file
void Registers::readFile(string fileName){
    ifstream infile;
	infile.open(fileName.c_str());
	if(!infile.good()){
		throw invalid_argument("Failed to open registers_file_input file.");
    }
    int count = 0;
    string line;
    string value;

    while(!infile.eof()){
        // cout<< "start reading" <<endl;
		getline(infile, line);
		// Testing infile (Successful!!)
		// cout<<line.substr(0, 8)<<endl;
		// Check if this is an empty line
		if(line.size()<2){
			continue;
		}

        if(count<10){
            value = line.substr(2);
        }else{
            value = line.substr(3);
        }
        value = remove0x(value);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        regs[count] = value;

        count ++;
	}
} 


// Removes possible 0x before a hex number
string Registers::remove0x(string str){
	if (str.substr(0, 2) == "0x"){
		str = str.substr(2);
	}
	return str;
}