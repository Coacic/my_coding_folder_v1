#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
    int a[10] = {10, 15, 11};
    int b = (*a);
    printf("%d\n%d\n%d", b, a, &a[1]);
    //a = 0b10101;
    //hex = 0x15;
    //octal = 015;
}