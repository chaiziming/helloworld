#include <stdio.h>

int main(int argc, char const *argv[])
{
    fopen("unknow.txt", "r");
    perror("我这不知道");
    return 0;
}
