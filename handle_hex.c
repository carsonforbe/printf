#include "main.h"

/**
 * handle_hex - handles %x and %X specifiers
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 * @upper: 1 for uppercase, 0 for lowercase
 *
 * Return: number of chars written
 */
int handle_hex(buf_t *b, fmt_spec_t *sp, va_list ap, int upper)
{
	unsigned long int val;
	char body[66], pfx[3];

	if (sp->len_l)
		val = va_arg(ap, unsigned long int);
	else if (sp->len_h)
		val = (unsigned short)va_arg(ap, unsigned int);
	else
		val = (unsigned long int)va_arg(ap, unsigned int);
	unum_to_str(body, val, 16, upper);
	pfx[0] = '\0';
	if (sp->flag_hash && val != 0)
	{
		pfx[0] = '0';
		pfx[1] = upper ? 'X' : 'x';
		pfx[2] = '\0';
	}
	return (fmt_num(b, sp, body, pfx));
}

/**
 * handle_bin - handles %b custom specifier (binary)
 * @b: buffer
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_bin(buf_t *b, va_list ap)
{
	unsigned int val = va_arg(ap, unsigned int);
	char body[66];
	int len;

	unum_to_str(body, (unsigned long int)val, 2, 0);
	len = _strlen(body);
	return (buf_add_str(b, body, len));
}

/**
 * handle_ptr - handles %p specifier
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_ptr(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	void *ptr = va_arg(ap, void *);
	char body[66];
	unsigned long int addr;

	if (ptr == NULL)
		return (fmt_str_out(b, sp, "(nil)", 5));
	addr = (unsigned long int)ptr;
	unum_to_str(body, addr, 16, 0);
	return (fmt_num(b, sp, body, "0x"));
}
