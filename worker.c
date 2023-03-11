#define _XOPEN_SOURCE 500
#include "config.h"
#include "operators.c"
#include <math.h>

void hillis (int * elems , int length, char op);



int main(int argc, char ** argv){

  (void)argc;
  char op = argv[2][0];
  char* shm_name = argv[1];
  int val_num = (int)strtol(argv[3],NULL,10);

  //--------------------LECTURE VALEURS SHM ------------------------------------

  int shm_fd = shm_open(shm_name, O_RDWR, S_IRUSR | S_IWUSR);

  if (shm_fd == -1) {
    exit(EXIT_FAILURE);
  }

  int *valeurs_shm = mmap(NULL, (size_t)val_num, PROT_READ | PROT_WRITE, MAP_SHARED,
      shm_fd, 0);

  if (valeurs_shm == MAP_FAILED) {
    exit(EXIT_FAILURE);
  }

  int valeurs[val_num];

  for (int i = 0; i < val_num; i++) {
    valeurs[i]= valeurs_shm[i];
  }

  //
  //Application de l'algortihme de Hillis Steele
  hillis(valeurs,val_num, op);

  //-------------------------------REMPLIR SHM----------------------------------

  for(int i =0; i <val_num; i++){
    valeurs_shm[i]=valeurs[i];
  }

  //-------------------------------PREVENIR CLIENT------------------------------

  sem_t *sem_p = sem_open(NOM_SEMAPHORE, O_RDWR,
                          S_IRUSR | S_IWUSR, 0);
  if (sem_p == SEM_FAILED) {
    exit(EXIT_FAILURE);
  }

  //On prévient le client
  if (sem_post(sem_p) == -1) {
      exit(EXIT_FAILURE);
    }

exit(EXIT_SUCCESS);

}


void operation(int *elems, int *acc, int length, int step,char op) {
  step = (int) pow(2, step);
  for (int i = 0; i < length; i++) {
    if (i < step) {
      acc[i] = elems[i];
    } else {
      acc[i] = makeCalcul( op ,elems[i],elems[i - step]);;
    }
  }
}

void hillis (int * elems , int length, char op){
  int acc[length];
  int range = (int) log2(length)+1;
  int i = 0;
  while (i < range) {
    operation(elems, acc, length, i,op);
    for (int i = 0; i < length; i++) {
      elems[i] = acc[i];
    }
    i++;
  }
}







