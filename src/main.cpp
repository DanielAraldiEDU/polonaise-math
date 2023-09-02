#include <iostream>

#include "structs.hpp"
#include "./utils/methods.hpp"
#include "native.hpp"

using namespace std;

int main() {
  Queue<char> queue, resultQueue;

  initialize(queue);
  initialize(resultQueue);

  string expression;
  cout << "Enter a math expression: ";
  getline(cin, expression);

  const int expressionLength = expression.length();
  if (expressionLength > LENGTH || !expressionLength) {
    cout << "You entered an invalid expression!";
    return 0;
  }

  for (int index = 0; index < expressionLength; index++) {
    if (expression[index] != ' ')
      insert(queue, expression[index]);
  }

  transformPolonaiseNotation(queue, resultQueue);
  show(resultQueue);
  return 0;
}
