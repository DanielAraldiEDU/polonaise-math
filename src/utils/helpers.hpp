/*

Trabalho M1.
Estudades: Daniel Sansão Araldi e Rafael Mota Alves.

*/

#include <iostream>

using namespace std;

template<typename T>
void show(Stack<T> stack) {
  T value;
  while (pop(stack, value)) cout << value;
}

template<typename T>
void show(Queue<T> queue) {
  T value;
  while (remove(queue, value)) cout << value;
}

template<typename T>
bool isLetter(T value) {
  return (value >= 65 && value <= 90) || (value >= 97 && value <= 122);
}

template<typename T>
bool isNumber(T value) {
  return value >= 48 && value <= 57;
}

template<typename T>
bool isOperator(T value) {
  return (value >= 40 && value <= 43) || value == 45 || value == 47 || value == 94;
}

template<typename T>
bool isOpenParenthese(T value) {
  return value == 40;
}

template<typename T>
bool isCloseParenthese(T value) {
  return value == 41;
}

template<typename T>
bool isParentheses(T value) {
  return isOpenParenthese(value) || isCloseParenthese(value);
}

double pow(double base, double exponent) {
  const int length = exponent;
  const double decimalValue = exponent - length;
  const double auxiliarBase = base;
  
  for (int index = 0; index < length; index++) {
    if (index != 0) base *= auxiliarBase;
  };

  if (decimalValue != 0) base *= (auxiliarBase * decimalValue);
  
  return base;
}
