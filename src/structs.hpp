#include <iostream>

using namespace std;

#define LENGTH 1000 

template<typename T> 
struct Stack {
    T array[LENGTH];
    int topLevel;
};
