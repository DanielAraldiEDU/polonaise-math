#include <iostream>

#include "structs.hpp"

using namespace std;

template<typename T>
void showStack(Stack<T> &stack) {
    for (int index = 0; index <= stack.topLevel; index++) {
        cout << stack.array[index] << " ";
    }    
}

template<typename T>
void showQueue(Queue<T> &queue) {
    for (int index = queue.start; index <= queue.end; index++) {
        cout << queue.array[index] << " ";
    }    
}
