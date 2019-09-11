#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

double simpson_numerical_integration(Integrand intg_arg) {
   double integral = 0.0;
   double interval = 0.0;
   double lowerl = intg_arg.lower_limit;
   double upperl = 0.0;
   if(intg_arg.n_intervals < 1)
   {
   intg_arg.n_intervals = 1;
   }
   interval = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
 
   if(intg_arg.upper_limit > intg_arg.lower_limit)
   {
     for(int i = 1; i <= intg_arg.n_intervals;i++)
     {
       upperl = intg_arg.lower_limit + interval * i;
       integral += (interval / 6) * (intg_arg.function_to_be_integrated(lowerl) + 4 * (intg_arg.function_to_be_integrated((lowerl + upperl) / 2)) + intg_arg.function_to_be_integrated(upperl));
	   lowerl = upperl;
     }

   }
   
   if(intg_arg.lower_limit > intg_arg.upper_limit)
   {
     lowerl = intg_arg.upper_limit;
     for(int i = 1; i <= intg_arg.n_intervals ;i++)
     {
	   upperl = intg_arg.upper_limit - interval * i;
       integral += (interval / 6) * (intg_arg.function_to_be_integrated(lowerl) + 4 * (intg_arg.function_to_be_integrated((lowerl + upperl) / 2)) + intg_arg.function_to_be_integrated(upperl));
	   lowerl = upperl;
     }
   }
   
   return integral;
}

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) {
   double integral = 0.0;
   double interval = 0.0;
   double lowerl = intg_arg.lower_limit;
   double upperl = 0.0;
   
   if(intg_arg.n_intervals < 1)
   {
     intg_arg.n_intervals = 1;
   }
   interval = (intg_arg.upper_limit - intg_arg.lower_limit) / intg_arg.n_intervals;
   double cossin1 = 0;
   double cossin2 = 0;
   double cossin3 = 0;
   double L = 0.0;
   if(intg_arg.upper_limit > intg_arg.lower_limit)
   { 
     L = (intg_arg.upper_limit - intg_arg.lower_limit) / 2.0;
     for(int i = 1; i <= intg_arg.n_intervals;i++)
     {
	   upperl = intg_arg.lower_limit + interval * i;
	   cossin1 = cos_sin(n * M_PI * lowerl / L);
	   cossin2 = cos_sin((n * M_PI * (lowerl + upperl) / 2.0) / L);
	   cossin3 = cos_sin(n * M_PI * upperl / L);
       integral += (interval / 6) * (intg_arg.function_to_be_integrated(lowerl) * cossin1 + 4 * intg_arg.function_to_be_integrated((lowerl + upperl) / 2) * cossin2 + intg_arg.function_to_be_integrated(upperl) * cossin3);
	   lowerl = upperl;
     }  

   }
   
   if(intg_arg.lower_limit > intg_arg.upper_limit)
   {
       L = (intg_arg.lower_limit - intg_arg.upper_limit) / 2.0;
       lowerl = intg_arg.upper_limit;
     for(int i = 1; i <= intg_arg.n_intervals ;i++)
     { 
	   upperl = intg_arg.upper_limit - interval * i;
	   cossin1 = cos_sin(n * M_PI * lowerl / L);
	   cossin2 = cos_sin(n * M_PI * ((lowerl + upperl) / 2 )/ L);
	   cossin3 = cos_sin(n * M_PI * upperl / L);

	   integral += (interval / 6) * (intg_arg.function_to_be_integrated(lowerl) * cossin1 + 4 * (intg_arg.function_to_be_integrated((lowerl + upperl) / 2)) * cossin2 + intg_arg.function_to_be_integrated(upperl) * cossin3);
	   lowerl = upperl;
     }
   }
   

   return integral;
}

void fourier_coefficients(Fourier fourier_arg) {
   for (int i = 0; i < fourier_arg.n_terms; i++) {
      double L = 0.0;
      fourier_arg.a_i[i] = 0.0;
      fourier_arg.b_i[i] = 0.0;
	  
	  L = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;
	  if (L < 0)
	  {
	    L = (fourier_arg.intg.lower_limit - fourier_arg.intg.upper_limit) / 2;
	  }
      if( i < 1)
	  { 
	    fourier_arg.a_i[i] = (1.0 / L) * simpson_numerical_integration(fourier_arg.intg);
      }
	  else
	  {
	    fourier_arg.a_i[i] = (1.0 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg,i, cos);  
        fourier_arg.b_i[i] = (1.0 / L) * simpson_numerical_integration_for_fourier(fourier_arg.intg,i, sin); 
	  }

   }

}
