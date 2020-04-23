#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main() {
    char* args[] = {"/bin/cat", "--help", NULL};
    execve("/bin/cat", args, environ);
    return 1;
}