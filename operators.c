#include "operators.h"


//-------------------------VERIFICATIONS----------------------------------------

int opExists(char op) {
  if( op == '+' || op == 'x'  || op == 'm' || op == 'l' || op == 'p' ){
    return 1;
  }
  return -1;
}



//-------------------------OPERATIONS PRISES EN CHARGE--------------------------

int sum(int x, int y) {
  return x + y;
}

int mult(int a , int b){
  return a*b;
}

int min(int a , int b){
  if(a>=b){
    return b;
  }
  return a;
}

int max(int a , int b){
  if(a<=b){
    return b;
  }
  return a;
}

int pgcd(int a, int b){
  int pgcd=0;
  for(int i=1; i <= a && i <= b; ++i){
    if(a%i==0 && b%i==0){
      pgcd = i;
    }
  }
  return pgcd;
}

//---------------------------------CALCUL---------------------------------------

int makeCalcul(char op, int a, int b) {
  switch (op) {
    case '+':
      return sum(a, b);
    case 'x':
      return mult(a,b);
    case 'm':
      return max(a,b);
    case 'l':
      return min(a,b);
    case 'p' :
      return pgcd(a,b);
    default:
      fprintf(stderr,"Err operator");
      return EXIT_FAILURE;
  }
}








