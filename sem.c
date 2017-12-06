#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
-c N
Create a semaphore, set value to N. 
If it already exists, print message saying so.

-v
view current value of the semaphore

-r
remove the semaphore
*/

int main (int argc, char * argv[]){
  printf("ARGHJDSKKJSDAF\n");
  int sd, i;
  printf("argc: %d\n", argc);
  for(i = 0; argv[i]; i++){
    printf("argv[%d]: %s\n", i, argv[i]);
  }
  if(argc > 1 && !strcmp(argv[1], "-c")){
    // create semaphore
    
    char * path = "/temp";
    key_t KEY = ftok(path, 1);
    if (KEY == -1) {
      printf("error creating KEY: %s\n", strerror(errno));
    } else {
      printf("KEY value: %d\n", (int)KEY);
    }
    
    sd = semget(KEY, 1, IPC_CREAT | IPC_EXCL);
    if(sd == -1){
      printf("semaphore already exists\n");
    }else{
      printf("semaphore created: %d\n", sd);
      int value = atoi(argv[2]);
      semctl(sd, 0, SETVAL, value);
      printf("value set: %d\n", value);
    }
  }
}
