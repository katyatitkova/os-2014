#include <stdlib.h>

int main(int argc, char * argv[])
{
    if (argc < 2 || argc % 2 != 0)
    {
        perror("number of arguments");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
