#include <iostream>

#include "structs.hpp"

using namespace std;

template<typename T> 
void initializeStack(Stack<T> &stack) {
    stack.topLevel = -1;
}

template<typename T> 
void initializeQueue(Queue<T> &queue) {
    queue.end = -1;
    queue.start = 0;
}

template<typename T>
bool pop(Stack<T> &stack, T &value) {
    if (stack.topLevel < 0) return false;
    
    value = stack.array[stack.topLevel];
    stack.topLevel--;
    return true;
}

template<typename T>
void push(Stack<T> &stack, T value) {
    if (stack.topLevel == LENGTH - 1) return;
    stack.topLevel++;
    stack.array[stack.topLevel] = value;
}

template<typename T>
bool remove(Queue<T> &queue, T &value) {
    if (queue.start > queue.end) return false;
    
    value = queue.array[queue.start];
    queue.start++;
    return true;
}

template<typename T>
void insert(Queue<T> &queue, T value) {
    if (queue.end == LENGTH - 1) return;
    queue.end++;
    queue.array[queue.end] = value;
}
