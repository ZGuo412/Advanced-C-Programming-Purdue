
#include <stdio.h>
#include "hw02.h"
void convert(int n, int radix)
{
   int m;
   m = n % radix;
   n = n / radix;
   if (n == 0)
   {
      fputc(m + '0', stdout);
   }
   else
   {
      convert(n, radix);
	  if(m > 9)
	  { 
	    m = m + 39;
	    fputc(m + '0', stdout);
	  }
	  else
	  {
	  fputc(m + '0', stdout);
	  }
   }
   return;
}
void print_integer(int n,int radix,char* prefix)
{ 
  int i = 0;
  if(n < 0)
  {
    fputc('-',stdout);
  }
  while(prefix[i] != '\0')
  {
    fputc(prefix[i],stdout);
	i++;
  }
    if (n < 0)
	{
	   n = -n;
	}
  convert(n,radix);
  

  return;
}

