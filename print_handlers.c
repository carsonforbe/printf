#include "main.h"

/**
 * print_char - prints a character
 * @args: va_list containing the character to print
 *
 * Return: number of characters printed
 */
int print_char(va_list args)
{
	char c = va_arg(args, int);

	write(1, &c, 1);
	return (1);
}

/**
 * print_string - prints a string
 * @args: va_list containing the string to print
 *
 * Return: number of characters printed
 */
int print_string(va_list args)
{
	char *str = va_arg(args, char *);
	int i = 0;

	if (str == NULL)
		str = "(null)";

	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}

	return (i);
}

/**
 * print_percent - prints a percent sign
 *
 * Return: number of characters printed
 */
int print_percent(void)
{
	write(1, "%", 1);
	return (1);
}
