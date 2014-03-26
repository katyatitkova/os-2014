#include "wrappers.h"

#include <stdbool.h>

const int ERROR = -1;
const int BUF_SIZE = 1024;

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

void write_all(int fd, const void * buf, ssize_t count)
{
    ssize_t written = 0;
    while (written < count)
        written += write_(fd, buf + written, count - written);
}

void read_and_write(int from, int to)
{
    char buf[BUF_SIZE];
    ssize_t len = 0;
    bool eof = false;
    while (!eof)
    {
        ssize_t r = read_(from, buf + len, BUF_SIZE - len);
        if (r == 0)
            eof = true;
        len += r;
        if (len == BUF_SIZE || eof)
            write_all(to, buf, len);
    }
}
