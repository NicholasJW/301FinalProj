#include "ASMParser.h"

/* This class reads in a MIPS assembly file and checks its syntax.  If
 * the file is syntactically correct, this class will retain a list 
 * of Instructions (one for each instruction from the file).  This
 * list of Instructions can be iterated through.
 */

// Specify a text file containing MIPS assembly instructions. Function
// checks syntactic correctness of file and creates a list of Instructions.
ASMParser::ASMParser(string filename)
{
  Instruction i;
  myFormatCorrect = true;

  // testing
  // myLabelAddress = 0x400000;

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }

  else{
    string line;

    while( getline(in, line)){
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


// Iterator that returns the next instruction in the list of instructions
Instruction ASMParser::getNextInstruction()
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }
  
  Instruction i;
  return i;

}


// Decomposes a line of assembly code into strings for the opcode field and operands, 
// checking for syntax errors and counting the number of operands.
void ASMParser::getTokens(string line, string &opcode, string *operand, int &numOperands)
{
    // locate the start of a comment
    string::size_type idx = line.find('#');
    if (idx != string::npos)                  // found a ';'
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

    // testing
    // for(int i = 0; i < 3; i++){
    int i = 0;

    while(p < len){
      while ( p < len && isWhitespace(line.at(p)))
         p++;

      // operand may start
      bool flag = false;

      while (p < len && !isWhitespace(line.at(p))) {
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
  ((idx2 - idx) < 2 )){
        // no () found
    }

    else{ // split string
      string offset = operand[numOperands-1].substr(0,idx);
      string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);
      
      operand[numOperands-1] = offset;
      operand[numOperands] = regStr;
      numOperands++;
    }
    
    

    // ignore anything after the whitespace after the operand
    return;
}


// Returns true if s represents a valid decimal integer
bool ASMParser::isNumberString(string s)
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


// Converts a string to an integer.  Assumes s is something like "-231" and produces -231
int ASMParser::cvtNumString2Number(string s)
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
    

// Given an Opcode, a string representing the operands, and the number of operands, 
// breaks operands apart and stores fields into Instruction.
bool ASMParser::getOperands(Instruction &i, Opcode o, string *operand, int operand_count)
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
    if(isNumberString(operand[imm_p])){
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
  return false;
    }
    else{ 
      if(opcodes.isIMMLabel(o)){

        // Debugging
        // cout<< "check" << endl;
        // Assign the immediate field an address
        // imm = cvtNumString2Number(operand[imm_p]);
        // imm = myLabelAddress;
        // cout<< operand[imm_p] <<endl;
        imm = strtol(operand[imm_p].substr(2).c_str(), NULL, 16);
          // cout<< imm <<endl;
          // myLabelAddress += 4;  // increment the label generator
      }
      else  // There is an error
        return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


// Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding of that instruction
string ASMParser::encode(Instruction i){
 Opcode opcode = i.getOpcode(); //get opcode of instruction
 
 OpcodeTable opTable;
 InstType instructionType = opTable.getInstType(opcode);
 
 string binaryEncoding;

 if(instructionType == RTYPE){
   binaryEncoding = rtypeEncoding(i);
 }  
 else if(instructionType == ITYPE){
   binaryEncoding = itypeEncoding(i);
 }  
 else{
   binaryEncoding = jtypeEncoding(i);
 }
  
  return binaryEncoding;

}


// Returns the r-type encoding as a string given an instruction
string ASMParser::rtypeEncoding(Instruction i){
  Opcode opcode = i.getOpcode();
  int rsDecimal = i.getRS();
  int rtDecimal = i.getRT();
  int rdDecimal = i.getRD();
  int shamtDecimal = i.getImmediate();
 
  OpcodeTable opTable;
  string encoding;

  string opcodeBinary = opTable.getOpcodeField(opcode);
  string rsBinary = convertToBinary(rsDecimal,5);
  string rtBinary = convertToBinary(rtDecimal,5);
  string rdBinary = convertToBinary(rdDecimal,5);
  string functBinary = opTable.getFunctField(opcode);
  string shamtBinary = convertToBinary(shamtDecimal,5);

  encoding = opcodeBinary + rsBinary + rtBinary + rdBinary + shamtBinary + functBinary;
  
  return encoding;
   
}


// Returns the i-type encoding as a string given an instruction
string ASMParser::itypeEncoding(Instruction i){
  Opcode opcode = i.getOpcode();
  int rsDecimal = i.getRS();
  int rtDecimal = i.getRT();
  int immediateDecimal = i.getImmediate();

  string encoding;
  OpcodeTable opTable;

  string opcodeBinary = opTable.getOpcodeField(opcode);
  string rsBinary = convertToBinary(rsDecimal,5);
  string rtBinary = convertToBinary(rtDecimal,5);
  string immediateBinary = convertToBinary(immediateDecimal,16);

  encoding = opcodeBinary + rsBinary + rtBinary + immediateBinary;
  
  return encoding;
   
}


// Returns the j-type encoding as a string given an instruction
string ASMParser::jtypeEncoding(Instruction i){
  Opcode opcode = i.getOpcode();
  int addressDecimal = i.getImmediate();
  // testing
  // cout << std::hex << addressDecimal << endl;
  
  // cout << std::to_string(addressDecimal) << endl;
  OpcodeTable opTable;
  string encoding;

  string opcodeBinary = opTable.getOpcodeField(opcode);
  string addressBinary = convertToBinary(addressDecimal,32);
  addressBinary = addressBinary.substr(4, 26);
  // testing
  // addressBinary = addressBinary.substr(0, addressBinary.size()-6); //changed from -2 to -4
  // addressBinary = addressBinary.substr(6);
  // addressBinary = "000000" + addressBinary; //changed from "00" to "0000"
  encoding = opcodeBinary + addressBinary;
  
  return encoding;  
}


// Converts a decimal number to its binary equivalent and returns it as a string.
string ASMParser::convertToBinary(int decimal, unsigned int length){
  bool negative = false;
  if(decimal < 0){
    decimal = 0-decimal;
    negative = true;
  }

  int number = decimal;
  string binary = "";
  int append = 0;

  while(binary.length() < length){
    append = number % 2;
    number = number/2;
    if(append == 1){
      binary = "1" + binary;
    }
    else{
      binary = "0" + binary;
    }
  }

  //if the number is negative return the two's complement version.
  if(negative){
    for(unsigned int i = 0; i < binary.length(); i++){
      if(binary[i] == '1'){
        binary[i] = '0';
      }
      else if(binary[i] == '0'){
        binary[i] = '1';
      }
    }

  bool add = true;
  int j = binary.length()-1;
    while (add == true && j >= 0){
      if(binary[j] == '0'){
        binary[j] = '1';
        add = false;
      } else {
        binary[j] = '0';
        j--;
      }
    }
  } 
  
  return binary;

}

