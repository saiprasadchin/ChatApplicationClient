#include "Utils.h"

int ErrorCheck(int expression, const char* message) {
    if(expression == SCOKETERROR) {
        perror(message);
        exit(0);
    }
    return expression;
}

int PthreadErrorCheck(int expression, const char* message) {
    if(expression != 0 ) {
        perror(message);
        exit(0);
    }
    return expression;
}

void StringOverwriteStdout() {
  printf("%s", "> ");
  fflush(stdout);
}