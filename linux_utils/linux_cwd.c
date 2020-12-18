#include "stdlib.h"
#include "unistd.h"
#include "stdio.h"

int main(int agrc ,char *argv[] )
{
    char *pwd = 0;

    printf("this program is show the usage of getcwd function\n");
    pwd = malloc(256);
    getcwd(pwd, 256);
    printf("the current worksapce is:\n    %s\n", pwd);
    free(pwd);
}


