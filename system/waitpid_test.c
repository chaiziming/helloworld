#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int subprocess_status;
    printf("老学员在校区\n");

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fail to fork\n");
        return 1;
    } else if (pid == 0) {
        char *args[] = {"/usr/bin/ping", "-c", "10", "www.baidu.com", NULL};
        char *envs[] = {NULL};
        printf("新学员%d ping\n", getpid());
        int exR = execve("/usr/bin/ping", args, envs);
        if (exR < 0)
        {
            perror("fail to execve\n");
            return 1;
        }
    } else {
        printf("老学员%d等待新学员%dping完\n", getpid(), pid);
        waitpid(pid, &subprocess_status, 0);
    }
    printf("老学员等待完成\n");
    

    return 0;
}
