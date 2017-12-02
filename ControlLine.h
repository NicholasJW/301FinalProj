#ifndef __CONTROLLINE_H__
#define __CONTROLLINE_H__

#include<string>
using namespace std;
class ControlLine{
public:
    // Default constructor, set the value to 0x0, name to "control_line", length to -1
    ControlLine(){value = "-1";};

    // Set the name of this cl.
    void setName(string _name){name = _name;};

    // Set the value to specified string, must be represented by a Hex number starting with "0x"
    void setValue(string _value){value = _value;};

    string getValue(){return value;};
    string getName(){return name;};

    //Print out the name and the value of this control line 
    string toString();
private:
    // Name of this control line, must follow the names we have in the project instruction pdf
    string name;

    //Represent the lenth of digits to indicate the control signal, mostly 1, the control line from ALUControl to ALU has 4.
    int length;

    //The string must be represented by a Hex number starting with "0x".
    string value;
    
};
#endif