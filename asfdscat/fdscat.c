#include "wrappers.h"

const int BUF_SIZE = 1024;

void read_and_write_all(int from, int to)
{
    char *buf = malloc_(BUF_SIZE);
    ssize_t len = 0;
    bool eof = false;
    while (!eof)
    {
        ssize_t r = read_(from, buf + len, BUF_SIZE - len);
        if (r == 0)
            eof = true;
        len += r;
        if (len == BUF_SIZE || eof)
        {
            write_all(to, buf, len);
            len = 0;
        }
    }
    free(buf);
}

int main(int argc, char * argv[])
{
    for (int i = 1; i < argc; ++i)
        read_and_write_all(atoi(argv[i]), STDOUT_FILENO);
    return EXIT_SUCCESS;
}
