#include "solve.h"
#include "parser.h"

#include <stdio.h>
#include <string.h>

int solveExpr(char *variables, char *expression) {
  char variablesBuf[9] = {0};
  uint8_t variableValues = 0;

  unsigned variablesLen = strlen(variables);

  for (unsigned i = 0; i < variablesLen / 2; i++) {
    variablesBuf[i] = variables[i * 2];
    if (variables[i * 2 + 1] == '1')
      variableValues |= 1 << i;
  }

  int result = parseExpression(variablesBuf, variablesLen / 2, variableValues,
                               expression);

  if (result == -1)
    return 1;

  unsigned expressionLen = strlen(expression);

  printf("+");
  for (unsigned i = 0; i < variablesLen / 2; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  printf("|");
  for (unsigned i = 0; i < variablesLen / 2; i++)
    printf("%c|", variables[i * 2]);
  printf("%s|\n", expression);

  printf("+");
  for (unsigned i = 0; i < variablesLen / 2; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  printf("|");
  for (unsigned i = 0; i < variablesLen / 2; i++)
    printf("%i|", ((int)variableValues >> i) & 1);
  printf("%i", result);
  for (unsigned i = 0; i < expressionLen - 1; i++)
    printf(" ");
  printf("|\n");

  printf("+");
  for (unsigned i = 0; i < variablesLen / 2; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  return 0;
}