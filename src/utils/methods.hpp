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

  const int openParentheses = 40;
  const int closeParentheses = 41;
  if (currentOperator == openParentheses || currentOperator == closeParentheses) return true;
  if (previousOperator == openParentheses || previousOperator == closeParentheses) return true;
  if (currentOperator == previousOperator) return false;
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
  int cont = 1;

  initialize(stack);
  initialize(resultQueue);

  while(remove(queue, value)) {
    const bool isOperator = (value >= 40 && value <= 43) || value == 45 || value == 47 || value == 94;
    const bool isCloseParentheses = value == 41;
    bool isParentheses = value == 40 || value == 41;

    if (isOperator) {
      bool isCurrentValueBiggest;
      if (previousValue != NULL) {
          isCurrentValueBiggest = handlePrecedence(value, previousValue);
          if (!isCurrentValueBiggest) {
            while(pop(stack, previousValue) && !isCurrentValueBiggest) {
              isParentheses = previousValue == 40 || previousValue == 41;
              isCurrentValueBiggest = handlePrecedence(value, previousValue);
              if (isParentheses) {
                isCurrentValueBiggest = true;
                push(stack, previousValue);
              } else {
                insert(resultQueue, previousValue);
              }
            }
            if (value != 41) push(stack, value);
          } else if (isCloseParentheses) {
            bool isFoundOpenParentheses = false;
            bool isFoundValue = pop(stack, value);
            while (isFoundValue != isFoundOpenParentheses) {
              isFoundOpenParentheses = value == 40;
              if (!isFoundOpenParentheses) {
                insert(resultQueue, value);
                isFoundValue = pop(stack, value);
              } else {
                isFoundValue = false;
              }
            }
          } else {
            push(stack, value);
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
