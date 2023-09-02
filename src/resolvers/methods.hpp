#include <iostream>

using namespace std;

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
              if (!hasNextStackValue) {
                cout << "You entered an invalid expression!";
                return;
              } else if (hasNextStackValue && stackValue == 40) hasNextStackValue = false;
            }
          }
        } else {
          cout << "You entered an invalid expression!";
          return;
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
                } else if (precedenceQueueValue > precedenceValue) {
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
