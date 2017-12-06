#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY ftok("/tmp", 1)

int main (int argc, char * argv[]){
  int sd, i;
  
  printf("argc: %d\n", argc);
  for(i = 0; argv[i]; i++){
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  
  if (argc > 2 && !strcmp(argv[1], "-c")) {
    printf("\ncreating semaphore...\n");
    
    char * path = "/tmp";
    //key_t KEY = ftok(path, 1);
    /*
    if (KEY == -1) {
      printf("error creating KEY: %s\n", strerror(errno));
    } else {
      printf("KEY: %d\n", (int)KEY);
    }
    */
    sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL);
    if (sd == -1) {
      printf("semaphore already exists\n");
    } else {
      printf("semaphore created: %d\n", sd);
      int value = atoi(argv[2]);
      semctl(sd, 0, SETVAL, value);
      printf("value set: %d\n", value);
    }
  }

  if (argc > 1 && ! strcmp(argv[1], "-v")) {
    printf("\nviewing semaphore...\n");
    int sv = (int)semctl(sd, 0, GETVAL);
    if (sv == -1) {
      printf("error viewing semaphore: %s\n", strerror(errno));
    } else {
      printf("sem value: %d\n", sv);
    }
  }
}
