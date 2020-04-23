#include <stdio.h>
#include <unistd.h> // заголовочный файл, который обеспечивает доступ к API операционной системы

int main(int argc, char* argv[]){

    int pid = fork();
    switch(pid) {
        case -1:
            perror("fork");
            return -1;
        case 0:
            printf("\nChild process\nmy pid = %i, returned pid = %i\n\n", getpid(), pid);
            break;
        default:
            printf("\nParent process\nmy pid = %i, returned pid = %i\n\n", getpid(), pid);
            break;
    }
    return 0;
}