#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;
   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
   double integral = 0.0;
   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   for (int i = 0; i < fourier_arg.n_terms; i++) {
      fourier_arg.a_i[i] = 0.0;
      fourier_arg.b_i[i] = 0.0;
   }
}
