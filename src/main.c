#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "table.h"

void printHelp() {
  printf("Usage:\n");
  printf("\tcdms [-h | --help]\n");
  printf("\tcdms [-t | --table] (variables) (expression)\n\n");

  printf("Arguments:\n");
  printf("\t-h, --help - Prints help.\n");
  printf("\t-t, --table - Solves expression for every possible variable value "
         "and builds truth table.\n\n");

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

  if (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")) {
    printHelp();
    return 0;
  } else if (strcmp(argv[1], "-t") || strcmp(argv[1], "--table")) {
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
  } else {
    printf("Error: bad mode. [%s]\n", argv[1]);
    return 1;
  }

  return 0;
}