#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define BUFFSIZE 10240

void exe(char *arg);
int launch(char *arg, int barrier);
void shellLoop();

int main(int argc, char **argv) {
  if (argc > 2){
    printf("too many arguments\n");  
    exit(0);
  }

  shellLoop();
  return 0;
  	
}

int launch(char *arg, int barrier){
  // this doesnt deal with barriers yet, so the functionailty does not qoek
  pid_t pid, wpid;
  int start;
  int status;
  
  pid = fork();
  if (pid == 0){
    // child 
    exe(arg);
    exit(1); 
  } else if (pid < 0){
    //error forking
    perror("error forking");
  } else {
    // parent 
    if (barrier == 0){
      wait(NULL); // normal behavior
    }
    else if (barrier = 1){
      int returnStat;
      waitpid(pid, &returnStat, 0);      
    }
 
  }


  
  return 1;  
}


//this might have to be modified a bit
void shellLoop(){
  //char cmd[BUFFSIZE];
  char *cmd = malloc(sizeof(char) * BUFFSIZE);
  //ssize_t bufsize = BUFFSIZE;
  int status;
  int c;
  int position;
  int barrier = 0;
  while(1){
    printf("prompt> ");
    position = 0;

    // this gets each char unil it sees a \n or eof	
    while(1){
      c = getchar();
      if (c == '\n' || c == EOF){
	cmd[position] = '\0';
	break;
      }
      else{
        cmd[position] = c;
      }
      position++;
    }
    
    //if the command is "exit" then we terminate the program	   
    if ( strcmp(cmd,"exit") == 0){
      printf("good bye\n");
      return;
      signal(SIGINT, SIG_DFL);
    }   
    
    //functionality doesn't work	
    else if (strcmp(cmd, "barrier") == 0){
      //barrier
      barrier = 1; 
      printf("barrier set\n");
      continue;
    } 
    status = launch(cmd, barrier);
    
  }
}

void exe(char *arg){
  int stat;
   
  char *cmd[] = {
      "/bin/bash",
      "-c",
      arg,
      NULL
  };
  
  int ret;
   
  ret = execvp(cmd[0], cmd);
  if (ret == -1){
      printf("error");
  }

}


