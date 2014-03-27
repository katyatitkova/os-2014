#include "wrappers.h"
#include <string.h>

const int MAX_INT_LENGTH = 11; // 10 and \0

int main(int argc, char * argv[])
{
    if (argc <= 1)
        error_exit("not enough arguments");
    char * argv_exec[argc];
    argv_exec[0] = argv[1];
    for (int i = 2; i < argc; ++i)
    {
        argv_exec[i - 1] = malloc_(MAX_INT_LENGTH);
        memset(argv_exec[i - 1], 0, MAX_INT_LENGTH);
        int fd = open_(argv[i], O_RDONLY);
        sprintf(argv_exec[i - 1], "%d", fd);
    }
    argv_exec[argc - 1] = NULL;
    pid_t pid = fork_();
    if (pid != 0)
    {
        int status;
        waitpid_(pid, &status, 0);
        if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
            error_exit("exit status of executed program");
    }
    else
    {
        execvp_(argv_exec[0], argv_exec);
        _exit(EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;
}
