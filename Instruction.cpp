#include "Instruction.h"

/* This class provides an internal representation for a MIPS assembly instruction.
 * Any of the fields can be queried.  Additionally, the class stores a 32 bit binary
 * encoding of the MIPS instruction.
 */

Instruction::Instruction()
{
  myOpcode = UNDEFINED;
  myRS = myRT = myRD = NumRegisters;
}


// You can specify all the fields to initialize the Instruction
Instruction::Instruction(Opcode op, Register rs, Register rt, Register rd, int imm)
{
  setValues(op, rs, rt, rd, imm);
}


// You can specify all the fields to initialize the Instruction
void Instruction::setValues(Opcode op, Register rs, Register rt, Register rd, int imm)
{

  myOpcode = op;
  if(op < 0 || op >= UNDEFINED)
    myOpcode = UNDEFINED;

  myRS = rs;
  if(rs < 0 || rs >= NumRegisters)
    myRS = NumRegisters;

  myRT = rt;
  if(rt < 0 || rt >= NumRegisters)
    myRT = NumRegisters;

  myRD = rd;
  if(rd < 0 || rd >= NumRegisters)
    myRD = NumRegisters;

  myImmediate = imm;

  // testing
  //  if(!( (imm & 0xFFFF0000) << 1))  // make sure it has nothing in upper 16 bits
  //    myImmediate = imm;  

}


// Returns a string which represents all of the fields
string Instruction::getString() 
{
  stringstream s ;
  s << "OP: \t" << myOpcode << "\t" << "RD: " << myRD << "\t" << 
    "RS: " << myRS << "\t" << "RT: " << "\t" << myRT << "\t" <<
    "Imm: " << myImmediate;
  
  return s.str();
  
}

