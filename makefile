#this is a makefile

#TODO : Keep adding objects to this macro
OBJS = FileReader.o main.o 

CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main : $(OBJS)
    $(CC) $(LFLAGS) $(OBJS) -o main

#TODO : Keep adding objects to the dependency of main object
main.o : main.cpp FileReader.o InstructionMem.o DataMem.o Registers.o
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

clean : 
	\rm *.o main