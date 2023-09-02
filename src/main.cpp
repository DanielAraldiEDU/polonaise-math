#include <iostream>

#include "structs.hpp"
#include "native.hpp"
#include "./utils/helpers.hpp"
#include "./resolvers/methods.hpp"
#include "./validation/expression.hpp"

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
    cout << "Expression in the Notation Hungarian: ";
    show(queue);
    cout << endl;

    transformPolonaiseNotation(queue, resultQueue);

    cout << "Expression in the Polonaise Notation: ";
    show(resultQueue);
    cout << endl;

    const double resultExpression = calculatePolonaiseNotation(resultQueue);

    cout << endl;
    cout << "Expression Result: " << resultExpression << endl;
  } else {
    cout << "You entered an invalid expression!";
  }

  return 0;
}
