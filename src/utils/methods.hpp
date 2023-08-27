#include <iostream>

using namespace std;

template<typename T>
void show(Stack<T> &stack) {
  for (int index = 0; index <= stack.topLevel; index++) cout << stack.array[index];    
}

template<typename T>
void show(Queue<T> &queue) {
  for (int index = 0; index <= queue.length; index++) cout << queue.array[index];
}

int getPrecedenceValue(char operatorValue){
  switch(operatorValue){
    case '^': return 3;
    case '*': return 2;
    case '/': return 2;
    case '+': return 1;
    case '-': return 1;
    default: return 0;
  }
}

bool handlePrecedence(char currentOperator, char previousOperator){
  int currentOperatorPrecedence = getPrecedenceValue(currentOperator);
  int previousOperatorPrecedence = getPrecedenceValue(previousOperator);

  return currentOperatorPrecedence >= previousOperatorPrecedence;
}

template<typename T>
void getOperators(Queue<T> &queue, Stack<T> &stack) {
  T value;
    
  while(remove(queue, value)) {
    const bool isOperator = (value >= 40 && value <= 43) || value == 45 || value == 47 || value == 94;
      if (isOperator) push(stack, value);
    }
}
