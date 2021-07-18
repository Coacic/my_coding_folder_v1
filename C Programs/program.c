#include <stdio.h>
#include <conio.h>
#define CHARBIT 8
void main () {
   unsigned char arr[3] = {0x34, 017}, x, c = 0;
   int i, n = sizeof(arr) / sizeof(unsigned char);
   for (i = 0; i < n; i++) {
      x = arr[i];
      x ^= x >> 4;
      x ^= x >> 2;
      x ^= x >> 1 ;
      arr[i] |= (x & 1 && ++c) << CHARBIT - 1;
   }
   for (; i > 0; printf("%hhx ", arr[--i]));
      printf("%d\n", c);

    _getch();
}