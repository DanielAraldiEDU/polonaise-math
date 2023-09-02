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
  T queueValue, stackValue;

  initialize(stack);
  initialize(resultQueue);

  while(remove(queue, queueValue)) {
    const bool isOperator = (queueValue >= 40 && queueValue <= 43) || queueValue == 45 || queueValue == 47 || queueValue == 94;
    const bool isCloseParentheses = queueValue == 41;

    if (isOperator) {
      if (isCloseParentheses) {
        
      } else {
        bool hasValue = pop(stack, stackValue);
        if (hasValue) {
          int precedenceValue = getPrecedenceValue(stackValue);
          int precedenceQueueValue = getPrecedenceValue(queueValue);
  
          if (precedenceQueueValue > precedenceValue) {
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

  if (!queue.length) insertOperatorsInQueue(resultQueue, stack, queueValue);

  return resultQueue;
}
