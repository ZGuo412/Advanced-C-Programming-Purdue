#include <stdio.h>
#include <stdlib.h>
#include "hw02.h"
#include <limits.h>

int main(int argc, char* argv[])
{ 
  print_integer(876, 8, "");
  fputc('\n', stdout);

  print_integer(15429760, 12, "imas");
  fputc('\n', stdout);

  print_integer(1312, 16, "ranko");
  fputc('\n', stdout);

  print_integer(-7643212, 6, "wa");
  fputc('\n', stdout);
  
  print_integer(INT_MAX, 10, "Max");
  fputc('\n', stdout);

  print_integer(478138, 12, "poi~");
  fputc('\n', stdout);

  print_integer(76543, 16, "mo~~");
  fputc('\n', stdout);

  print_integer(23333, 10, ""); 
  print_integer(-20202, 10, "");
  fputc('\n', stdout);
  
  return EXIT_SUCCESS;
}

