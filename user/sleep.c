#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "Usage: set a number for sleep...\n");
    exit(1);
  } else if (argc > 2){
    fprintf(2, "Usage: only set a number...\n");
    exit(1);
  }

  sleep(atoi(argv[1]));
  
  exit(0);
}
