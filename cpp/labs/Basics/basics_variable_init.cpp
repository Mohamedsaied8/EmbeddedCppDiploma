//! \file basics_variable_init.cpp
//! \authors Anas Khedr
//! \brief 
//! \version 0.1
//! \date 06-May-2023
//! \copyright This work is licensed under a Creative Commons Attribution 4.0 International License. Copyright (c) 2023
//!

// Ctrl + Shift + B  to compile

//-------------------------------
// Includes
//-------------------------------
#include <iostream> // include the cout cin functions

//-------------------------------
// Data
//-------------------------------

/// NOTES: cpp Terminology:
// 1. https://careerkarma.com/blog/c-plus-plus-terminolog/
// 2. http://web.cs.ucla.edu/classes/winter05/cs31/lectures/defs.html

///NOTE: basic tutorial: https://cplusplus.com/files/tutorial.pdf

///NOTES: C++11 ins the standard that has been release in 2011, and C++14 in 2014 and so on
// new standard means new modern features in C++, a new standard is released every 3 years

// some POD(Plain Old Data) or trivial(POD has been replaced with trivial as of C++11) variables
float myFloat = 25.75f; // the f at the end is something called suffix, the types and their suffix (https://www.learncpp.com/cpp-tutorial/literals/)
// without suffix any number will be interpreted as a double
int myInt = 31;

struct myStructExample
{
    int intVal;
    float floatVal;
    double doubleVal;
};

myStructExample myStruct;


// different ways to initialize variables

// Default initialization:
int defaultInitialization; // here we let the compiler give the variable the default value, All uninitialized global variables will have 0 as the default
// variables declared in a function has a garbage(undefined) initial value

//Direct initialization:
// This involves initializing a variable with a value in the constructor. For example, int x(10); initializes x with the value 10.
int directInitialization(10);
int directInitialization_2(myInt);

// Copy initialization:
// This involves initializing a variable with a value using the = operator. For example, int x = 10; initializes x with the value 10.
int copyInitialization = 10;
int copyInitialization_2 = myInt;  // also copy initialization but from a another variable
int copyInitialization_3 = myFloat; // the compiler will try to perform an implicit conversion to convert myFloat to an int(it will succeed)
// int copyInitialization_4 = myStruct; // the compiler will try to perform an implicit conversion to convert myStruct to an int(it will fail, can't convert the struct to int[we didn't tell the compiler how to convert])


// Uniform initialization (since C++11):
// This involves initializing a variable using braces {}. For example, int x{10}; also initializes x with the value 10.
int uniformInitialization{10};
int uniformInitialization_2 {myInt};
int uniformInitialization_3 {myFloat};  // this will give you a warning(narrowing conversion of ‘myFloat’ from ‘float’ to ‘int’)
int arr[]{1, 2, 3}; ///NOTE: {} work with any data type in C++, POD or complex


// Aggregate initialization:
myStructExample AggregateInitializedStruct{10, 12.57, 300000};  // the {} can work here as an aggregate initialization
// good read to show the difference between aggregate and uniform initialization https://stackoverflow.com/questions/58993745/aggregate-initialization-vs-uniform-initialization


// List initialization (since C++11):
// This is similar to aggregate initialization, but it allows for more complex initialization of non-aggregate types. For example, std::vector<int> v{1, 2, 3}; initializes a vector with three elements

// Reference initialization:
// This initializes a reference variable to refer to an existing object. For example, int x = 10; int& ref_x = x; initializes a reference variable ref_x to refer to the variable x.

int main()
{
    return 0;
}