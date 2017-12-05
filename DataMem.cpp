#include "DataMem.h"

DataMem::DataMem(){

}

string DataMem::inputs(){
	stringstream in;
	in << "Inputs: ";
	in << "\nMemory Address: " << address;
	in << "\nData to write: " << writeData;
	return in.str();
}

string DataMem::outputs(){
	return "0x" + readData;
}

string DataMem::read(string address){
	address = remove0x(address);
	// cout << address << endl;
	std::transform(address.begin(), address.end(), address.begin(), ::tolower);
	if(data.count(address) == 1){
		return data.at(address);
	}else{
		throw invalid_argument("memory_not_found");
	}
}

void DataMem::write(string address, string content){
	address = remove0x(address);
	std::transform(address.begin(), address.end(), address.begin(), ::tolower);
	content = remove0x(content);
	std::transform(content.begin(), content.end(), content.begin(), ::tolower);
	if (data.count(address) == 0){
		data.insert(std::pair<string, string>(address, content));
	} else {
		data.at(address) = content;
	}
	
}


string DataMem::toString(){
	string s = "\n\n======================================\n";
    s += "Data Memmory:\n(All value in hex)\n";
	map<string, string>::iterator it = data.begin();
	while(it!=data.end()){
		// if(it->first == ""){
			// break;
		// }
		s += it->first + " : " + it->second + '\n';
		it++;
	}
	return s;
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
		//Check if this is an empty line
		if(line.size()<2){
			continue;
		}

		if(line.substr(0, 2) == "0x"){
			// int length = line.size();
			line = line.substr(2);
		}
		if(line.substr(9, 2) == "0x"){
			// int length = line.size();
			line = line.substr(0, 9) + line.substr(11);
		}

		address = line.substr(0,8);
		std::transform(address.begin(), address.end(), address.begin(), ::tolower);
		content = line.substr(9,8);
		std::transform(content.begin(), content.end(), content.begin(), ::tolower);


		// cout<<address<<":"<<content<<endl;
		write(address, content);
	}
	infile.close();
}

string DataMem::remove0x(string str){
	if (str.substr(0,2) == "0x"){
		str = str.substr(2);
	}
	return str;
}

// Testing
// int main(int argc, char *argv[]){
// 	string s = "AsaaJSDaa";
// 	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
// 	cout<<s<<endl;
// }