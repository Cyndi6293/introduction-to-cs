#include <stdio.h>
#include <stdlib.h>
#define LEN 10

int main(void)
{
    char* buffer[LEN];
    FILE* fp = fopen("a.txt", "r");
    int i = 0;
    while (i < LEN)
    {
        buffer[i] = malloc( 50*sizeof(char) );
        fscanf (fp, "%s", buffer[i]);
        printf("%s\n", buffer[i]);
        i++;
    } 
    fclose(fp);
    //
    printf("-------------------\n");
    char* a = "asdddffff";
    char* b = malloc( 20*sizeof(char) );
    b = a;
    a = "";
    printf("%s, %s\n", a, b);
    //
    printf("-------------------\n");  
    FILE* fp2 = fopen("a.txt", "r");
    char* werd = malloc( 50*sizeof(char) );
    while ( fscanf (fp2, "%s", werd) != EOF )
    {      
        printf("%s\n", werd);        
    } 
    fclose(fp2);
}

