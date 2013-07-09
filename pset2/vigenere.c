#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if( argc!=2 )
    {
        printf("Wrong!\n");
        return 1;
    }
    for (int i=0; i<strlen( argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Wrong!\n");
            return 1;
        }
    }
    string str=GetString();
    int N= strlen(str);
    for(int i=0, j=0; i<N; i++)
    {
        if ( isupper(str[i]) )
        {
             str[i]=65 + ( str[i]-65 + (isupper( argv[1][j] ) ? argv[1][j]-65 : argv[1][j]-97) )%26;
             j=(j+1) % strlen(argv[1]);
        }
        else if ( islower(str[i]) )
        {
            str[i]=97 + ( str[i]-97 + (isupper( argv[1][j] ) ? argv[1][j]-65 : argv[1][j]-97) )%26;
            j=(j+1) % strlen(argv[1]);
        }
        //printf("%d", j);
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}
