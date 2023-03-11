//---------------------------------INCLUDES-----------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <semaphore.h>
#include <signal.h>

//----------------------------------MACROS------------------------------------//
#define NOM_SEMAPHORE "/semaphore_nommé"
#define NOM_FIFO "/tmp/tube_requete"
#define MAX_PID_DIGITS 6
#define PIPE_MAX PIPE_BUF // Pour paramtrer la taille du fifo

//A modifier selon emplacement
#define WORKER_PATH "the path of the project here"
#define SERVER_PATH "the path of the project here"

//---------------------------------AUTRE----------------------------------------

//structure permettant l'envoi d'information dans le tube
typedef struct requete {
  char pid[6];
  char op;
  int val_num;
} requete;

//headers
void gestionnaire(int signum);
int myIsDigit(char * dig);
