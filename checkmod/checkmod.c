#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void error_exit(char * error_msg)
{
    perror(error_msg);
    exit(EXIT_FAILURE);
}

bool verify_mode(char * mode)
{
    return
        (strlen(mode) == 1 && (mode[0] == 'r' || mode[0] == 'w')) ||
        (strlen(mode) == 2 && mode[0] == 'r' && mode[1] == 'w');
}

int main(int argc, char * argv[])
{
    if (argc < 2 || argc % 2 != 0)
        error_exit("number of arguments");
    char * uid = argv[1];
    // check if uid exists?
    for (int i = 2; i < argc; i += 2)
    {
        char * file = argv[i];
        // check if file exists
        char * mode = argv[i + 1];
        if (!verify_mode(mode))
            error_exit("mode");
    }
    return EXIT_SUCCESS;
}
