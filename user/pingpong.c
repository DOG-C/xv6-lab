#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p_to_c[2];
  int c_to_p[2];
  char buf[1];

  if(argc != 1){
    fprintf(2, "Usage: no extra argument...\n");
    exit(1);
  }

  pipe(p_to_c);
  pipe(c_to_p);
  if (fork() == 0){
    if (read(p_to_c[0],buf, 1) != 1){
      fprintf(2, "pingpong: child failed to read\n");
      exit(1);
    }
    close(p_to_c[0]);
    
    printf("%d: received ping\n", getpid());

    if(write(c_to_p[1], buf, 1) != 1){
      fprintf(2, "pingpong: child failed to write\n");
      exit(1);
    }
    close(c_to_p[1]);
    exit(0);
  } else {
    if(write(p_to_c[1], buf, 1) != 1){
      fprintf(2, "pingpong: parent failed to write\n");
      exit(1);
    }
    close(p_to_c[1]);
    wait(0);

    if (read(c_to_p[0],buf, 1) != 1){
      fprintf(2, "pingpong: parent failed to read\n");
      exit(1);
    }
    close(c_to_p[0]);

    printf("%d: received pong\n", getpid());
    
    exit(0);
  }

  exit(0);
}
