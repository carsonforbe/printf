#include "main.h"

/**
 * handle_char - handles %c specifier
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_char(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	char c = (char)va_arg(ap, int);
	int count = 0;

	if (!sp->flag_minus && sp->width > 1)
		count += pad_buf(b, sp->width - 1, ' ');
	buf_add(b, c);
	count++;
	if (sp->flag_minus && sp->width > 1)
		count += pad_buf(b, sp->width - 1, ' ');
	return (count);
}

/**
 * handle_str - handles %s specifier
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_str(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	char *str = va_arg(ap, char *);

	if (str == NULL)
	{
		if (sp->prec >= 0 && sp->prec < 6)
			return (fmt_str_out(b, sp, "", 0));
		return (fmt_str_out(b, sp, "(null)", 6));
	}
	return (fmt_str_out(b, sp, str, _strlen(str)));
}

/**
 * handle_percent - handles %% specifier
 * @b: buffer
 * @sp: format specifier
 *
 * Return: number of chars written
 */
int handle_percent(buf_t *b, fmt_spec_t *sp)
{
	(void)sp;
	buf_add(b, '%');
	return (1);
}

/**
 * handle_custom_S - handles %S (non-printable as \xNN)
 * @b: buffer
 * @sp: format specifier
 * @ap: va_list
 *
 * Return: number of chars written
 */
int handle_custom_S(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	char *str = va_arg(ap, char *);
	int i, count = 0;
	char hex[3];
	char *hx = "0123456789ABCDEF";

	(void)sp;
	if (str == NULL)
		str = "(null)";
	for (i = 0; str[i]; i++)
	{
		if (str[i] > 0 && (str[i] < 32 || str[i] >= 127))
		{
			buf_add(b, '\\');
			buf_add(b, 'x');
			hex[0] = hx[(unsigned char)str[i] / 16];
			hex[1] = hx[(unsigned char)str[i] % 16];
			hex[2] = '\0';
			buf_add_str(b, hex, 2);
			count += 4;
		}
		else
		{
			buf_add(b, str[i]);
			count++;
		}
	}
	return (count);
}
