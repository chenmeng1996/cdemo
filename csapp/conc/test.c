#include "stdio.h"
int main()
{
    int i;
    for (i = 0; i < 2; i++) {
        int a = i;
        printf("%d, %p\n", a, &a);
        printf("%d, %p\n", i, &i);
    }
}