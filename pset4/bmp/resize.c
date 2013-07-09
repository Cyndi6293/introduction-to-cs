/****************************************************************************
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    
    int n = atoi(argv[1]);
    if( n<1 && n>100)
    {
        printf("Scaling factor is between 1 and 100\n");
        return 4;
    }
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // determine padding for scanlines in infile
    int inpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;    
    int oldWidth = bi.biWidth;
    int oldHeight = abs(bi.biHeight) ;
    
    //Change resolution in header info
    bi.biWidth *= n;
    bi.biHeight *= n;   
    
    //Create input array to save input image's pixels
    RGBTRIPLE inarray[oldWidth][oldHeight];       
    // determine padding for scanlines in outfile
    int outpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; 
    
    // iterate over infile's scanlines and fill inarray    
    for (int i = 0; i < oldHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            inarray[i][j] = triple;
            //printf("%.2x%.2x%.2x ", inarray[i][j].rgbtBlue,inarray[i][j].rgbtGreen,inarray[i][j].rgbtRed);            
            
        }
        //printf("\n");
        // skip over padding, if any
        fseek(inptr, inpadding, SEEK_CUR);       
    }    
    //printf("\n");
    
    //Outarray. Create it 
    RGBTRIPLE outarray[bi.biWidth][abs(bi.biHeight)];  
    //Now, to filling outarray   
    for (int nn=0, mm=0, i = 0; i < oldHeight && mm+n <= abs(bi.biHeight); i++)    
    {
        nn=0;
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth && nn+n <= bi.biWidth; j++)
        {
            for (int k=0; k<n; k++)
            {
                for (int l=0; l<n; l++)
                {
                    outarray[mm+k][nn+l] = inarray[i][j];
                }
            } 
            nn+=n;                       
        }
        mm+=n;         
    }
    //Calculate img size in bytes    
    bf.bfSize = sizeof(bf)+sizeof(bi)+sizeof(outarray)+outpadding*abs(bi.biHeight)*sizeof(BYTE);
    bi.biSizeImage = sizeof(outarray)+outpadding*abs(bi.biHeight)*sizeof(BYTE);
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //Aaand writing outarray to file
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // write RGB triple to outfile
            fwrite(&outarray[i][j], sizeof(RGBTRIPLE), 1, outptr);
            //printf("%.2x%.2x%.2x ", outarray[i][j].rgbtBlue, outarray[i][j].rgbtGreen, outarray[i][j].rgbtRed);
        }         
        //add some padding to file
        for (int k = 0; k < outpadding; k++)
        {
           //printf("%.2x", 0x00);
           fputc(0x00, outptr);
        }   
        //printf("\n");
    }     
    
    // close infile    
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
