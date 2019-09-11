#include <stdio.h>
#include <stdlib.h>
#include "mintf.h"
#include <limits.h>


int main(int argc, char* argv[])
{ 
  mintf("%d",12345);
  fputc('\n', stdout);

  mintf("%$", -1234.5678);
  fputc('\n', stdout);
  
  mintf("%$", 1234.5678);
  fputc('\n', stdout);
  
  mintf("%$", 123489000.0678);
  fputc('\n', stdout);
  
  mintf("%$", 10.00);
  fputc('\n', stdout);
  
  mintf("%$", 7.03);
  fputc('\n', stdout);




  return EXIT_SUCCESS;
}
