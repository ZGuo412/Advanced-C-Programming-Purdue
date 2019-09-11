#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"

int main(int argc, char ** argv) {

   Integrand integrand = {
	   .upper_limit = 0.0,  // TODO: change to the real value
	   .lower_limit = 10.0, // TODO: change to the real value
	   .n_intervals = 5,    // TODO: change to the real value

   };

   int n_terms = 1;         // TODO: change to the real value

   Fourier fourier = {
	   .intg      = integrand,
	   .n_terms   = n_terms,
	   .a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
	   .b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
   };

   // If allocation of fourier.a_i and/or fourier.b_i failed, then free the
   // one that didn't fail and then exit with EXIT_FAILURE.
   if (fourier.a_i == NULL || fourier.b_i == NULL) {
      free(fourier.a_i);  // free(..) has not effect if its argument is NULL
      free(fourier.b_i);
      return EXIT_FAILURE;
   }

   fourier_coefficients(fourier);

   print_fourier_coefficients(fourier.a_i, fourier.b_i, 
                              fourier.n_terms);

   free(fourier.a_i);
   free(fourier.b_i);

   return EXIT_SUCCESS;
} 
