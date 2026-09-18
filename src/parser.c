#include "parser.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *variables = NULL;
unsigned varaiblesAmount = 0;
char *expression = NULL;
unsigned char variableValues = 0;
unsigned chindex = 0;

char getCh() { return expression[chindex]; }

int parseEqual();

int parseUnary() {
  if (getCh() == 0) {
    printf("Error: expected a value. [%u]\n", chindex);
    return -1;
  }

  if (getCh() == '(') {
    chindex++;
    int result = parseEqual();
    if (result == -1)
      return -1;
    if (getCh() != ')') {
      printf("Error: expected a closing paren. [%u]\n", chindex);
      return -1;
    }
    chindex++;
    return result;
  }

  if (getCh() == '!') {
    chindex++;
    int result = parseUnary();
    if (result == -1)
      return -1;
    return !result;
  }

  if (getCh() == '0') {
    chindex++;
    return 0;
  }

  if (getCh() == '1') {
    chindex++;
    return 1;
  }

  if (isalpha(getCh())) {
    char name = getCh();
    int valueIndex = -1;
    for (unsigned i = 0; i < varaiblesAmount; i++)
      if (name == variables[i])
        valueIndex = i;
    if (valueIndex == -1) {
      printf("Error: bad variable name '%c'. [%u]\n", name, chindex);
      return -1;
    }
    chindex++;
    return (variableValues >> valueIndex) & 1;
  }

  printf("Error: unexpected char '%c'. [%u]\n", getCh(), chindex);
  return -1;
}

int parseAnd() {
  int result = parseUnary();

  if (result == -1)
    return -1;

  while (getCh() == '&') {
    chindex++;
    int newResult = parseUnary();
    if (newResult == -1)
      return -1;
    result = result && newResult;
  }

  return result;
}

int parseOr() {
  int result = parseAnd();

  if (result == -1)
    return -1;

  while (getCh() == '|') {
    chindex++;
    int newResult = parseAnd();
    if (newResult == -1)
      return -1;
    result = result || newResult;
  }

  return result;
}

int parseIf() {
  int result = parseOr();

  if (result == -1)
    return -1;

  while (getCh() == '>') {
    chindex++;
    int newResult = parseOr();
    if (newResult == -1)
      return -1;
    result = !result || newResult;
  }

  return result;
}

int parseXor() {
  int result = parseIf();

  if (result == -1)
    return -1;

  while (getCh() == '^') {
    chindex++;
    int newResult = parseIf();
    if (newResult == -1)
      return -1;
    result = result ^ newResult;
  }

  return result;
}

int parseEqual() {
  int result = parseXor();

  if (result == -1)
    return -1;

  while (getCh() == '=') {
    chindex++;
    int newResult = parseXor();
    if (newResult == -1)
      return -1;
    result = result == newResult;
  }

  return result;
}

int parseExpression(char *_variables, unsigned _variablesAmount,
                    uint8_t _variableValues, char *_expression) {
  variables = _variables;
  variableValues = _variableValues;
  expression = _expression;
  varaiblesAmount = _variablesAmount;
  chindex = 0;

  return parseEqual();
}