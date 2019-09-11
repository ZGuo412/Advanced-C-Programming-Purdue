#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

void change_order(int n, int radix)
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
		change_order(n, radix);
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
	change_order(n,radix);


	return;
}


void mintf(const char *format, ...)
{
	va_list vari;
	va_start(vari, format);
	int i = 0;
	int m = 0;
	while(format[i] != '\0')
	{
		if(format[i] == '%'){
			if(format[i + 1] =='d')
			{
			    i++;   
				print_integer(va_arg(vari,int),10,"");
			}
			else if(format[i+1] =='$')
			{
			    i++;
				double dvari = va_arg(vari,double);
				if(dvari < 0)
				{
				fputc('-',stdout);
				dvari = dvari * (-1);
				}
				print_integer((int)dvari,10,"$");
                fputc('.',stdout);
				if((int)(100 * (dvari - (int)dvari)) < 10)
				{
				fputc('0', stdout);
				}
				print_integer((int)(100 * (dvari - (int)dvari)),10,"");
				
		    }
			else if(format[i+1] =='x')
			{ 
			   i++;
			   int iivari = va_arg(vari,int); 
			   if(iivari < 0)
			   {
			   fputc('-', stdout);
			   iivari = iivari * (-1);
			   }
			   fputc('0', stdout);
			   fputc('x', stdout);
               print_integer(iivari,16,"");
			}
			else if(format[i+1] =='b')
			{
			   int ivari = va_arg(vari,int);
			   i++;
			   if(ivari < 0)
			   {
			   fputc('-', stdout);
			   ivari = ivari * (-1);
			   }
			   fputc('0', stdout);
			   fputc('b', stdout);
               print_integer(ivari,2,"");
			}
			else if(format[i+1] =='s')
			{
			   i++;
			   char *print_str = va_arg(vari,char *);
			   for(m = 0; print_str[m] !='\0'; m++)
			   {
			   fputc(print_str[m],stdout);
			   }
			}
			else if(format[i+1] =='c')
			{
			   i++;
			   fputc((char)va_arg(vari,int),stdout);
			}
			else if(format[i+1] =='%')
			{
			   i++;
               fputc('%',stdout);
			}
			else if(format[i+1] == '\0')
			{
			  
			   fputc('%',stdout);
			}
	   }		

		else{
			fputc(format[i],stdout);
		}

        i++;
	
	}
    va_end(vari); 



	return;
}

