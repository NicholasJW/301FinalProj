#ifndef __OPCODE_H__
#define __OPCODE_H__


#include <iostream>
#include <string>

using namespace std;

/* Stores different MIPS instructions into a table containing the instructions'
 * opcodes, expected operands, and other fields
 */

// Listing of all supported MIPS instructions
enum Opcode {
  ADD, 
  SUB,
  ADDI, 
  MULT,
  MFLO,
  SRA,
  SLT,
  LB,
  LW,
  SW,
  BEQ,
  J, 
  UNDEFINED
};

// Different types of MIPS encodings
enum InstType{
  RTYPE,
  ITYPE,
  JTYPE
};


/* This class represents templates for supported MIPS instructions.  For every supported
 * MIPS instruction, the OpcodeTable includes information about the opcode, expected
 * operands, and other fields.  
 */
class OpcodeTable {
 public:
  OpcodeTable();

  // Given a valid MIPS assembly mnemonic, returns an Opcode which represents a 
  // template for that instruction.
  Opcode getOpcode(std::string str);

  // Given an Opcode, returns number of expected operands.
  int numOperands(Opcode o);

  // Given an Opcode, returns the position of RS/RT/RD/IMM field.  If field is not
  // appropriate for this Opcode, returns -1.
  int RSposition(Opcode o);
  int RTposition(Opcode o);
  int RDposition(Opcode o);
  int IMMposition(Opcode o);

  // Given an Opcode, returns true if instruction expects a label in the instruction.
  // See "J".
  bool isIMMLabel(Opcode o);

  // Given an Opcode, returns instruction type.
  InstType getInstType(Opcode o);

  // Given an Opcode, returns a string representing the binary encoding of the opcode
  // field.
  std::string getOpcodeField(Opcode o);

  // Given an Opcode, returns a string representing the binary encoding of the function
  // field.
  std::string getFunctField(Opcode o);


 private:
  struct OpcodeTableEntry{
    std::string name;
    int numOps;
    int rdPos;
    int rsPos;
    int rtPos;
    int immPos;
    bool immLabel;

    InstType instType;
    std::string op_field;
    std::string funct_field;

    OpcodeTableEntry(){
      numOps = 0; 
      rdPos = rsPos = rtPos = immPos = -1;
      immLabel = false;
    };
  };

  OpcodeTableEntry myArray[UNDEFINED];


};


#endif
