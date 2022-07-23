#include <stdio.h>
struct info
{
    int rollNo;
    char name[50];
    float cgpa;
};

void input(struct info *myInfo)
{
    printf("\nEnter roll: ");
    scanf("%d", &myInfo->rollNo);

    printf("\nEnter name: ");
    scanf("%s", &myInfo->name);

    printf("\nEnter CGPA: ");
    scanf("%f", &myInfo->cgpa);
}

void display(struct info *info)
{
    printf("\nName: %s:, \nRoll No: %d, \nCGPA: %f", info->name, info->rollNo, info->cgpa);
}
int main()
{
    struct info s1, s2, s3;

    input(&s1);
    input(&s2);

    printf("\n\n");
    display(&s1);
    printf("\n");
    display(&s2);

    return 0;
}