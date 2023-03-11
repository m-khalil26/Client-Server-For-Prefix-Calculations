#include "config.h"


int main(void){
  switch(fork()){
    case -1:
    fprintf(stderr,"Err fork");
    exit(EXIT_FAILURE);
    case 0 :
    //creation nouvelle session
    if(setsid() == -1){
      exit(EXIT_FAILURE);
    }
    //ignorer les signaux
    signal(SIGCHLD,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    switch(fork()){
      case -1 :
      fprintf(stderr,"Err fork");
      exit(EXIT_FAILURE);
      case 0:
      umask(077);
      //
      if( chdir ("/") == -1){
        fprintf(stderr,"Err : passage au root");
        exit(EXIT_FAILURE);
      }
      execlp(SERVER_PATH,"server_d",NULL);
      fprintf(stderr,"Err : Lancement serveur\nVeuillez configurer les chemins\nEssayez --help pour afficher le manuel");
      break;
      default:
      exit(EXIT_SUCCESS);
    }
    default:
    break;
  }
  exit(EXIT_SUCCESS);
}


