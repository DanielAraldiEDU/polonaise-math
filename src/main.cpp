/*

Trabalho M1.
Estudades: Daniel Sansão Araldi e Rafael Mota Alves.

*/

#include <cctype>
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

  cout << "Introduction\n\n";
  cout << "Constants represented by a single digit (0–9) and inside "
          "parentheses!\n";
  cout << "Incognitos represented by a single letter! (a–z or A-Z)\n";
  cout << "Math operations: (+, -, *, / and ^)\n\n";

  string expression;
  cout << "Enter a math expression: ";
  getline(cin, expression);

  removeEmptySpaces(queue, expression);

  const bool isValid = validateExpression(queue);
  if (isValid) {
    cout << "\nExpression in the Notation Hungarian: ";
    show(queue);
    cout << endl;

    transformPolonaiseNotation(queue, resultQueue);

    cout << "Expression in the Polonaise Notation: ";
    show(resultQueue);
    cout << endl;

    toUpperNotation(resultQueue);

    const double resultExpression = calculatePolonaiseNotation(resultQueue);

    cout << "\nExpression Result: " << resultExpression << endl;
  } else {
    cout << "You entered an invalid expression!";
  }

  return 0;
}
