#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY ftok("/tmp", 1)

int main (int argc, char * argv[]){
  
  int sd, i, sv;
  
  for(i = 0; argv[i]; i++){  
    if (!strcmp(argv[i], "-c")) {
      printf("creating semaphore...\n");
      char * path = "/tmp";
      sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0600);
      if (sd == -1) {
	printf("semaphore already exists\n");
      } else {
	printf("semaphore created: %d\n", sd);
	int value = atoi(argv[i+1]);
	semctl(sd, 0, SETVAL, value);
	printf("value set: %d\n", value);
      }
    }

    if (!strcmp(argv[i], "-v")) {
      printf("viewing semaphore...\n");
      sd = semget(KEY, 1, 0);
      sv = semctl(sd, 0, GETVAL);
      
      if (sv == -1) {
	printf("error viewing semaphore: %s\n", strerror(errno));
      } else {
	printf("sem value: %d\n", sv);
      }
    }

    if (!strcmp(argv[i], "-r")) {
      printf("removing semaphore...\n");
      sd = semget(KEY, 1, 0);
      sv = semctl(sd, 0, IPC_RMID);

      if (sv == -1) {
	printf("error removing semaphore: %s\n", strerror(errno));
      } else {
	printf("semaphore removed: %d\n", sd);
      }
    }
  }
}
