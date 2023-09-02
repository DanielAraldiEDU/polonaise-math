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