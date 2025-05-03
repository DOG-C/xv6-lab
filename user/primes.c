#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
pipeline(int r)
{
    int p;
    int n;
    if (read(r, &p, sizeof(int)) != sizeof(int)) {
        close(r);
        exit(0);
    }

    printf("prime %d\n", p);

    int fd[2];
    pipe(fd);
    int pid = fork();
    if(pid > 0){
        close(fd[0]);

        while (read(r, &n, sizeof(int)) == sizeof(int)) {
            if (n % p != 0) {
                write(fd[1], &n, sizeof(int));
            }
        }

        close(r);
        close(fd[1]);
        wait(0);
    } else if(pid == 0){
        close(fd[1]);
        pipeline(fd[0]);
        exit(0);
    } else {
        fprintf(2, "fork error\n");
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 1) {
        fprintf(2, "Usage: no extra argument...\n");
        exit(1);
      }
    
    int fd[2];

    pipe(fd);
    int pid = fork();
    if (pid > 0) {
        close(fd[0]);

        for(int i=2; i<=35; i++){
            write(fd[1], &i, sizeof(int));
        }
        close(fd[1]);
        wait(0);
    } else if (pid == 0) {
        close(fd[1]);
        pipeline(fd[0]);
        exit(0);
    } else {
        fprintf(2, "fork error\n");
    }

    exit(0);
}
