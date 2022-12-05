%%cuda --name Julia_set.cu --compile true

#include <stdio.h>
#include "EasyBMP.h"
#include "EasyBMP.cu"

//Complex number definition
struct Complex {	// typedef is not required for C++
	float x; 				// real part is represented on x-axis in output image
	float y; 				// imaginary part is represented by y-axis in output image
};

//Function declarations
void compute_julia(const char*, int, int);
void save_image(uchar4*, const char*, int, int);
__device__ Complex add(Complex, Complex);
__device__ Complex mul(Complex, Complex);
__device__ float mag(Complex);

//main function
int main(void) {
	char* name = "test.bmp";
	compute_julia(name, 3000, 3000);	//width x height
	printf("Finished creating %s.\n", name);
	return 0;
}

// serial implementation of Julia set
__global__ void compute_julia_cuda(int width, int height, float x_min, float y_min, float x_incr, float y_incr, uchar4 *p, int infinity, int max_iterations, Complex c1){
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	if (col < width && row < height){		
		Complex z;
		z.x = x_min + col * x_incr;
		z.y = y_min + row * y_incr;
		int n = 0;
		do{
			z = add(mul(z, z), c1);								// z = z^2 + c
		} while (mag(z) < infinity && n++ < max_iterations);	// keep looping until z->infinity or we reach max_iterations
		if (n == max_iterations) {								// if we reach max_iterations before z reaches infinity, pixel is black 
			p[col + row * width] = { 0,0,0,0 };
		} else {												// if z reaches infinity, pixel color is based on how long it takes z to go to infinity
			unsigned char hue = (unsigned char)(255 * sqrt((float)n / max_iterations));
			p[col + row * width] = { hue,hue,hue,255 };
		}
				
	}

}


void compute_julia(const char* filename, int width, int height) {
	//create output image
	uchar4 *pixels = (uchar4*)malloc(width * height * sizeof(uchar4));	//uchar4 is a CUDA type representing a vector of 4 chars

	//PROBLEM SETTINGS (marked by '******')
	// **** Accuracy ****: lower values give less accuracy but faster performance
	int max_iterations = 400;
	int infinity = 20;													//used to check if z goes towards infinity

	// ***** Shape ****: other values produce different patterns. See https://en.wikipedia.org/wiki/Julia_set
	Complex c = { 0.285, 0.01 }; 										//the constant in z = z^2 + c

	// ***** Size ****: higher w means smaller size
	float w = 4;
	float h = w * height / width;										//preserve aspect ratio

	// LIMITS for each pixel
	float x_min = -w / 2, y_min = -h / 2;
	float x_incr = w / width, y_incr = h / height;
	
	//****************************************************
	//REQ: Parallelize the following for loop using CUDA 
	//****************************************************
	uchar4 *d_pixels;
	int size = width * height * sizeof(uchar4);
	cudaMalloc(&d_pixels, size);
	cudaMemcpy(d_pixels, pixels, size, cudaMemcpyHostToDevice);
	dim3 grid, block;
	block.x = 32;	
	block.y = 32;
	grid.x = (width -1) / block.x + 1;
	grid.y = (width -1) / block.y + 1;
	compute_julia_cuda<<<grid, block>>>(width, height, x_min, y_min, x_incr, y_incr, d_pixels, infinity, max_iterations, c);
	cudaDeviceSynchronize();

	cudaMemcpy(pixels, d_pixels, size, cudaMemcpyDeviceToHost);

	//Write output image to a file (DO NOT parallelize this function)
	save_image(pixels, filename, width, height);

	//free memory
	cudaFree(d_pixels);
	free(pixels);
}

void save_image(uchar4* pixels, const char* filename, int width, int height) {
	BMP output;
	output.SetSize(width, height);
	output.SetBitDepth(24);
	// save each pixel to output image
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			uchar4 color = pixels[col + row * width];
			output(col, row)->Red = color.x;
			output(col, row)->Green = color.y;
			output(col, row)->Blue = color.z;
		}
	}
	output.WriteToFile(filename);
}

__device__ Complex add(Complex c1, Complex c2) {
	return{ c1.x + c2.x, c1.y + c2.y };
}

__device__ Complex mul(Complex c1, Complex c2) {
	return{ c1.x * c2.x - c1.y * c2.y, c1.x * c2.y + c2.x * c1.y };
}

__device__ float mag(Complex c) {
	return (float)sqrt((double)(c.x * c.x + c.y * c.y));
}

