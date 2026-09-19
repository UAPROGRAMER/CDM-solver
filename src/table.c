#include "table.h"
#include "parser.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int makeTruthTable(char *variables, char *expression) {
  unsigned variablesAmount = strlen(variables);
  unsigned expressionLen = strlen(expression);

  unsigned maxValue = 1;

  for (unsigned i = 0; i < variablesAmount; i++)
    maxValue *= 2;

  if (parseExpression(variables, variablesAmount, 0, expression) == -1)
    return 1;

  printf("+");
  for (unsigned i = 0; i < variablesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  printf("|");
  for (unsigned i = 0; i < variablesAmount; i++)
    printf("%c|", variables[i]);
  printf("%s|\n", expression);

  printf("+");
  for (unsigned i = 0; i < variablesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  for (unsigned value = 0; value < maxValue; value++) {
    int result =
        parseExpression(variables, variablesAmount, value, expression);

    printf("|");

    for (unsigned i = 0; i < variablesAmount; i++)
      printf("%i|", ((int)value >> i) & 1);

    printf("%i", result);
    for (unsigned i = 0; i < expressionLen - 1; i++)
      printf(" ");
    printf("|\n");
  }

  printf("+");
  for (unsigned i = 0; i < variablesAmount; i++)
    printf("-+");
  for (unsigned i = 0; i < expressionLen; i++)
    printf("-");
  printf("+\n");

  return 0;
}