#include "wrappers.h"

#include <string.h>

const int BLOCK_SIZE = 4;//1024;
const char DELIMETER = '\n';

struct buffer_t
{
    char * buf;
    size_t size; //allocated memory
    size_t length; //used memory
};

void buffer_init(struct buffer_t * buf)
{
    buf->buf = malloc_(BLOCK_SIZE);
    buf->size = BLOCK_SIZE;
    buf->length = 0;
}

void buffer_realloc(struct buffer_t * buf)
{
    buf->size += BLOCK_SIZE;
    buf->buf = realloc_(buf->buf, buf->size);
}

void buffer_reverse(struct buffer_t * buf, size_t until)
{
    for (size_t i = 0; i <= until / 2; ++i)
    {
        char tmp = buf->buf[i];
        buf->buf[i] = buf->buf[until - i];
        buf->buf[until - i] = tmp;
    }
}

void read_and_write_all(int from, int to)
{
    struct buffer_t buf;
    buffer_init(&buf);
    bool eof = false;
    while (!eof)
    {
        ssize_t r = read_(from, buf.buf + buf.length, buf.size - buf.length);
        if (r == 0)
            eof = true;
        size_t old_length = buf.length;
        buf.length += r;
        size_t i = old_length;
        while (i < buf.length)
        {
            if (buf.buf[i] == DELIMETER)
            {
                if (i != 0)
                    buffer_reverse(&buf, i - 1);
                /*perror("after reverse");
                perror(buf.buf);
                perror("----");*/
                write_all(to, buf.buf, i + 1);
                size_t count = buf.length - i - 1;
                memmove(buf.buf, buf.buf + i + 1, count);
                /*perror("after memcpy");
                perror(buf.buf);
                perror("----");*/
                memset(buf.buf + count, 0, buf.size - count);
                /*perror("after memset");
                perror(buf.buf);
                perror("----");*/
                buf.length -= (i + 1);
                i = 0;
            }
            else
                ++i;
        }
        if (buf.length == buf.size && !eof)
        {
            buffer_realloc(&buf);
        }
        if (eof)
        {
            buffer_reverse(&buf, buf.length);
            write_all(to, buf.buf, buf.length);
        }
    }
    free(buf.buf);
}

int main(int argc, char * argv[])
{
    for (int i = 2; i < argc; ++i)
    {
        read_and_write_all(atoi(argv[i]), STDOUT_FILENO);
        if (i != argc - 1)
            write_all(STDOUT_FILENO, argv[1], strlen(argv[1]));
    }
    return EXIT_SUCCESS;
}

