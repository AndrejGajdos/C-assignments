/** @file processing.h*/

/**
 * Compute histogram of the given image
 *
 * @param [out] hist         histogram to compute
 * @param [in]  img          input image
 * @param [in]  histSize     histogram size
 * @param [in]  imgSize      image size
 * @return                   nothing
 */
void ComputeHistogram(unsigned int *hist, const unsigned char *img, size_t histSize, size_t imgSize);

/**
 * Compute cumulative histogram from the given histogram
 *
 * @param [out] cumulative   histogram to compute
 * @param [in]  hist         input histogram
 * @param [in]  histSize     histogram size
 * @return                   nothing
 */
void ComputeCumulative(unsigned int *cumulative, const unsigned int *hist, size_t histSize);

/**
 * Equalize the given image based on the cumulative histogram
 *
 * @param [out] output       image after equalization
 * @param [in]  input        input image
 * @param [in]  cumulative   cumulative histogram of the input image
 * @param [in]  imgSize      image size
 * @param [in]  maxVal       maximal value of the image type
 * @return                   nothing
 */
void Equalize(unsigned char *output, const unsigned char *input, const unsigned int *cumulative, size_t imgSize, size_t maxVal);

/**
 * Compute binary image from the given image by thresholding
 *
 * @param [out] bin          computed binary image
 * @param [in]  img          input image
 * @param [in]  imgSize      image size
 * @param [in]  thresh       threshold value to use
 * @return                   nothing
 */
void Threshold(unsigned char *bin, const unsigned char *img, size_t imgSize, unsigned char thresh);

/**
 * Prints the given histogram
 *
 * @param [in]  hist         histogram to print
 * @param [in]  histSize     histogram size
 * @return                   nothing
 */
void PrintHistogram(const unsigned int *hist, size_t histSize);

/**
 * Prints the binary image
 *
 * @param [in]  img          binary image to print
 * @param [in]  sizeX        size of the image in the x-dimension
 * @param [in]  sizeY        size of the image in the y-dimension
 * @return                   nothing
 */
void PrintBinaryImage(const unsigned char *img, size_t sizeX, size_t sizeY);
