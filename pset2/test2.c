#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main()
{

    int N=25;
    for(int i=0, j=0; i<N; i++)
    {
        j=(j+1) % 5;
        printf("%d\n", j);
    }
    printf("\n");
}
