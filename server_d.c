#include "config.h"



int main(void){
  if (mkfifo(NOM_FIFO, S_IRUSR | S_IWUSR) == -1) {
    exit(EXIT_FAILURE);
  }
  //
  while (1) {
    //gestion du signal kill
    signal(SIGTERM,gestionnaire);
    //
    //-------------------------LECTURE REQUETE----------------------------------
    requete info;
    int pipe_fd;
    if ((pipe_fd = open(NOM_FIFO, O_RDONLY, O_CREAT)) == -1) {
      exit(EXIT_FAILURE);
    }
    if (read(pipe_fd, &info, sizeof(info)) == -1) {
      exit(EXIT_FAILURE);
    }
    if(close(pipe_fd) ==-1){
      exit(EXIT_FAILURE);
    }
    //-------------------------CREATION DU WORKER------------------------------

    char op[1];
    op[0] = info.op;
    char val_num[3];
    sprintf(val_num,"%d",info.val_num);

    switch (fork()) {
      case -1:
        exit(EXIT_FAILURE);
      case 0:
      {
        char *args[] = {
          (char *)("worker"), info.pid, op,val_num, NULL
        };
      execv(WORKER_PATH, args);
      exit(EXIT_FAILURE);
    }
      break;
    default:
      break;
    }
  }
}
void gestionnaire(int signum) {
  if (signum < 0) {
    exit(EXIT_FAILURE);
  }
  if(unlink(NOM_FIFO)==-1){
    exit(EXIT_FAILURE);
  }
}
