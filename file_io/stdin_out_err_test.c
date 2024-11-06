#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ch = malloc(100);
    fgets(ch, 100, stdin);
    printf("你好：%s", ch);
    fputs(ch, stdout);
    printf("\n");
    fputs(ch, stderr);
    printf("\n");
    return 0;
}
