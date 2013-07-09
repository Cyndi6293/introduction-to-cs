#include <cs50.h>
#include <stdio.h>

#define SIZE 8

bool search(int needle, int haystack[], int size)
{
    // TODO: return true iff needle is in haystack, using binary search
    for (int i=0; i < size; i++)
    {
        if (haystack[i] == needle)
            return true;
    }
    return false;
}

int main(void)
{
    int numbers[SIZE] = { 4, 8, 15, 16, 23, 42, 50, 108 };
    printf("> ");
    int n = GetInt();
    if (search(n, numbers, SIZE))
        printf("YES\n");
    return 0;
}
