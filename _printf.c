#include "main.h"

/**
 * handle_specifier - handles a format specifier
 * @specifier: the format specifier character
 * @args: va_list of arguments
 *
 * Return: number of characters printed, or -1 on error
 */
static int handle_specifier(char specifier, va_list args)
{
	int count = 0;

	switch (specifier)
	{
		case 'c':
			count = print_char(args);
			break;
		case 's':
			count = print_string(args);
			break;
		case '%':
			count = print_percent();
			break;
		case 'd':
		case 'i':
			count = print_int(args);
			break;
		default:
			write(1, "%", 1);
			write(1, &specifier, 1);
			count = 2;
			break;
	}
	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: character string containing zero or more directives
 *
 * Return: the number of characters printed (excluding null byte),
 *         or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
	int i = 0, count = 0;
	va_list args;

	if (format == NULL)
		return (-1);

	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
			{
				va_end(args);
				return (-1);
			}
			count += handle_specifier(format[i + 1], args);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
