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

int getPrecedenceValue(char operatorValue) {
  switch(operatorValue) {
    case '^': return 3;
    case '*': return 2;
    case '/': return 2;
    case '+': return 1;
    case '-': return 1;
    default: return 0;
  }
}

bool handlePrecedence(char currentOperator, char previousOperator) {
  int currentOperatorPrecedence = getPrecedenceValue(currentOperator);
  int previousOperatorPrecedence = getPrecedenceValue(previousOperator);

  if (currentOperator == 40) return true;
  return currentOperatorPrecedence > previousOperatorPrecedence;
}

template<typename T>
void insertOperatorsInQueue(Queue<T> &queue, Stack<T> &stack, T value) {
  while (pop(stack, value)) {
    const bool isParentheses = value == 40 || value == 41;
    if (!isParentheses) insert(queue, value);
  }
}

template<typename T>
Queue<T> transformPolonaiseNotation(Queue<T> &queue) {
  Queue<T> resultQueue;
  Stack<T> stack;
  T value, previousValue = NULL;

  initialize(stack);
  initialize(resultQueue);

  while(remove(queue, value)) {
    const bool isOperator = (value >= 40 && value <= 43) || value == 45 || value == 47 || value == 94;
    const bool isCloseParentheses = value == 41;

    if (isOperator) {
      bool isCurrentValueBiggest = true;
      if (previousValue != NULL) isCurrentValueBiggest = handlePrecedence(value, previousValue);
      if (!isCurrentValueBiggest) insertOperatorsInQueue(resultQueue, stack, previousValue);
      if (isCloseParentheses) {
        bool isOpenParentheses = false;
        while (pop(stack, value) != isOpenParentheses) {
          isOpenParentheses = value == 40;
          if (!isOpenParentheses) insert(resultQueue, value);
        }
      } else {
        push(stack, value);
      }
      previousValue = value;
    } else {
      insert(resultQueue, value);
    }
  }

  if (!queue.length) insertOperatorsInQueue(resultQueue, stack, value);

  return resultQueue;
}
