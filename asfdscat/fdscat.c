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

void buffer_init_size(struct buffer_t * buf, size_t size)
{
    buf->buf = malloc_(size);
    buf->size = size;
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
    bool first = false;
    bool second = false;
    struct buffer_t first_str;
    struct buffer_t second_str;
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
                if (first)
                {
                    buffer_init_size(&second_str, i + 1);
                    memcpy(second_str.buf, buf.buf, i + 1);
                    second_str.length = i + 1;
                    if (i != 0)
                        buffer_reverse(&second_str, i - 1);
                    second = true;
                }
                else
                {
                    buffer_init_size(&first_str, i + 1);
                    memcpy(first_str.buf, buf.buf, i + 1);
                    first_str.length = i + 1;
                    if (i != 0)
                        buffer_reverse(&first_str, i - 1);
                    first = true;
                }
                if (second)
                {
                    write_all(to, second_str.buf, second_str.length);
                    write_all(to, first_str.buf, first_str.length);
                    first = false;
                    second = false;
                    free(first_str.buf);
                    free(second_str.buf);
                }
                size_t count = buf.length - i - 1;
                memmove(buf.buf, buf.buf + i + 1, count);
                memset(buf.buf + count, 0, buf.size - count);
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
            if (first)
            {
                write_all(to, first_str.buf, first_str.length);
                free(first_str.buf);
            }
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

