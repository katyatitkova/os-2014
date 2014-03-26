#include "wrappers.h"

int main(int argc, char * argv[])
{
    for (int i = 0; i < argc; ++i)
        read_and_write(atoi(argv[i]), STDOUT_FILENO);
    return EXIT_SUCCESS;
}
