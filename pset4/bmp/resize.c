/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);
    // remember filenames
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
    bf.bfSize = bf.bfSize * n;
    

    // read infile's BITMAPINFOHEADER
    //copy old info somewhere
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //printf("%d\n", n);
    //printf("%d %d %d\n", bi.biWidth, bi.biHeight, bi.biSizeImage);
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    int newpadding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (newpadding * abs(bi.biHeight)) + (bi.biWidth * abs(bi.biHeight) * 3);
    bf.bfSize = bi.biSizeImage + 54;
    //bi.biSizeImage = bi.biSizeImage * n;
    //printf("%d %d %d\n", bi.biWidth, bi.biHeight, bi.biSizeImage);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        /*
        if (bf.bfType != 0x4d42) {printf("71\n");}
        if (bf.bfOffBits != 54) {printf("72\n");}
        if (bi.biSize != 40) {printf("73\n");}
        if (bi.biBitCount != 24) {printf("74\n");}
        if (bi.biCompression != 0) {printf("75\n");}*/
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    // TODO: PADDING IS CURRENTLY VERY BROKEN
    int padding =  (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    int tempHeight = abs(oldHeight);
    // iterate over infile's scanlines
    for (int i = 0; i < tempHeight; i++)
    {
        RGBTRIPLE line[bi.biWidth];
        int position = 0;
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
            // write RGB triple to outfile
            //printf("%d", n);
            for (int x = 0; x < n;  x++)
            {
                //fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                line[position] = triple;
                position++;
            }
        }
        fseek(inptr, padding, SEEK_CUR);
        for (int y = 0; y < n; y++) 
        {
            fwrite(line, sizeof(RGBTRIPLE), bi.biWidth, outptr);
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
            
        }
        // skip over padding, if any
        /*fseek(inptr, padding, SEEK_CUR);
        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }   */
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
