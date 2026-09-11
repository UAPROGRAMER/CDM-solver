#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "table.h"

void printHelp() {
  printf("Usage:\n");
  printf("\tcdms h -> prints help\n");
  printf("\tcdms t [str of vars] [expression] -> builds a truth table\n\n");
  printf("Variables:\n");
  printf("\tA string of consecutive non-repeating case-sencetive letters.\n");
  printf("\tMax of 8 variables are allowed for the truth table.\n\n");
  printf("Expressions:\n");
  printf("\tUnary operators: !\n");
  printf("\tBinary operators: & | > ^ =\n");
  printf("\tOperators precedence: ! & | > ^ =\n");
  printf("\tParens are allowed and have the highest precedence.\n");
  printf("\tMax expression length is 32.\n\n");
  printf("Autor:\n\tStanislav Yatskiv\n\n");
  printf(
      "Contact info:\n\tgithub.com/UAPROGRAMER\n\tstasyatskiu2008@gmail.com\n");
}

// first argument a str of characters (variables)
int main(int argc, char *argv[]) {
  if (argc < 2) {
    printHelp();
    return 1;
  }

  if (strlen(argv[1]) != 1) {
    printf("Error: mode must be 1 char. [%s]\n", argv[1]);
    return 1;
  }

  char mode = argv[1][0];

  switch (mode) {
  case 'h':
    printHelp();
    return 0;
  case 't':
    if (argc < 4) {
      printf("Error: not enough arguments. [%i]\n", argc);
      return 1;
    }

    unsigned variablesAmount = strlen(argv[2]);

    if (variablesAmount > 8) {
      printf("Error: too many variables. [%u]\n", variablesAmount);
      return 1;
    }

    for (unsigned i = 0; i < variablesAmount; i++) {
      if (!isalpha(argv[2][i])) {
        printf("Error: variable name must only be a letter. [%u]\n", i);
        return 1;
      }
    }

    for (unsigned i = 0; i < variablesAmount; i++) {
      for (unsigned j = 1; j < variablesAmount - i; j++) {
        if (argv[2][i] == argv[2][j]) {
          printf("Error: variable names must not repeat. [%u]\n", i);
        }
      }
    }

    unsigned expressionLength = strlen(argv[3]);

    if (expressionLength > 32) {
      printf("Error: expression is too long. [%u]\n", expressionLength);
      return 1;
    }

    return makeTruthTable(argv[2], argv[3]);
  default:
    printf("Error: bad mode. [%c]\n", mode);
    return 1;
  }

  return 0;
}