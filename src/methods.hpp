#include <iostream>

using namespace std;

template<typename T> 
void initializeStack(Stack<T> &stack) {
    stack.topLevel = -1;
}

template<typename T> 
void initializeQueue(Queue<T> &queue) {
    queue.end = -1;
    queue.start = 0;
    queue.length = 0;
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
    if (queue.length == 0) return false;
    
    value = queue.array[queue.start];
    const bool isFull = queue.start == LENGTH - 1;
    queue.start = isFull ? 0 : queue.start + 1;
    queue.length--;
    return true;
}

template<typename T>
void insert(Queue<T> &queue, T value) {
    if (queue.length == LENGTH) return;

    const bool isFull = queue.start == LENGTH - 1;
    queue.end = isFull ? 0 : queue.end + 1;
    queue.array[queue.end] = value;
    queue.length++;
}
