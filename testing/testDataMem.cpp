#include "../DataMem.h"

using namespace std;

int main(){
	DataMem testMem("../sample_inputs/data1.memory");
	// testMem = new DataMem("data1.memory");
	testMem.write("10000044", "00000000");
	// testMem.print();
	cout<<testMem.read("10000044")<<endl;
	//cout<<testMem.read("10000164")<<endl;
	// testMem.read("10101010");

	cout<<"====================="<<endl;

	cout<<testMem.read("0x10000044")<<endl;
	testMem.write("10000118", "0xaaaaaaaa");
	testMem.write("0x10010100", "hihihihi");
	testMem.write("0x100101CC", "00AAAA00");
	testMem.print();
	// delete testMem;
	return 0;
} 