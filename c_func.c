#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

extern double imgCvtGrayIntToDouble(long long int ia1);

int main(int argc, char* argv[]) {

	int height = 0;							// declare variables
	int width = 0;
	long long int* pixels = NULL;
	double new_pixel = 0.0;
	int i;

	scanf_s("%d %d", &height, &width);				// ask for height and width, assume input is correct

	long long int area = height * width;			// get area of image, for loop counter and size of pointer needed

	pixels = (long long int*)malloc(area * sizeof(long long int));
													// alloc space for pixels to be stored
		
	for (int i = 0; i < area; i++) {				// collect input in loop
		if ((i + 1) % width == 0)
			scanf_s("%lld ", &pixels[i]);
		else 
			scanf_s("%lld, ", &pixels[i]);
	}

	clock_t start, end;
	double cpu_time_used = 0;

	for (i = 0; i < area; i++) {					// calculate and print new value for pixels
		start = clock();
		new_pixel = imgCvtGrayIntToDouble(pixels[i]);		// assembly function for calculation
		end = clock();
		cpu_time_used += ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("%.2f ", new_pixel);
		if ((i + 1) % width == 0)
			printf("\n");
	}
	
	printf("Execution time: %.6f seconds\n", cpu_time_used);

	return 0;
}
