#include "DataMem.h"

DataMem::DataMem(){

}

void DataMem::readFile(string fileName){
	ifstream infile;
	infile.open(fileName.c_str());
	if(!infile.good()){
		throw invalid_argument("Failed to open memory_contents_input file.");
	}
	string line;
	string address;
	string content;

	while(!infile.eof()){
		getline(infile, line);
		// Testing infile (Successful!!)
		// cout<<line.substr(0, 8)<<endl;
		if(line.substr(0, 2) == "0x"){
			int length = line.size();
			line = line.substr(2, length-2);
		}
		if(line.substr(9, 2) == "0x"){
			int length = line.size();
			line = line.substr(0, 9) + line.substr(11, 8);
		}

		address = line.substr(0,8);
		content = line.substr(9,8);


		// cout<<address<<":"<<content<<endl;
		write(address, content);
	}
	infile.close();

}

string DataMem::read(string address){
	address = remove0x(address);
	if(data.count(address) == 1){
		return data.at(address);
	}else{
		throw invalid_argument("memory_not_found");
	}
}

void DataMem::write(string address, string content){
	address = remove0x(address);
	content = remove0x(content);
	if (data.count(address) == 0){
		data.insert(std::pair<string, string>(address, content));
	} else {
		data.at(address) = content;
	}
	
}


void DataMem::print(){
	map<string, string>::iterator it = data.begin();
	string printLine;
	while(it!=data.end()){
		// if(it->first == ""){
			// break;
		// }
		printLine = it->first + ":" + it->second;
		cout<<printLine<<endl;
		it++;
	}
}

string DataMem::remove0x(string str){
	if (str.size() == 10){
		str = str.substr(2, 8);
	}
	return str;
}