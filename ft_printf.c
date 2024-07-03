// Assignment name  : ft_printf
// Expected files   : ft_printf.c
// Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
// --------------------------------------------------------------------------------

// Write a function named `ft_printf` that will mimic the real printf but 
// it will manage only the following conversions: s,d and x.

// Your function must be declared as follows:

// int ft_printf(const char *, ... );

// Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
// To test your program compare your results with the true printf.

// Exemples of the function output:

// call: ft_printf("%s\n", "toto");
// out: toto$

// call: ft_printf("Magic %s is %d", "number", 42);
// out: Magic number is 42%

// call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
// out: Hexadecimal for 42 is 2a$

#include <unistd.h>
#include <stdarg.h>

void	put_str(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
		*len += write(1, str++, 1);
}

void	put_digit(long long int nbr, int base, int *len)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		put_digit((nbr / base), base, len);
	*len += write(1, &hexa[nbr % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int			len;
	va_list		ptr;

	len = 0;
	va_start(ptr, format);
	while (*format)
	{
		if ((*format == '%') && *(format + 1))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(ptr, char *), &len);
			else if (*format == 'd')
				put_digit((long long int)va_arg(ptr, int), 10, &len);
			else if (*format == 'x')
				put_digit((long long int)va_arg(ptr, unsigned int), 16, &len);
		}
		else
			len += write(1, format, 1);
		format++;
	}
	return (va_end(ptr), len);
}


void putstr(char *str, int *len)
{
	if(!str)
		str = "(null)";
	while(*str)
		*len += write(1, str++, 1);
}

void putnbr(long long int nbr, int base, int *len)
{
	char *hexa = "0123456789abcdef";
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		putnbr((nbr / base), base, len);
	*len += write(1, &hexa[nbr % base], 1);
}

int ft_printf(const char *format, ...)
{
	int len = 0;
	va_list ptr;

	va_start(ptr, format);
	while(*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				put_str(va_arg(ptr, char *), len);
			else if (*format == 'd')
				putnbr((long long)va_arg(ptr, int), 10, len);
			else if (*format == 'x')
				putnbr((long long)va_arg(ptr, unsigned int), 16, len);
		}
		else 
			len += write(1, format, 1);
		format++;
	}
	va_end(ptr);
	return(len);
}


int main(void)
{
	int len[] = 5;
	ft_printf("%s\n", put_str("Munia", &len));
}