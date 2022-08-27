#include <stdio.h>
#include <winsock.h>

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
int main()
{
    int a, b;
    printf("Enter Num 1: ");
    scanf("%d", &a);
    printf("EnterNum 2: ");
    scanf("%d", &b);

    printf("Before Swapping: \n Num 1 = %d \n Num 2 = %d", a, b);

    swap(&a, &b);
    printf("\nAfter Swapping: \n Num 1 = %d \n Num 2 = %d", a, b);
    return 0;
}