#include "main.h"

/**
 * handle_rev - handles %r custom specifier (reverse string)
 * @b: buffer
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_rev(buf_t *b, va_list ap)
{
	char *str = va_arg(ap, char *);
	int len, i, count = 0;

	if (str == NULL)
		str = "(null)";
	len = _strlen(str);
	for (i = len - 1; i >= 0; i--)
	{
		buf_add(b, str[i]);
		count++;
	}
	return (count);
}

/**
 * handle_rot13 - handles %R custom specifier (rot13)
 * @b: buffer
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_rot13(buf_t *b, va_list ap)
{
	char *str = va_arg(ap, char *);
	int i, count = 0, j;
	char *in = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char *out = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	char c;

	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i]; i++)
	{
		c = str[i];
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				c = out[j];
				break;
			}
		}
		buf_add(b, c);
		count++;
	}
	return (count);
}
