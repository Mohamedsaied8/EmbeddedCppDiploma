test_date: testDate.o Date.o
	g++ -o test_date testDate.o Date.o

testDate.o: testDate.cpp Date.h
	g++ -c testDate.cpp

Date.o: Date.cpp Date.h
	g++ -c Date.cpp
