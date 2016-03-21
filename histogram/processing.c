/*
   ============================================================================
   Name        : processing.c
   Author      : 359234
   Copyright   : 359234@mail.muni.cz
   Description : Histogram processing
   ============================================================================
 */

#include <stdio.h>
#include "processing.h"
#include <string.h>

/***********************************************************************************/

void ComputeHistogram(unsigned int *hist, const unsigned char *img, size_t histSize, size_t imgSize)
{
        memset (hist,0,histSize*sizeof(unsigned int));

        for(unsigned int i = 0; i < imgSize; i++) {
                *(hist + img[i]) += 1;
        }
}

/***********************************************************************************/

void ComputeCumulative(unsigned int *cumulative, const unsigned int *hist, size_t histSize)
{
        unsigned int tmp = 0;

        memset (cumulative,0,histSize*sizeof(unsigned int));

        for(unsigned int i = 0; i < histSize; i++) {

                tmp += hist[i];
                *(cumulative + i) = tmp;
        }
}

/***********************************************************************************/

void Equalize(unsigned char *output, const unsigned char *input, const unsigned int *cumulative, size_t imgSize, size_t maxVal)
{
        double alpha = (double) maxVal/imgSize;
        memset (output,0,imgSize);

        for(unsigned int i=0; i < imgSize; i++)
                *(output + i) = cumulative[input[i]] * alpha;

}

void Threshold(unsigned char *bin, const unsigned char *img, size_t imgSize, unsigned char thresh)
{
        memset (bin,0,imgSize);

        for (unsigned int i=0; i < imgSize; i++) {
                if (img[i] > thresh)
                        *(bin+i) = 1;
                else
                        *(bin+i) = 0;
        }

}

/***********************************************************************************/

void PrintHistogram(const unsigned int *hist, size_t histSize)
{
        unsigned int maxValue = 0;


        for(unsigned int j = 1; j< histSize; j++) {
                if (hist[0] > hist[j] && (hist[0] > maxValue)) maxValue = hist[0];
                if (hist[0] < hist[j] && (hist[j] > maxValue)) maxValue = hist[j];
        }


        printf(".");
        for(unsigned int i = 0; i < histSize; i++)
                printf("-");
        printf(".\n");

        for(unsigned int j = 0; j < maxValue; j++) {
                for(unsigned int i = 0; i <= histSize; i++) {
                        if (i == 0 ) printf("|");
                        if (i == histSize ) printf("|\n");

                        if ((i != histSize) &&  ((hist[i]+j) >= maxValue)) printf("*");
                        if ((i != histSize) && ((hist[i]+j) < maxValue)) printf(" ");
                }
        }

        printf(".");
        for(unsigned int i = 0; i < histSize; i++)
                printf("-");
        printf(".\n");
        printf("\n");
        printf("\n");

}

void PrintBinaryImage(const unsigned char *img, size_t sizeX, size_t sizeY)
{
        printf(".");
        for(unsigned int i = 0; i < sizeX; i++)
                printf("-");
        printf(".\n");


        for(unsigned int j = 0; j < sizeY; j++) {
                for(unsigned int i = 0; i <= sizeX; i++) {
                        if (i == 0) printf ("|");
                        if (i == sizeX) printf("|\n");

                        if ((i != sizeX) && (img[(sizeX*j)+i] == 1)) printf("*");
                        if ((i != sizeX) && (  (img[(sizeX*j)+i] == 0) ) ) printf(" ");
                }
        }

        printf(".");
        for(unsigned int i = 0; i < sizeX; i++)
                printf("-");
        printf(".\n");
        printf("\n");
        printf("\n");
}
