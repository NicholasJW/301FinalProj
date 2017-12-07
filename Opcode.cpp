#include "Opcode.h"

using namespace std;

/* Stores different MIPS instructions into a table containing the instructions'
 * opcodes, expected operands, and other fields
 */

// Initializes all the fields for every instruction in Opcode enum
OpcodeTable::OpcodeTable()
{
  myArray[ADD].name = "add";  myArray[ADD].numOps = 3;   myArray[ADD].rdPos = 0;  myArray[ADD].rsPos = 1;  myArray[ADD].rtPos = 2;   myArray[ADD].immPos = -1;  myArray[ADD].instType = RTYPE; myArray[ADD].op_field = "000000"; myArray[ADD].funct_field = "100000";
 
  //Supported MIPS instructions
  myArray[SUB].name = "sub"; myArray[SUB].numOps = 3; myArray[SUB].rdPos = 0; myArray[SUB].rsPos = 1; myArray[SUB].rtPos = 2; myArray[SUB].immPos = -1; myArray[SUB].instType = RTYPE; myArray[SUB].op_field = "000000"; myArray[SUB].funct_field = "100010";
  myArray[ADDI].name = "addi";  myArray[ADDI].numOps = 3;   myArray[ADDI].rdPos = -1;  myArray[ADDI].rsPos = 1;  myArray[ADDI].rtPos = 0;   myArray[ADDI].immPos = 2;  myArray[ADDI].instType = ITYPE; myArray[ADDI].op_field = "001000";
  myArray[MULT].name = "mult";  myArray[MULT].numOps = 2;   myArray[MULT].rdPos = -1;  myArray[MULT].rsPos = 0;  myArray[MULT].rtPos = 1;   myArray[MULT].immPos = -1;  myArray[MULT].instType = RTYPE; myArray[MULT].op_field = "000000"; myArray[MULT].funct_field = "011000"; 
  myArray[MFLO].name = "mflo";  myArray[MFLO].numOps = 1;   myArray[MFLO].rdPos = 0;  myArray[MFLO].rsPos = -1;  myArray[MFLO].rtPos = -1;   myArray[MFLO].immPos = -1;  myArray[MFLO].instType = RTYPE; myArray[MFLO].op_field = "000000"; myArray[MFLO].funct_field = "010010";
  myArray[SRA].name = "sra";  myArray[SRA].numOps = 3;   myArray[SRA].rdPos = 0;  myArray[SRA].rsPos = -1;  myArray[SRA].rtPos = 1;   myArray[SRA].immPos = 2;  myArray[SRA].instType = RTYPE; myArray[SRA].op_field = "000000"; myArray[SRA].funct_field = "000011";
  myArray[SLT].name = "slt";  myArray[SLT].numOps = 3;   myArray[SLT].rdPos = 0;  myArray[SLT].rsPos = 1;  myArray[SLT].rtPos = 2;   myArray[SLT].immPos = -1;  myArray[SLT].instType = RTYPE; myArray[SLT].op_field = "000000"; myArray[SLT].funct_field = "101010";
  myArray[LB].name = "lb";  myArray[LB].numOps = 3;   myArray[LB].rdPos = -1;  myArray[LB].rsPos = 2;  myArray[LB].rtPos = 0;   myArray[LB].immPos = 1;  myArray[LB].instType = ITYPE; myArray[LB].op_field = "100000";
  myArray[LW].name = "lw"; myArray[LW].numOps=3; myArray[LB].rdPos = -1; myArray[LW].rsPos = 2; myArray[LW].rtPos = 0; myArray[LW].immPos = 1; myArray[LW].instType = ITYPE; myArray[LW].op_field = "100011";
  myArray[SW].name = "sw"; myArray[SW].numOps=3; myArray[SW].rdPos = -1; myArray[SW].rsPos = 2; myArray[SW].rtPos = 0; myArray[SW].immPos = 1; myArray[SW].immLabel = true; myArray[SW].instType = ITYPE; myArray[SW].op_field = "101011";
  myArray[BEQ].name = "beq"; myArray[BEQ].numOps=3; myArray[BEQ].rdPos = -1; myArray[BEQ].rsPos = 0; myArray[BEQ].rtPos = 1; myArray[BEQ].immPos = 2; myArray[BEQ].immLabel = true; myArray[BEQ].instType = ITYPE; myArray[BEQ].op_field = "000100";
  myArray[J].name = "j";  myArray[J].numOps = 1;   myArray[J].rdPos = -1;  myArray[J].rsPos = -1;  myArray[J].rtPos = -1;   myArray[J].immPos = 0;  myArray[J].immLabel = true; myArray[J].instType = JTYPE; myArray[J].op_field = "000010";
}


// Given a valid MIPS assembly mnemonic, returns an Opcode which represents a 
// template for that instruction.
Opcode OpcodeTable::getOpcode(string str)
{
  for(int i = 0; i < (int)UNDEFINED; i++){
    if(myArray[i].name == str){
      return (Opcode)i;
    }
  }
  return UNDEFINED;
}


// Given an Opcode, returns number of expected operands.
int OpcodeTable::numOperands(Opcode o)
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].numOps;
}


// Given an Opcode, returns the position of RS field.  If field is not
// appropriate for this Opcode, returns -1.
int OpcodeTable::RSposition(Opcode o)
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rsPos;
}


// Given an Opcode, returns the position of RT field.  If field is not
// appropriate for this Opcode, returns -1.
int OpcodeTable::RTposition(Opcode o)
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rtPos;
}


// Given an Opcode, returns the position of RD field.  If field is not
// appropriate for this Opcode, returns -1.
int OpcodeTable::RDposition(Opcode o)
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].rdPos;
}


// Given an Opcode, returns the position of IMM field.  If field is not
// appropriate for this Opcode, returns -1.
int OpcodeTable::IMMposition(Opcode o)
{
  if(o < 0 || o >= UNDEFINED)
    return -1;

  return myArray[o].immPos;
}


// Given an Opcode, returns instruction type.
InstType OpcodeTable::getInstType(Opcode o)
{
  if(o < 0 || o > UNDEFINED)
    return (InstType)-1;
  return myArray[o].instType;
}


// Given an Opcode, returns a string representing the binary encoding of the opcode
// field.
string OpcodeTable::getOpcodeField(Opcode o)
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].op_field;
}


// Given an Opcode, returns a string representing the binary encoding of the function
// field.
string OpcodeTable::getFunctField(Opcode o)
{
  if(o < 0 || o > UNDEFINED)
    return string("");
  return myArray[o].funct_field;
}

// Given an Opcode, returns true if instruction expects a label in the instruction.
// See "J".
bool OpcodeTable::isIMMLabel(Opcode o)
{
  if(o < 0 || o > UNDEFINED)
    return false;
  return myArray[o].immLabel;
}
