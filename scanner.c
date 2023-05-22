#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#define int long long // work with 64bit target

int token;            // current token
char *src, *old_src;  // pointer to source code string;
int poolSize;         // default size of text/data/stack
int line;             // line number

void next() {
    token = *src++;
    return;
}

void expression(int level) {
    // do nothing
}

void program() {
    next();                  // get next token
    while (token > 0) {
        printf("token is: %c\n", token);
        next();
    }
}

int eval() { // do nothing yet
    return 0;
}

int main(int argc, char **argv)
{
    int i, fd;

    argc--;
    argv++;

    poolSize = 256 * 1024; // arbitrary size
    line = 1;
    
    if ((fd = open(*argv, 0)) < 0) {
      printf("could not open(%s)\n", *argv);
      return -1;
    }

    if (!(src = old_src = malloc(poolSize))) {
        printf("could not malloc(%d) for source area\n", poolSize);
        return -1;
    } 

    // read the source file
    if ((i = read(fd, src, poolSize-1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }

    src[i] = 0; // add EOF character
    close(fd);

    program();
    return eval();
}