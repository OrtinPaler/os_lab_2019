#include <stdio.h>

int main(int argc, char* argv[]){

printf("\n\nArguments: ");
for (int i = 1; i < argc; ++i){
printf("%s ", argv[i]);
}
printf("\n\n");
return 0;
}