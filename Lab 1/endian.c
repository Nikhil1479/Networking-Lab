#include <stdio.h>

void print(char *val, int n)
{
    printf("Little Endian\n");
    for (int i = 0; i < n; i++)
    {
        printf("%.2x, ", val[i]);
    }

    printf("\n\nBig Endian\n");
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%.2x, ", val[i]);
    }
}
int main()
{
    int i = 1;

    char *p = (char *)&i;
    if (*p == 1)
    {
        printf("\nYour host machine is Little Endian\n\n");
    }
    else
    {
        printf("\nYour host machine is Big Endian\n\n");
    }

    print((char *)&i, sizeof(i));
    return 0;
}