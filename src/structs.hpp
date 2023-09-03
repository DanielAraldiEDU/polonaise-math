/*

Trabalho M1.
Estudades: Daniel Sansão Araldi e Rafael Mota Alves.

*/

#include <iostream>

using namespace std;

#define LENGTH 1000 

template<typename T> 
struct Stack {
  T array[LENGTH];
  int topLevel;
};

template<typename T> 
struct Queue {
  T array[LENGTH];
  int start, end, length;
};
