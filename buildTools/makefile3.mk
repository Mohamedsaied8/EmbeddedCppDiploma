CC = g++
C = gcc

test_date: testDate.o Date.o
	$(CC) -o test_date testDate.o Date.o

testDate.o: testDate.cpp Date.h
	$(C) -c testDate.cpp

Date.o: Date.cpp Date.h
	$(C) -c Date.cpp
