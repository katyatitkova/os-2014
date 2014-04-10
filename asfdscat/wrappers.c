#include "wrappers.h"

const int ERROR = -1;

// Wrapper functions
void error_exit(char * error_msg)
{
    perror(error_msg);
    exit(EXIT_FAILURE);
}

void * malloc_(size_t size)
{
    void * res = malloc(size);
    if (res == NULL) // we suppose size != 0
        error_exit("malloc");
    return res;
}

void * realloc_(void * ptr, size_t size)
{
    void * res = realloc(ptr, size);
    if (res == NULL)
        error_exit("realloc");
    return res;
}

ssize_t read_(int fd, void * buf, size_t count)
{
    ssize_t res = read(fd, buf, count);
    if (res == ERROR)
        error_exit("read");
    return res;
}

ssize_t write_(int fd, const void * buf, size_t count)
{
    ssize_t res = write(fd, buf, count);
    if (res == ERROR)
        error_exit("write");
    return res;
}

int open_(const char * pathname, int flags)
{
    int res = open(pathname, flags);
    if (res == ERROR)
        error_exit("open");
    return res;
}

int close_(int fd)
{
    int res = close(fd);
    if (res == ERROR)
        error_exit("close");
    return res;
}

pid_t fork_(void)
{
    pid_t res = fork();
    if (res == ERROR)
        error_exit("fork");
    return res;
}

pid_t waitpid_(pid_t pid, int * status, int options)
{
    pid_t res = waitpid(pid, status, options);
    if (res == ERROR)
        error_exit("waitpid");
    return res;
}

int execvp_(const char * file, char * const argv[])
{
    int res = execvp(file, argv);
    if (res == ERROR)
        error_exit("execvp");
    return res;
}

void write_all(int fd, const void * buf, ssize_t count)
{
    ssize_t written = 0;
    while (written < count)
        written += write_(fd, buf + written, count - written);
}
