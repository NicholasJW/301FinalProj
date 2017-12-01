#include "ASMParser.h"
using namespace std;  


ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
{
  Instruction i;
  myFormatCorrect = true;

  myLabelAddress = 0x400000;

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }
  else{
    string line;
    while( getline(in, line)){
      // cout << line << endl;
      i.setPlain(line);
      string opcode("");
      string operand[80];
      int operand_count = 0;

      getTokens(line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
	// No opcode but operands
	myFormatCorrect = false;
	break;
      }

      Opcode o = opcodes.getOpcode(opcode);      
      if(o == UNDEFINED){
	// invalid opcode specified
	myFormatCorrect = false;
	break;
      }

      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
	myFormatCorrect = false;
	break;
      }

      string encoding = encode(i);
      i.setEncoding(encoding);

      myInstructions.push_back(i);

    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }
  
  Instruction i;
  return i;

}

void ASMParser::getTokens(string line,
			       string &opcode,
			       string *operand,
			       int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos) // found a ';'
	line = line.substr(0,idx);
    int len = line.length();
    opcode = "";
    numOperands = 0;

    if (len == 0) return;
    int p = 0; // position in line

    // line.at(p) is whitespace or p >= len
    while (p < len && isWhitespace(line.at(p)))
	p++;
    // opcode starts
    while (p < len && !isWhitespace(line.at(p)))
    {
	opcode = opcode + line.at(p);
	p++;
    }
    //    for(int i = 0; i < 3; i++){
    int i = 0;
    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
	p++;

      // operand may start
      bool flag = false;
      while (p < len && !isWhitespace(line.at(p)))
	{
	  if(line.at(p) != ','){
	    operand[i] = operand[i] + line.at(p);
	    flag = true;
	    p++;
	  }
	  else{
	    p++;
	    break;
	  }
	}
      if(flag == true){
	numOperands++;
      }
      i++;
    }

    
    idx = operand[numOperands-1].find('(');
    string::size_type idx2 = operand[numOperands-1].find(')');
    
    if (idx == string::npos || idx2 == string::npos ||
	((idx2 - idx) < 2 )){ // no () found
    }
    else{ // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);
      
      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }
    
    

    // ignore anything after the whitespace after the operand
    // We could do a further look and generate an error message
    // but we'll save that for later.
    return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
    int len = s.length();
    if (len == 0) return false;
    if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
    {
	// check remaining characters
	for (int i=1; i < len; i++)
	{
	    if (!isdigit(s.at(i))) return false;
	}
	return true;
    }
    return false;
}


int ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
    if (!isNumberString(s))
    {
	cerr << "Non-numberic string passed to cvtNumString2Number"
		  << endl;
	return 0;
    }
    int k = 1;
    int val = 0;
    for (int i = s.length()-1; i>0; i--)
    {
	char c = s.at(i);
	val = val + k*((int)(c - '0'));
	k = k*10;
    }
    if (isSign(s.at(0)))
    {
	if (s.at(0) == '-') val = -1*val;
    }
    else
    {
	val = val + k*((int)(s.at(0) - '0'));
    }
    return val;
}
		

bool ASMParser::getOperands(Instruction &i, Opcode o, 
			    string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }
  
  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
	return false;
    }
    else{ 
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
	// Assign the immediate field an address
	imm = myLabelAddress;
	myLabelAddress += 4;  // increment the label generator
      }
      else  // There is an error
	return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  // Your code here
  string result = "";
  result += opcodes.getOpcodeField(i.getOpcode()); //append opcode
  if (opcodes.getInstType(i.getOpcode()) == RTYPE) { // RTYPE
    int rs = i.getRS();
    string bin = toBin(rs);
    result += bin; //append rs
    int rt = i.getRT();
    bin = toBin(rt);
    result += bin; //append rt
    int rd = i.getRD();
    bin = toBin(rd);
    result += bin; //append rd
    int imm = i.getImmediate();
    bin = toBin(imm);
    result += bin; //append immediate value
    string op = opcodes.getFunctField(i.getOpcode());
    result += op; //append function code
  } else if (opcodes.getInstType(i.getOpcode()) == ITYPE) { // ITYPE
    int rs = i.getRS();
    result += toBin(rs); //append rs
    int rt = i.getRT();
    result += toBin(rt); //append rt
    int imm = i.getImmediate();
    result += toBinaryImm(imm); //append immediate value
  } else if (opcodes.getInstType(i.getOpcode()) == JTYPE) { // JTYPE
    string address = toBinaryIns(myLabelAddress);
    address.insert(0, "00");
    address.erase(address.end() - 1);
    address.erase(address.end() - 1);
    //address += "0000"; //address
    result += address;
  } else { // UNDEFIND
    result = "The instruction is undefined.";
  }
  return result;
}

string ASMParser::toBin(int a) 
  // Given an decimal int, converts to 5 characters binary string.
  // parse the register number from decimal to binary
  // input: int value between 0 and 31 inclusive.
  // output: binary string representation of the int value
{
  string result = "";
  if (a <= 31 && a >= 0) { //input int meets requirement
    while (a > 0) {
      int bit = a % 2;
      char temp;
      temp = bit + '0'; //convert integer bit to char
      result = temp + result;
      a = a/2;
    }
  } else {

  }
  while (result.size() < 5) {
    result.insert(0, "0");
  }
  return result;
}

string ASMParser::toBinaryImm(int a)  
  // Given an decimal int, converts to 16 characters binary string.
  // parse the immediate value from decimal to binary
  // input: int value (convertable to 16 bits)
  // output: binary string representation of the int value
{
  // cout<< a << endl;
  if (a >= 0) {
    string result = "";
    while (a > 0) {
      int bit = a % 2;
      char temp;
      temp = bit + '0';
      result = temp + result;
      a = a/2;
    } 
    while (result.size() < 16) {
      result.insert(0, "0");
    }
    return result;
  } else {
    a = 0 - a;
    // cout <<a << endl;
    string result = "";
    while (a > 0) {
      int bit = a % 2;
      char temp;
      temp = bit + '0';
      result = temp + result;
      a = a/2;
    } 
    while (result.size() < 16) {
      result.insert(0, "0");
    }
      string temp = "0000000000000000";

    for (int i = 0; i < 16; i++) {
      if (result[i] == '1') {
        temp[i] = '0';
      } else {
        temp[i] = '1';
      }
    }

    string temp2 = "0000000000000001";
    result = add(temp, temp2);
    return result;
  }
}

string ASMParser::add(string operand1, string operand2) {
  char carry = '0'; //carry bit
  string result = "0000000000000000";
  for (int i = 16; i > -1; i--) {
    //cout << i << carry << myOperand1[i] << myOperand2[i] << endl;
    if (operand1[i] == '0' && operand2[i] == '0' && carry == '0') {
      //ignore overflow

      //cout << i << "\tcarry = 0 result = 0" << endl;
      result[i] = '0';
      carry = '0';
    } else if ((operand1[i] == '0' && operand2[i] == '0' && carry == '1')
      || (operand1[i] == '0' && operand2[i] == '1' && carry == '0')
      || (operand1[i] == '1' && operand2[i] == '0' && carry == '0')) {
      //cout << i << "\tcarry = 0 result = 1" << endl;
      result[i] = '1';
      carry = '0';
    } else if ((operand1[i] == '1' && operand2[i] == '1' && carry == '0')
      || (operand1[i] == '1' && operand2[i] == '0' && carry == '1')
      || (operand1[i] == '0' && operand2[i] == '1' && carry == '1')) {
      //cout << i << "\tcarry = 1 result = 0" << endl;
      result[i] = '0';
      carry = '1';
    } else if (operand1[i] == '1' && operand2[i] == '1' && carry == '1') {
      //cout << i << "\tcarry = 1 result = 1" << endl;
      result[i] = '1';
      carry = '1';
    }
  }
  //cout << "result\t\t" << result << endl;
  return result;
}

string ASMParser::toBinaryIns(int a)  
  // Given an decimal int, converts to 26 characters binary string.
  // parse the address from decimal to binary
  // input: int value (convertable to 26 bits)
  // output: binary string representation of the int value
{
  string result = "";
  while (a > 0) {
    int bit = a % 2;
    char temp;
    temp = bit + '0';
    result = temp + result;
    a = a/2;
  } 
  while (result.size() < 26) {
    result.insert(0, "0");
  }
  return result;
}
