#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main (int argc, string argv[])
{
    if (argc!=2)
    {
        printf("You did wrong!\n");
        return 1;
    }
    int k = atoi( argv[1] ) % 26;
    //printf("String: ");
    string str=GetString();
    for (int i = 0; i < strlen(str); i++)
    {
        if(str[i]<=90 && str[i]>=65) 
                str[i]=65 + ( str[i]-65 + k )%26;
        else if(str[i]<=122 && str[i]>=97)
                str[i]=97 + ( str[i]-97 + k )%26;
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}
