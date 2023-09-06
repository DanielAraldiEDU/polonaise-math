/*

Trabalho M1.
Estudades: Daniel Sansão Araldi e Rafael Mota Alves.

*/

#include <iostream>

using namespace std;

// Transform to Polonaise Notation functions

template<typename T>
int getPrecedenceValue(T operatorValue) {
  switch(operatorValue) {
    case '^': return 3;
    case '*': return 2;
    case '/': return 2;
    case '+': return 1;
    case '-': return 1;
    default: return 0;
  }
}

template<typename T>
void transformPolonaiseNotation(Queue<T> &queue, Queue<T> &resultQueue) {
  Stack<T> stack;
  T queueValue, stackValue;

  initialize(stack);

  while(remove(queue, queueValue)) {
    if (isOperator(queueValue)) {
      if (isCloseParenthese(queueValue)) {
        bool hasNextStackValue = pop(stack, stackValue);
        if (hasNextStackValue) {
          while (hasNextStackValue) {
            if (!isOpenParenthese(stackValue)) insert(resultQueue, stackValue);
            
            if (hasNextStackValue) {
              hasNextStackValue = pop(stack, stackValue);
              if (hasNextStackValue && stackValue == 40) hasNextStackValue = false;
            }
          }
        }
      } else {
        bool hasValue = pop(stack, stackValue);
        if (hasValue) {
          int precedenceValue = getPrecedenceValue(stackValue);
          int precedenceQueueValue = getPrecedenceValue(queueValue);
  
          if (precedenceQueueValue > precedenceValue || isOpenParenthese(queueValue)) {
            push(stack, stackValue);
            push(stack, queueValue);
          } else {
            insert(resultQueue, stackValue);

            bool hasNextStackValue = pop(stack, stackValue);
            if (hasNextStackValue) {
              while (hasNextStackValue) {
                precedenceValue = getPrecedenceValue(stackValue);
                precedenceQueueValue = getPrecedenceValue(queueValue);
                
                if (precedenceQueueValue <= precedenceValue) {
                  insert(resultQueue, stackValue);
                } else {
                  push(stack, stackValue);
                  push(stack, queueValue);
                  hasNextStackValue = false;
                }
  
                if (hasNextStackValue) {
                  hasNextStackValue = pop(stack, stackValue);
                  if (!hasNextStackValue) push(stack, queueValue);
                }
              }
            } else {
              push(stack, queueValue);
            }
          }
        } else {
          push(stack, queueValue);
        }
      }
    } else {
      insert(resultQueue, queueValue);
    }
  }

  if (!queue.length) {
    while (pop(stack, queueValue)) {
      if (!isParentheses(queueValue)) insert(resultQueue, queueValue);
    }
  }
}

// Calculate Polonaise Notation functions

double charToDouble(char number) {
  if (isNumber(number)) return (double)number - 48;
  else return 0;
}

template<typename T>
double handleResultOperation(char operatorValue, T currentNumber, T previousNumber) {
  switch(operatorValue) {
    case '^': return pow(previousNumber, currentNumber);
    case '*': return previousNumber * currentNumber;
    case '/': return previousNumber / currentNumber;
    case '+': return previousNumber + currentNumber;
    case '-': return previousNumber - currentNumber;
    default: return 0;
  }
}

template<typename T>
T calculatePolonaiseNotation(Queue<T> queue) {
  T value;
  Stack<double> stack;
  double currentValue, previousValue, resultValue;

  initialize(stack);

  while(remove(queue, value)) {
    if (isOperator(value)) {
      pop(stack, currentValue);
      pop(stack, previousValue);
      resultValue = handleResultOperation(value, currentValue, previousValue);
      push(stack, resultValue);
    } else {
      resultValue = charToDouble(value);
      push(stack, resultValue);
    }
  }
  
  pop(stack, resultValue);

  return resultValue;
}

// Transform to Upper Case all letters of the notation

template<typename T>
void toUpperNotation(Queue<T> &queue) {
  Queue<T> auxiliarQueue;
  T value;

  initialize(auxiliarQueue);

  while(remove(queue, value)) {
    if (isLetter(value)) value = toupper(value);
    insert(auxiliarQueue, value);
  }

  while(remove(auxiliarQueue, value)) insert(queue, value);
}

// Change Incognitos to Numbers

int getCharIndex(char value) {
  if (isLetter(value)) return (int)value - 65;
  else return 0;
}

template<typename T>
bool changeIncognitosToNumbers(Queue<T> &queue) {
  Queue<T> auxiliarQueue;
  T value;
  char letters[26];

  for (int index = 0; index < AMOUNT_LETTERS; index++) letters[index] = ' ';

  initialize(auxiliarQueue);

  while(remove(queue, value)) {
    if (isLetter(value)) {
      int charIndex = getCharIndex(value);
      if (letters[charIndex] == ' ') letters[charIndex] = value;
    }
    insert(auxiliarQueue, value);
  }

  while(remove(auxiliarQueue, value)) insert(queue, value);

  for (int index = 0; index < AMOUNT_LETTERS; index++) {
    if (letters[index] != ' ') {
      T auxiliarValue;
      cout << "Value to the letter " << letters[index] << " (single digit (0–9)): ";
      cin >> auxiliarValue;
      
      if (isNumber(auxiliarValue)) {
        while(remove(queue, value)) {
          if (isLetter(value) && value == letters[index]) value = auxiliarValue;
          insert(auxiliarQueue, value);
        }
        while(remove(auxiliarQueue, value)) insert(queue, value);
      } else {
        cout << "You entered an invalid value!" << endl;
        return false;
      }
    }
  }

  return true;
}
