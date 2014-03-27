#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

void error_exit(char * error_msg);

void * malloc_(size_t size);
ssize_t read_(int fd, void * buf, size_t count);
ssize_t write_(int fd, const void * buf, size_t count);
int open_(const char * pathname, int flags);
int close_(int fd);
pid_t fork_(void);
pid_t waitpid_(pid_t pid, int * status, int options);
int execvp_(const char * file, char * const argv[]);

void write_all(int fd, const void * buf, ssize_t count);
