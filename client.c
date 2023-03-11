#define _XOPEN_SOURCE 500

#include "operators.c"
#include "config.h"


int main(int argc, char *argv[]){

  //----------------------------verifications ----------------------------------
  if(argc<=1){
    fprintf(stderr,
      "Veuillez inserer des valeurs à calculer\nEssayez --help pour afficher le manuel\n");
    return EXIT_FAILURE;
  }
  //--------------------------------aide----------------------------------------
  if(strcmp((const char *)argv[1],"--help") == 0){
    execlp("cat","cat","Manuels/manuel.txt",NULL);
    fprintf(stderr,"Err");

  }

  //---------------------------traitement entrées ------------------------------

  char *op = argv[argc-1];
  int val_num = argc-2;
  int valeurs[val_num];
  pid_t pid = getpid();


  if (opExists(op[0]) == -1){
    fprintf(stderr,
      "L'operateur entré n'est pas pris en charge \nEssayez --help pour afficher le manuel\n");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < val_num; i++) {
    if (myIsDigit(argv[i + 1])==-1) {
      fprintf(stderr,
        "Veuillez inserer uniquement des nombres\nEssayez --help pour afficher le manuel\n");
      return EXIT_FAILURE;
    }
  valeurs[i] = (int) strtol(argv[i + 1], NULL, 10);
  }

  //-------------------------------traitement shm ------------------------------
  // nom de la shm
  char shm_name[MAX_PID_DIGITS];
  sprintf(shm_name, "%d", pid);
  //
  //ouverture
  int shm_fd = shm_open(shm_name, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);

  if (shm_fd == -1) {
    fprintf(stderr,"Err shm_open");
    exit(EXIT_FAILURE);
  }
  //
  //def taille
  if (ftruncate(shm_fd, (long int) (val_num )) == -1) {
    fprintf(stderr,"Err ftruncate");
    exit(EXIT_FAILURE);
  }
  //
  //projection
  int *valeurs_shm = mmap(NULL, (size_t)val_num, PROT_READ | PROT_WRITE, MAP_SHARED,
      shm_fd, 0);

  if (valeurs_shm == MAP_FAILED) {
    fprintf(stderr,"Err mmap");
    exit(EXIT_FAILURE);
  }
  if (close(shm_fd) == -1) {
    fprintf(stderr,"Err close");
    exit(EXIT_FAILURE);
  }
  //
  //injection valeurs
  for (int i = 0; i < val_num; i++) {
    valeurs_shm[i] = valeurs[i];
  }
  //---------------------------- gestion interruption---------------------------

  signal(SIGTERM,gestionnaire);
  signal(SIGINT,gestionnaire);

  //----------------------------envoi de la requete-----------------------------


  requete info;
  strcpy(info.pid,shm_name);
  info.op = op[0];;
  info.val_num = val_num;

  if(sizeof(info) >= PIPE_MAX){
    fprintf(stderr,"Err : Taille max du tube atteinte");
    exit(EXIT_FAILURE);
  }

  int pipe_d;

  if((pipe_d = open(NOM_FIFO, O_WRONLY)) == -1 ){
    fprintf(stderr,
      "Veuillez lancer le serveur d'abord\nEssayez --help pour afficher le manuel\n");
    exit(EXIT_FAILURE);
  }
  if(write(pipe_d,&info,sizeof(info)) == -1 ){
    fprintf(stderr,"Err lecture tube");
    exit(EXIT_FAILURE);
  }
  if( close(pipe_d) == -1 ){
    perror("Erreur fermeture tube");
    exit(EXIT_FAILURE);
  }


//---------------------------réception résultat --------------------------------


  sem_t *sem_p = sem_open(NOM_SEMAPHORE, O_RDWR | O_CREAT | O_EXCL,
                          S_IRUSR | S_IWUSR, 0);
  if (sem_p == SEM_FAILED) {
    fprintf(stderr,"Err : sem_open");
    exit(EXIT_FAILURE);
  }
  //
  // On attends la fin du calcul
  if (sem_wait(sem_p) == -1) {
      fprintf(stderr,"Err:sem_wait");
      exit(EXIT_FAILURE);
    }

  //------------------------------Affichage-------------------------------------
  printf("le resultat est le suivant :\n");
  for (int i = 0 ; i <val_num ; i++){
  printf(" %d ", valeurs_shm[i]);
  }
  printf("\n");

  //------------------------------Unlink----------------------------------------
  if(shm_unlink(shm_name)==-1){
    fprintf(stderr,"Err shm_unlink");
    exit(EXIT_FAILURE);
  }
  if(sem_unlink(NOM_SEMAPHORE) == -1) {
    fprintf(stderr,"Err sem_unlink");
    exit(EXIT_FAILURE);
  }
}
//--------------------------Gestionnaire de signaux ----------------------------

void gestionnaire(int signum) {
  if (signum < 0) {
    exit(EXIT_FAILURE);
  }
  if(sem_unlink(NOM_SEMAPHORE)==-1){
    exit(EXIT_FAILURE);
  }
}

//vérifie si un char * represente un nombre valide
int myIsDigit(char * dig){
  size_t length = strlen(dig);
  for(size_t i =0 ; i< length;i++){
    if(i==0  && dig[i]== '-'){
      continue;
    }
    if(!isdigit(dig[i])){
      return -1;
    }
  }
  return 1;
}






