#ifndef OPERATORS_H
#define OPERATORS_H

#include <stdio.h>
#include <stdlib.h>

// -----------------------
extern int opExists(char op);

extern int makeCalcul(char op, int a, int b);

extern int sum(int x, int y);

extern int mult(int x, int y);

extern int min(int a, int b);

extern int max(int a, int b);

extern int pgcd(int a, int b);

#endif
