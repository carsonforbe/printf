#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: string to measure
 *
 * Return: length of string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

/**
 * rev_str - reverses a string in place
 * @s: string to reverse
 * @len: length of string
 */
static void rev_str(char *s, int len)
{
	int i = 0, j = len - 1;
	char tmp;

	while (i < j)
	{
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
		i++;
		j--;
	}
}

/**
 * unum_to_str - converts unsigned long to string in given base
 * @out: output buffer (must be big enough, 65 chars for binary)
 * @n: unsigned number
 * @base: numeric base (2, 8, 10, 16)
 * @up: if non-zero use uppercase hex digits
 *
 * Return: length of resulting string
 */
int unum_to_str(char *out, unsigned long int n, int base, int up)
{
	int len = 0;
	char *digits = up ? "0123456789ABCDEF" : "0123456789abcdef";

	if (n == 0)
	{
		out[0] = '0';
		out[1] = '\0';
		return (1);
	}
	while (n > 0)
	{
		out[len++] = digits[n % base];
		n /= base;
	}
	out[len] = '\0';
	rev_str(out, len);
	return (len);
}

/**
 * num_to_str - converts signed long to string in given base
 * @out: output buffer
 * @n: signed number
 * @base: numeric base
 * @upper: uppercase flag
 *
 * Return: length of resulting string (without sign)
 */
int num_to_str(char *out, long int n, int base, int upper)
{
	unsigned long int u;

	if (n < 0)
		u = (unsigned long int)(-(n + 1)) + 1;
	else
		u = (unsigned long int)n;
	return (unum_to_str(out, u, base, upper));
}
