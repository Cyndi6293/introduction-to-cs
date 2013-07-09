#include <stdio.h>

#define SIZE 9
void sort(int array[], int size)
{
    // TODO: sort array using any algorithm
    //base case to stop recursion
    if (size < 2 )
        return; 
    //Determine sizes of subarrays, considering size may be odd number    
    int fSize, sSize;
    if (size%2 ==1)
    {
        fSize = size/2;
        sSize = size/2 + 1;
    }
    else
    {
        fSize = sSize = size/2;
    } 
    //split into subarrays, based on sizes of subarrays, determined in section above 
    int firstHalf[ fSize ], secondHalf[ sSize ];
    for (int i=0; i < fSize; i++)
        firstHalf[i]=array[i];
    for (int j=0, i=fSize; i < size; j++, i++)
        secondHalf[j]=array[i];
    //recursivelly call our function, to split everything into 1-element arrays    
    sort(firstHalf,  fSize);
    sort(secondHalf,  sSize);
    //Start merging monsters of our creation
    //Merge subarrays into combined sorted bigger array(that is transform original) untill one of subs is depleted
    //i-iteration variable for combined array; j-first half; k- second
    int  i=0,j=0, k=0;    
    while (j < fSize && k < sSize)
    {
        if (firstHalf[j] < secondHalf[k])
        {
            array[i++] = firstHalf[j++];
        }
        else 
        {
            array[i++] = secondHalf[k++];
        }
    }
    //Check wich of subs was depleted
    //if it's the fisrt part, just add rest of the second into comb
    if (j==fSize)
        while (i<size)
            array[i++] = secondHalf[k++];
    //if the second part happend to have been depleted, drain the first one into the rest of comb array        
    else
        while (i<size)
            array[i++] = firstHalf[j++];  
}

int main(void)
{
    int numbers[SIZE] = { 4, 15, 16, 50, 8, 23, 42, 108, 19 };
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    sort(numbers, SIZE);
    for (int i = 0; i < SIZE; i++)
        printf("%d ", numbers[i]);
    printf("\n");
    return 0;
}
