#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
//#include <bluetooth/bluetooth.h>
//#include <bluetooth/hci.h>
//#include <bluetooth/hci_lib.h>

char** setUpArgs();
int tearDownArgs(char**);

int main(int argc, char ** argv)
{
  char ** args = setUpArgs();

  int status = 0;
  pid_t pid = fork();

  if (pid == 0) // child process
    {
      printf("in child");
      execvp(*args,args);
    }// end child process
  else
    {
      printf("in parent\n");
      printf("child id = %d\n",pid);
      //while(wait(&status) != pid);
      sleep(6);

      int killNo = kill(pid,0);
      int errVal = errno;
      printf("killNo = %d\nerrVal = %d\n",killNo,errVal);
      if (killNo == -1 && errVal == EPERM)
	{
	  printf("child is alive\n");
	  //TODO: UNLOCK DOOR
	}// wait
      else
	{
	  printf("child failed\n");
	  if (errVal == EINVAL)
	    printf("errVal = EINVAL\n");
	  else if (errVal == ESRCH)
	    printf("errVal = ESRCH\n");
	  else if (errVal == EPERM)
	    printf("errVal = EPERM\n");
	  else
	    printf("errVal = UNKNOWN\n");
	}
      waitpid(pid,NULL,0);
      printf("after waitpid()\n");
    }// do something else

  printf("done\n");
  printf("tear down args rc:%d\n",tearDownArgs(args));
  return 0;
}// end main()

char ** setUpArgs()
{
  char * sudo = (char*)calloc(5,sizeof(char));
  memcpy(sudo,"sudo",4);

  char * rfcomm = (char*)calloc(7,sizeof(char));
  memcpy(rfcomm,"rfcomm",6);

  char * connect = (char*)calloc(8,sizeof(char));
  memcpy(connect,"connect",7);

  char * zero = (char*)calloc(2,sizeof(char));
  memcpy(zero,"0",1);

  char * bluetooth = (char*)calloc(18,sizeof(char));
  memcpy(bluetooth,"00:CD:FE:CE:BC:4D",17);

  char * one = (char*)calloc(2,sizeof(char));
  memcpy(one,"1",1);

  char ** args = (char**)calloc(6,sizeof(char*));
  *args = sudo;
  *(args + 1) = rfcomm;
  *(args + 2) = connect;
  *(args + 3) = zero;
  *(args + 4) = bluetooth;
  *(args + 5) = one;

  return args;
}// end setUpArgs()

int tearDownArgs(char ** args)
{
  int i = 0;
  while (i < 6)
    free(*(args + i++));
  free(args);
  return i;
}// end tearDownArgs()
