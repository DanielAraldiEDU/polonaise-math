#include <iostream>

using namespace std;

template<typename T>
void removeEmptySpaces(Queue<T> &queue, string expression) {
  for (int index = 0; index < expression.length(); index++) {
    if (expression[index] != ' ') insert(queue, expression[index]);
  }
}

template<typename T>
bool hasCharacterAfterCharacter(T currentValue, T previousValue) {
  const bool hasNumberAfterNumber = isNumber(currentValue) && isNumber(previousValue);
  const bool hasNumberAfterLetter = isLetter(currentValue) && isNumber(previousValue);
  const bool hasLetterAfterNumber = isNumber(currentValue) && isLetter(previousValue);
  const bool hasLetterAfterLetter = isLetter(currentValue) && isLetter(previousValue);
  
  return hasNumberAfterNumber || hasNumberAfterLetter || hasLetterAfterNumber || hasLetterAfterLetter;
}

template<typename T>
bool validateExpression(Queue<T> queue) {
  if (queue.length > LENGTH || !queue.length) return false;

  T currentValue, previousValue = NULL;
  int couterCloseParentheses = 0, couterOpenParentheses = 0;
  
  while (remove(queue, currentValue)) {
    if (isOpenParenthese(currentValue)) couterOpenParentheses++;
    if (isCloseParenthese(currentValue)) couterCloseParentheses++;

    if (previousValue == NULL && isOperator(currentValue) && !isOpenParenthese(currentValue)) return false;
    if (hasCharacterAfterCharacter(currentValue, previousValue)) return false;

    if (isOperator(currentValue) && isOperator(previousValue) && isCloseParenthese(currentValue)) {
      if (!isCloseParenthese(previousValue)) return false;
    };

    const bool doesntValuesAreParentheses = !isParentheses(currentValue) && !isParentheses(previousValue);
    if (isOperator(currentValue) && isOperator(previousValue) && doesntValuesAreParentheses) return false;

    previousValue = currentValue;
  }

  if (couterOpenParentheses != couterCloseParentheses) return false;
  if (isOperator(previousValue) && !isCloseParenthese(previousValue)) return false;

  return true;
}
