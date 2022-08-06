C = gcc
CC = g++
SRC = Date.cpp testDate.cpp
OBJS = Date.o testDate.o 

testDate: $(OBJS) 
	$(CC) -o testDate Date.o testDate.o 
	
# Define a pattern rule that compiles every .c file into a .o file
%.o: %.c
	$(CC) -c $@ $<

.PHONY: cleanall cleanobj 

cleanall : cleanobj 
	del	*.exe

cleanobj :
	del	*.o

