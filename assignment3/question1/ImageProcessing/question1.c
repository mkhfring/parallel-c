/**************************************************************

 The program reads a BMP image file and creates a new
 image that is the negative or desaturated of the input file.

 **************************************************************/

#include "qdbmp.h"
#include <stdio.h>
#include <omp.h>

typedef enum {desaturate, negative} ImgProcessing ;

/* Creates a negative image of the input bitmap file */
int main() {
	const char* inFile = "okanagan.bmp";
	const char* outFile = "okanagan_processed.bmp";
	const ImgProcessing processingType = desaturate; //or negative

	UCHAR r, g, b;
	UINT width, height;
	UINT x, y;
	BMP* bmp;
	int numThread = 8;

	/* Read an image file */
	bmp = BMP_ReadFile(inFile);
	BMP_CHECK_ERROR(stdout, -1);

	/* Get image's dimensions */
	width = BMP_GetWidth(bmp);
	height = BMP_GetHeight(bmp);



	double t = omp_get_wtime();
	/* Iterate through all the image's pixels */
    #pragma omp parallel num_threads(numThread) private(x, y, r, g, b)
	{
	int myId = omp_get_thread_num();
	int myWidth = width / numThread;
	int start = myId * myWidth;
	int end = start + myWidth;
//	printf("The interval for thread number %d is [%d, %d]\n", myId, start, end);
	for (x = start; x < end; ++x) {
		for (y = 0; y < height; ++y) {
			/* Get pixel's RGB values */
			BMP_GetPixelRGB(bmp, x, y, &r, &g, &b);

			/* Write new RGB values */
			if(processingType == negative)
				BMP_SetPixelRGB(bmp, x, y, 255 - r, 255 - g, 255 - b);
			else if(processingType == desaturate){
				UCHAR gray = r * 0.3 + g * 0.59 + b * 0.11;
				BMP_SetPixelRGB(bmp, x, y, gray, gray, gray);
			}

		}

	}
    }
	/* calculate and print processing time*/
	t = 1000 * (omp_get_wtime() - t);
	printf("Finished image processing in %.1f ms.", t);

	/* Save result */
	BMP_WriteFile(bmp, outFile);
	BMP_CHECK_ERROR(stdout, -2);

	/* Free all memory allocated for the image */
	BMP_Free(bmp);

	return 0;
}

/*
 For the sequential code: Finished image processing in 145.9 ms.

 For parallel with 2 threads: Finished image processing in 126.2 ms.

 For parallel with 4 threads: Finished image processing in 180.5 ms.

 For parallel with 8 threads: Finished image processing in 283.6 ms.

 For parallel with 16 threads: Finished image processing in 282.5 ms.

 */

