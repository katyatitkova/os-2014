#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h> 
#include <sys/types.h>
#include <unistd.h>

const int ERROR = -1;

void error_exit(char * error_msg)
{
    perror(error_msg);
    exit(EXIT_FAILURE);
}

int setreuid_(uid_t ruid, uid_t euid)
{
    int res = setreuid(ruid, euid);
    if (res == ERROR)
        error_exit("setreuid");
    return res;
}

int setuid_(uid_t uid)
{
    int res = setuid(uid);
    if (res == ERROR)
        error_exit("setuid");
    return res;
}

int access_(const char * pathname, int mode)
{
    int res = access(pathname, mode);
    if (res == ERROR)
        error_exit("access");
    return res;
}

int get_mode(char * mode)
{
    if (strlen(mode) == 1)
    {
        if (mode[0] == 'r')
            return R_OK;
        if (mode[0] == 'w')
            return W_OK;
    }
    if (strlen(mode) == 2 && mode[0] == 'r' && mode[1] == 'w')
        return R_OK | W_OK;
    error_exit("mode");
    return ERROR;
}

int main(int argc, char * argv[])
{
    //setreuid_(geteuid(), getuid());
    if (argc < 2 || argc % 2 != 0)
        error_exit("number of arguments");
    int uid = atoi(argv[1]);
    setuid_(uid);
    for (int i = 2; i < argc; i += 2)
    {
        access_(argv[i], F_OK);
        access_(argv[i], get_mode(argv[i + 1]));
    }
    return EXIT_SUCCESS;
}
