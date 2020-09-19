#include <stdio.h>
#include <stddef.h>
#include <stdint.h>


void printBits(size_t size, void const *ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
        printf(" ");
    }
}

int		main(void)
{
    int dir_size = 4;
	unsigned int num = 1 + 2 + 4 + 8  + 32 + 64 + 128 + 256 + 1024 + 2048;
    unsigned short b = 1 + 2 + 4;
	unsigned char c;
    unsigned char code[10];

    int i = 0;
    while (dir_size != 0)
    {
        code[i] = num >> (8 * (dir_size - 1));
        dir_size--;
        i++;
    }
    int j = 0;
    while (j != i)
    {
        printBits(sizeof(char), &(code[j]));
        j++;
    }

	return (0);
}
//unsigned int      4 bytes
//unsigned short    2 bytes
//unsigned char     1 byte
