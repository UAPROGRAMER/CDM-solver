#include "table.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

char *variables = NULL;
unsigned varaiblesAmount = 0;
char *expression = NULL;
unsigned char values = 0;
unsigned chindex = 0;

char getCh() { return expression[chindex]; }

int parseExpression();

int parseUnary() {
  if (getCh() == 0) {
    printf("Error: expected a value. [%u]\n", chindex);
    return -1;
  }

  if (getCh() == '(') {
    chindex++;
    int result = parseExpression();
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
    for (int i = 0; i < (int)varaiblesAmount; i++)
      if (name == variables[i])
        valueIndex = i;
    if (valueIndex == -1) {
      printf("Error: bad variable name '%c'. [%u]\n", name, chindex);
      return -1;
    }
    chindex++;
    return (values >> valueIndex) & 1;
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

int parseExpression() { return parseEqual(); }

int makeTruthTable(char *_variables, char *_expression) {
  variables = _variables;
  expression = _expression;

  varaiblesAmount = strlen(variables);
  unsigned expressionLen = strlen(expression);
  unsigned maxValue = pow(2, varaiblesAmount);

  values = 0;
  chindex = 0;

  if (parseExpression() == -1)
    return 1;

  printf("+");
  for (unsigned i = 0; i < varaiblesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  printf("|");
  for (unsigned i = 0; i < varaiblesAmount; i++)
    printf("%c|", variables[i]);
  printf("%s|\n", expression);

  printf("+");
  for (unsigned i = 0; i < varaiblesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  for (unsigned ivalue = 0; ivalue < maxValue; ivalue++) {
    values = ivalue;
    chindex = 0;

    int result = parseExpression();

    printf("|");

    for (unsigned i = 0; i < varaiblesAmount; i++)
      printf("%i|", ((int)values >> i) & 1);

    printf("%i", result);
    for (unsigned i = 0; i < expressionLen - 1; i++)
      printf(" ");
    printf("|\n");
  }

  printf("+");
  for (unsigned i = 0; i < varaiblesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  return 0;
}