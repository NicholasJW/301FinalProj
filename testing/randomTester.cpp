#include <iostream>
#include <sstream>
#include <string>

using namespace std;
int main(){
    long h = 0xeeeeeeee;
    stringstream ss;
    ss << std::hex << h;
    cout << ss.str() << endl;
}