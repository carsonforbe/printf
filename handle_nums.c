#include "main.h"

/**
 * get_signed_val - extracts signed value with length modifier
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: signed long value
 */
static long int get_signed_val(fmt_spec_t *sp, va_list ap)
{
	if (sp->len_l)
		return (va_arg(ap, long int));
	if (sp->len_h)
		return ((short int)va_arg(ap, int));
	return ((long int)va_arg(ap, int));
}

/**
 * get_unsigned_val - extracts unsigned value with length modifier
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: unsigned long value
 */
static unsigned long int get_unsigned_val(fmt_spec_t *sp, va_list ap)
{
	if (sp->len_l)
		return (va_arg(ap, unsigned long int));
	if (sp->len_h)
		return ((unsigned short)va_arg(ap, unsigned int));
	return ((unsigned long int)va_arg(ap, unsigned int));
}

/**
 * handle_int - handles %d and %i specifiers
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_int(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	long int val;
	char body[66], pfx[2];

	val = get_signed_val(sp, ap);
	pfx[0] = '\0';
	pfx[1] = '\0';
	if (val < 0)
	{
		pfx[0] = '-';
		num_to_str(body, val, 10, 0);
	}
	else
	{
		if (sp->flag_plus)
			pfx[0] = '+';
		else if (sp->flag_space)
			pfx[0] = ' ';
		unum_to_str(body, (unsigned long int)val, 10, 0);
	}
	return (fmt_num(b, sp, body, pfx));
}

/**
 * handle_uint - handles %u specifier
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_uint(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	unsigned long int val;
	char body[66];

	val = get_unsigned_val(sp, ap);
	unum_to_str(body, val, 10, 0);
	return (fmt_num(b, sp, body, ""));
}

/**
 * handle_oct - handles %o specifier
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_oct(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	unsigned long int val;
	char body[66];
	int blen;

	val = get_unsigned_val(sp, ap);
	blen = unum_to_str(body, val, 8, 0);
	if (sp->flag_hash && val != 0 && body[0] != '0')
	{
		if (sp->prec <= blen)
			return (fmt_num(b, sp, body, "0"));
	}
	return (fmt_num(b, sp, body, ""));
}
