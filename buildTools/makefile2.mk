C = gcc
CC = g++
OBJS = Date.o testDate.o 
SRC = $(OBJS, .o=.c)

testDate: $(OBJS) 
	$(CC) -o $@ Date.o testDate.o 
	
# Define a pattern rule that compiles every .c file into a .o file
%.o: %.c
	$(C) -c $@ $<

.PHONY: cleanall cleanobj 

cleanall : cleanobj 
	del	*.exe

cleanobj :
	del	*.o

