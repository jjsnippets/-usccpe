#include <stdio.h>
#include <math.h>
#include <tgmath.h>
#include <complex.h>


double complex Xjw(double w){
	return (1 / (I * w)) * (-exp(I * 2 * w) - 3 + 3 * exp(-I * w) + 2 * exp(-I * 3 * w))
		+ (1 / (w * w)) * (-exp(I * 3 * w) + exp(I * 2 * w) + 2 * exp(-I * 3 * w) - 2 * exp(-I * 4 * w));
}
