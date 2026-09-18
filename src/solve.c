#include "solve.h"
#include "parser.h"

#include <string.h>
#include <stdio.h>

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

  printf("%s -> %i\n", expression, result);

  return 0;
}