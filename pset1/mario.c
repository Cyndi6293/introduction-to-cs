#include <stdio.h>
#include <cs50.h>
int main()
{
    int height=-1;
    //loop to get correct input
    while (height<0 || height>23)
    {
        printf("Enter height of the pyramid: ");
        height=GetInt();
    } //end of while
    //Drawing loop    
    for(int i=1; i<=height; i++)
    {
        //spaces
        for(int j=1; j<=height-i; j++)
        {
            printf(" ");
        } //end of for
        //hashes
        for(int j=1; j<=i+1; j++)
        {
            printf("#");
        } //end of for
        //newline before next iteration
        printf("\n");
    } //end of for
    return 0;
} //end of main()
