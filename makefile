#this is a makefile

#TODO : Keep adding objects to this macro
OBJS = FileReader.o main.o InstructionMem.o DataMem.o Registers.o FileWriter.o ProgramCounter.o ALU.o Mux.o SLTwo.o MainControl.o SignExtend.o ALUControl.o

CC = g++
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
InstructionMem.o : InstructionMem.cpp InstructionMem.h
	$(CC) $(CFLAGS) InstructionMem.cpp

#TODO : Keep adding objects to the dependency of Instruction Data Memory object
DataMem.o : DataMem.cpp DataMem.h
	$(CC) $(CFLAGS) DataMem.cpp

#TODO : Keep adding objects to the dependency of Instruction Registers object
Registers.o : Registers.cpp Registers.h
	$(CC) $(CFLAGS) Registers.cpp

#TODO : Keep adding objects to the dependency of Processor object
Processor.o : Processor.cpp Processor.h InstructionMem.o DataMem.o Registers.o FileWriter.o ProgramCounter.o ALU.o Mux.o SLTwo.o MainControl.o SignExtend.o ALUControl.o
	$(CC) $(CFLAGS) Processor.cpp

FileWriter.o : FileWriter.cpp FileWriter.h
	$(CC) $(CFLAGS) FileWriter.cpp

ProgramCounter.o : ProgramCounter.cpp ProgramCounter.h
	$(CC) $(CFLAGS) ProgramCounter.cpp

ALU.o: ALU.cpp ALU.h
	$(CC) $(CCFLAGS) ALU.cpp

Mux.o: Mux.cpp Mux.h
	$(CC) $(CCFLAGS) Mux.cpp

SLTwo.o : SLTwo.cpp SLTwo.h
	$(CC) $(CCFLAGS) SLTwo.cpp

MainControl.o: MainControl.cpp MainControl.h
	$(CC) $(CCFLAGS) MainControl.cpp

SignExtend.o: SignExtend.cpp SignExtend.h
	$(CC) $(CCFLAGS) SignExtend.cpp

ALUControl.o: ALUControl.cpp ALUControl.h
	$(CC) $(CCFLAGS) ALUControl.cpp

clean : 
	\rm *.o main