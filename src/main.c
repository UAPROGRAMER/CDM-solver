#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "solve.h"
#include "table.h"

void printHelp() {
  printf("Usage:\n");
  printf("\tcdms [-h | --help]\n");
  printf("\tcdms [-t | --table] (variables) (expression)\n");
  printf("\tcdms [-s | --solve] (expression)\n");
  printf("\tcdms [-s | --solve] (variables) (expression)\n\n");

  printf("Arguments:\n");
  printf("\t-h, --help - Prints help.\n");
  printf("\t-t, --table - Solves expression for every possible variable value "
         "and builds truth table.\n");
  printf("\t-s, --solve - Solves expression for specified variable value if "
         "any.\n\n");

  printf("Table variables:\n");
  printf("\tA string of consecutive non-repeating case-sencetive letters.\n");
  printf("\tMax of 8 variables are allowed.\n\n");

  printf("Solve variables:\n");
  printf("\tA string of non-repeating case-sencetive letters and a "
         "corresponding value: 0 or 1.\n");
  printf("\tMax of 8 variables are allowed.\n\n");

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

  if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
    printHelp();
    return 0;
  }

  if (!strcmp(argv[1], "-t") || !strcmp(argv[1], "--table")) {
    if (argc != 4) {
      printf("Error: not enough arguments. [%i]\n", argc);
      return 1;
    }

    unsigned variablesAmount = strlen(argv[2]);

    if (variablesAmount > 8 || variablesAmount == 0) {
      printf("Error: variables amount can be in range [1-8]. [%u]\n",
             variablesAmount);
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
          return 1;
        }
      }
    }

    unsigned expressionLength = strlen(argv[3]);

    if (expressionLength > 64) {
      printf("Error: expression is too long. [%u]\n", expressionLength);
      return 1;
    }

    return makeTruthTable(argv[2], argv[3]);
  }

  if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--solve")) {
    if (argc == 3) {
      unsigned expressionLength = strlen(argv[2]);

      if (expressionLength > 64) {
        printf("Error: expression is too long. [%u]\n", expressionLength);
        return 1;
      }

      return solveExpr("", argv[2]);
    } else if (argc == 4) {
      unsigned variablesLen = strlen(argv[2]);

      if (variablesLen % 2 == 1 || variablesLen > 16) {
        printf("Error: bad variables length. [%u]\n", variablesLen);
        return 1;
      }

      for (unsigned i = 0; i < variablesLen / 2; i++) {
        if (!isalpha(argv[2][i * 2])) {
          printf("Error: variable name must only be a letter. [%u]\n", i);
          return 1;
        }

        if (argv[2][i * 2 + 1] != '0' && argv[2][i * 2 + 1] != '1') {
          printf("Error: variable must have value of 0 or 1. [%u]\n", i);
          return 1;
        }
      }

      for (unsigned i = 0; i < variablesLen / 2; i++) {
        for (unsigned j = 1; j < variablesLen / 2 - i; j++) {
          if (argv[2][i * 2] == argv[2][j * 2]) {
            printf("Error: variable names must not repeat. [%u]\n", i);
            return 1;
          }
        }
      }

      unsigned expressionLength = strlen(argv[3]);

      if (expressionLength > 64) {
        printf("Error: expression is too long. [%u]\n", expressionLength);
        return 1;
      }

      return solveExpr(argv[2], argv[3]);
    } else {
      printf("Error: bad amount of variables. [%i]\n", argc);
      return 1;
    }
  }

  printf("Error: bad argument. [%s]\n", argv[1]);
  return 1;

  return 0;
}