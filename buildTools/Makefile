C = gcc
CC = g++

testdate: Date.o testDate.o 
	$(CC) -o testdate testDate.o Date.o

testDate.o: testDate.cpp  Date.h
	$(C) -c testDate.cpp

Date.o: Date.cpp Date.h 
	$(C) -c Date.cpp

#Execute even if not updated = execute even if no change
.PHONY: cleanall cleanobj

cleanall : cleanobj 
	del	*.exe

cleanobj :
	del	*.o


