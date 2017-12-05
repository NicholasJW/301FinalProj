#this is a makefile

OBJS = main.o FileReader.o InstructionMem.o ASMParser.o Instruction.o Opcode.o RegisterTable.o DataMem.o Registers.o Processor.o ControlLine.o ProgramCounter.o ALU.o MUX.o SLTwo.o MainControl.o SignExtend.o ALUControl.o

CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main : $(OBJS)
	$(CC) $(LFLAGS) -o main $(OBJS)

main.o : main.cpp FileReader.o InstructionMem.o DataMem.o Registers.o Processor.o
	$(CC) $(CFLAGS) main.cpp

FileReader.o : FileReader.cpp FileReader.h
	$(CC) $(CFLAGS) FileReader.cpp

InstructionMem.o : InstructionMem.h InstructionMem.cpp ASMParser.o
	$(CC) $(CFLAGS) InstructionMem.cpp

ASMParser.o: Instruction.o RegisterTable.o Opcode.o ASMParser.cpp ASMParser.h
	$(CC) $(CFLAGS) ASMParser.cpp

Instruction.o: Opcode.o RegisterTable.o Instruction.cpp Instruction.h
	$(CC) $(CFLAGS) Instruction.cpp

RegisterTable.o: RegisterTable.cpp RegisterTable.h
	$(CC) $(CFLAGS) RegisterTable.cpp

Opcode.o: Opcode.cpp Opcode.h
	$(CC) $(CFLAGS) Opcode.cpp

DataMem.o : DataMem.cpp DataMem.h
	$(CC) $(CFLAGS) DataMem.cpp

Registers.o : Registers.cpp Registers.h
	$(CC) $(CFLAGS) Registers.cpp

Processor.o : ControlLine.o ProgramCounter.o ALU.o MUX.o SLTwo.o MainControl.o SignExtend.o ALUControl.o Processor.cpp Processor.h
	$(CC) $(CFLAGS) Processor.cpp

ControlLine.o : ControlLine.cpp ControlLine.h
	$(CC) $(CFLAGS) ControlLine.cpp

ProgramCounter.o : ProgramCounter.cpp ProgramCounter.h
	$(CC) $(CFLAGS) ProgramCounter.cpp

ALU.o : ALU.cpp ALU.h
	$(CC) $(CFLAGS) ALU.cpp

MUX.o : MUX.cpp MUX.h
	$(CC) $(CFLAGS) MUX.cpp

SLTwo.o : SLTwo.cpp SLTwo.h
	$(CC) $(CFLAGS) SLTwo.cpp

MainControl.o: MainControl.cpp MainControl.h
	$(CC) $(CFLAGS) MainControl.cpp

SignExtend.o: SignExtend.cpp SignExtend.h
	$(CC) $(CFLAGS) SignExtend.cpp

ALUControl.o: ALUControl.cpp ALUControl.h
	$(CC) $(CFLAGS) ALUControl.cpp

clean : 
	rm -f *.o main