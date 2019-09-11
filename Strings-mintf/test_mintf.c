#include <stdio.h>
#include <stdlib.h>
#include "mintf.h"
#include <limits.h>


int main(int argc, char* argv[])
{ 
  mintf("%d",12345);
  fputc('\n', stdout);

  mintf("%d",-12345);
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

  mintf("%s %d","ranko",520 );
  fputc('\n', stdout);

  mintf("wolaopo shi ranko erqie %d",520);
  fputc('\n', stdout);

  mintf("ranko laopo ai wo 100%%");
  fputc('\n', stdout);

  mintf("nihao 100%");
  fputc('\n', stdout);

  mintf("%c", 48);
  fputc('\n', stdout);
 
  mintf("%b", -234567);
  fputc('\n', stdout);

  mintf("%x", -76543);
  fputc('\n', stdout);

  return EXIT_SUCCESS;
}
