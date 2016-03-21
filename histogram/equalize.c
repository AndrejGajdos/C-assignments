#include <stdio.h>
#include <stdlib.h>
#include "processing.h"

const size_t INPUT_BUFFER = 1024;
const size_t INPUT_MAX = 255;

void LoadImage(const char *fileName, unsigned char *image, size_t *imgSize);
void SaveImage(const char *fileName, unsigned char *image, size_t imgSize);

/***********************************************************************************/
/***********************************************************************************/

int main(int argc, char *argv[])
{
	if(argc != 6)
	{
		printf("Usage: <program> imageFile maxValue sizeX sizeY threshold");
		return 1;
	}

	const char *image = argv[1];
	size_t maxVal = atoi(argv[2]);
	size_t sizeX = atoi(argv[3]);
	size_t sizeY = atoi(argv[4]);
	unsigned char thresh = atoi(argv[5]);

	// Here will be the logic loading a input file
	size_t imageSize;
	size_t histSize = maxVal != 0 ? maxVal+1 : 0;
	unsigned char input[INPUT_BUFFER], output[INPUT_BUFFER], binary[INPUT_BUFFER];
	unsigned int histogram[INPUT_MAX+1], cumulative[INPUT_MAX+1];
	LoadImage(image, input, &imageSize);

	//Compute and print the binary image of the input image
	Threshold(binary, input, imageSize, thresh);
	printf("Input image, range [0, %lu] thresholded with [%u]:\n", maxVal, thresh);
	PrintBinaryImage(binary, sizeX, sizeY);

	// Compute and print the histogram of the input image
	ComputeHistogram(histogram, input, histSize, imageSize);
	printf("Input image histogram:\n");
	PrintHistogram(histogram, histSize);

	// Compute and print the cumulative histogram
	ComputeCumulative(cumulative, histogram, histSize);
	//PrintHistogram(cumulative, maxVal+1);

	// Equalize the image based on the cumulative histogram
	Equalize(output, input, cumulative, imageSize, maxVal);

	//Compute and print the binary image of the output image
	Threshold(binary, output, imageSize, thresh);
	printf("Output image, range [0, %lu] thresholded with [%u]:\n", maxVal, thresh);
	PrintBinaryImage(binary, sizeX, sizeY);

	// Compute and print the histogram of the output image
	ComputeHistogram(histogram, output, histSize, imageSize);
	printf("Output image histogram:\n");
	PrintHistogram(histogram, histSize);

	return 0;
}

/***********************************************************************************/

void LoadImage(const char *fileName, unsigned char *image, size_t *imgSize)
{
	FILE *file = NULL;

	// Open the file
	if((file = fopen(fileName, "rt")) == NULL)
	{
		fprintf(stderr, "Error opening image <%s>!\n", fileName);
		exit(2);
	}

	// Load the pixels
	unsigned int pixel;
	int count;
	*imgSize = 0;
	do
	{
		count = fscanf(file, "%u", &pixel);

		if(count == EOF)
			break;

		image[*imgSize] = (unsigned char)pixel;
		(*imgSize)++;
	} while(1);

	// Close the file
	if(file)
		fclose(file);
}

/***********************************************************************************/

void SaveImage(const char *fileName, unsigned char *image, size_t imgSize)
{
	FILE *file = NULL;

	// Open the file
	if((file = fopen(fileName, "wt")) == NULL)
	{
		fprintf(stderr, "Error opening image <%s>!\n", fileName);
		exit(3);
	}

	// Write the pixels
	for(size_t i = 0; i < imgSize; i++)
	{
		fprintf(file, "%u ", image[i]);
	}

	// Close the file
	if(file)
		fclose(file);
}
