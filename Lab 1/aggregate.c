#include <stdio.h>

struct pkt
{
    unsigned char ch1;
    unsigned char ch2[2];
    unsigned char ch3;
};

int main()
{

    unsigned int value = 0x11223344;

    int a, b, c, d;

    a = (value & 0xFF);
    b = ((value >> 8) & 0xFF);
    c = ((value >> 16) & 0xFF);
    d = ((value >> 24) & 0xFF);

    struct pkt *pktObj;

    pktObj->ch1 = a;
    pktObj->ch2[0] = b;
    pktObj->ch2[1] = c;
    pktObj->ch3 = d;
    int integerValue = 50000;
    printf("\n%e\n", integerValue);
    printf("char1= %.2x", pktObj->ch1);
    printf("\nchar2[0]= %.2x", pktObj->ch2[0]);
    printf("\nchar2[1]= %.2x", pktObj->ch2[1]);
    printf("\nchar3= %.2x", pktObj->ch3);

    int val = ((int)(pktObj->ch3 << 24) + (int)(pktObj->ch2[1] << 16) + (int)(pktObj->ch2[0] << 8) + (int)(pktObj->ch1));
    printf("\n%d", val);

    return 0;
}