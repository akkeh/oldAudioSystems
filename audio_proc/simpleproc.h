#ifndef SIMPLE_PROC_H
#define SIMPLE_PROC_H

double c_abs(double a, double b);
double d_abs(double a);
double clip(double a, double low, double hi); 

void c_mul(double a, double b, double c, double d, double* r, double* i);

double* decimate(double const* arr, unsigned long int N);
#endif
