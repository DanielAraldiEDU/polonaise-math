#include <iostream>

#include "structs.hpp"
#include "./utils/helpers.hpp"
#include "./validation/expression.hpp"
#include "./resolvers/methods.hpp"
#include "native.hpp"

using namespace std;

int main() {
  Queue<char> queue, resultQueue;

  initialize(queue);
  initialize(resultQueue);

  string expression;
  cout << "Enter a math expression: ";
  getline(cin, expression);

  removeEmptySpaces(queue, expression);

  const bool isValid = validateExpression(queue);
  if (isValid) {
    transformPolonaiseNotation(queue, resultQueue);
    show(resultQueue);
  } else {
    cout << "You entered an invalid expression!";
  }

  return 0;
}
