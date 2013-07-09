/****************************************************************************
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 ***************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCKSIZE 512
typedef uint8_t  BYTE;

int main(void)
{
    char* outfilename = (char*) malloc(sizeof(char)*10);
    FILE* fp = fopen("card.raw", "r");
    BYTE block[BLOCKSIZE];
    int n = -1;  
    FILE* outp ;
    while( fread(&block, sizeof(BYTE), BLOCKSIZE, fp) == BLOCKSIZE )
    {
        if( (block[0]==0xff && block[1]==0xd8 && block[2]==0xff && (block[3]==0xe0 || block[3]==0xe1) ) )
        {            
            if (n>-1)
                fclose(outp);
            n++;
            sprintf(outfilename, "%.3d.jpg", n); 
            //printf("%s\n", outfilename);           
            outp = fopen(outfilename, "w");
        }
        if (n > -1)
        {
            fwrite(&block, sizeof(BYTE), BLOCKSIZE, outp);
        }               
    }
    fclose(outp);    
    fclose(fp);
    return 0;
}
