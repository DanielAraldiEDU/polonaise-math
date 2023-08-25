#include <iostream>

#include "methods.hpp"
#include "structs.hpp"
#include "./utils/show.hpp"

using namespace std;

int main() {
    Queue<char> queue;

    initializeQueue(queue);

    string expression;
    cout << "Enter a math expression: ";
    getline(cin, expression);

    if (expression.length() > LENGTH || expression.length() == 0) {
        cout << "You entered an invalid expression!";
        return 0;
    }

    for (int index = 0; index < expression.length(); index++) {
        if (expression[index] != ' ') insert(queue, expression[index]);
    }
    return 0;
}
