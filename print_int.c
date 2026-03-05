#include "main.h"

/**
 * print_int - prints an integer
 * @args: va_list containing the integer to print
 *
 * Return: number of characters printed
 */
int print_int(va_list args)
{
	int n = va_arg(args, int);
	int count = 0;
	unsigned int num;
	char digit;

	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		num = -n;
	}
	else
	{
		num = n;
	}

	if (num / 10)
		count += print_int_helper(num / 10);

	digit = (num % 10) + '0';
	write(1, &digit, 1);
	count++;

	return (count);
}

/**
 * print_int_helper - helper function to print integer recursively
 * @n: unsigned integer to print
 *
 * Return: number of characters printed
 */
int print_int_helper(unsigned int n)
{
	int count = 0;
	char digit;

	if (n / 10)
		count += print_int_helper(n / 10);

	digit = (n % 10) + '0';
	write(1, &digit, 1);
	count++;

	return (count);
}
