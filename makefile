#this is a makefile

#TODO : Keep adding objects to this macro
OBJS = FileReader.o main.o InstructionMem.o DataMem.o Registers.o ControlLine.o ProgramCounter.o ALU.o MUX.o SLTwo.o MainControl.o SignExtend.o ALUControl.o

CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o : main.cpp FileReader.o InstructionMem.o DataMem.o Registers.o Processor.o
	$(CC) $(CFLAGS) main.cpp

FileReader.o : FileReader.cpp FileReader.h
	$(CC) $(CFLAGS) FileReader.cpp

#TODO : Keep adding objects to the dependency of Instruction Memory object
InstructionMem.o : InstructionMem.h InstructionMem.cpp
	$(CC) $(CFLAGS) InstructionMem.cpp

DataMem.o : DataMem.cpp DataMem.h
	$(CC) $(CFLAGS) DataMem.cpp

Registers.o : Registers.cpp Registers.h
	$(CC) $(CFLAGS) Registers.cpp

#TODO : Keep adding objects to the dependency of Processor object
Processor.o : Processor.cpp Processor.h InstructionMem.o DataMem.o Registers.o ControlLine.o ProgramCounter.o ALU.o MUX.o SLTwo.o MainControl.o SignExtend.o ALUControl.o
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