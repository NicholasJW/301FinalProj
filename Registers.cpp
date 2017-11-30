#include "Registers.h"

Registers::Registers(){

}

string Registers::get(int num){
    if(num>-1 || num<32){
        return regs[num];
    }else{
        throw invalid_argument("register_not_found");
    }
}

void Registers::set(int num, string value){
    if(num>-1 || num<32){
        value = remove0x(value);
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        regs[num] = value;
    }else{
        throw invalid_argument("register_not_found");
    }
}

void Registers::print(){
    for(std::size_t i=0; i<(sizeof(regs)/sizeof(*regs)); i++){
        cout << i << ":" + regs[i] << endl;
    }

    // cout<<(sizeof(regs)/sizeof(*regs))<<endl;
}

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

string Registers::remove0x(string str){
	if (str.size() == 10){
		str = str.substr(2, 8);
	}
	return str;
}