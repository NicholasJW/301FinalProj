#include "../Registers.h"

// This is the testing file to test the register memory
int main(int argc, char *argv[]){
    Registers r("../sample_inputs/register2.memory");

    // Test read function
    cout<<r.get(1)<<endl;
    // cout<<r.get(32)<<endl;// Should output error
    
    // Test set function
    r.set(1, "0xffffffff");
    r.set(31, "0xAAAAAAAA");
    r.print();
    return 0;
}