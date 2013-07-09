#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    printf("Enter the string\n");
    string s=GetString();
    for(int i=0; i<strlen(s); i++)
    {
        if(i%2==1)
        {
            if(s[i]<=90 && s[i]>=65) 
                s[i]+=32;
            else if(s[i]<=122 && s[i]>=97)
                s[i]-=32;
        }
        printf("%c", s[i]);
    }
    printf("\n");
    return 1;
}
