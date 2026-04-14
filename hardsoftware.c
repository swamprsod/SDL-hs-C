#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("выберите то что нужно\n");
    printf(" \n");
    printf("1 = cpu model\n");
    printf("2 = ram\n");
    printf("3 = gpu model\n");
    printf("4 = disk (/)\n");
    printf("5 = kernel name\n");
    printf("6 = display\n");
    printf("7 = everything\n");
    printf(" \n");
int a
    while (1)
{
    scanf("%d", &a);
    if (a==1)
{
    system("echo \"ваша модель процессора:\" && cat /proc/cpuinfo | grep \"model name\" | head -n 1 | cut -d':' -f2 | sed 's/model name\\s*//'");
    break;
}
    if (a==2)
    system("echo \
}
}
