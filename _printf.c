#include "main.h"

/**
 * dispatch_custom - dispatches custom specifiers (b, S, r, R)
 * @b: buffer
 * @sp: parsed specifier
 * @ap: va_list
 *
 * Return: chars written, or -1 if not a custom specifier
 */
static int dispatch_custom(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	if (sp->spec == 'b')
		return (handle_bin(b, ap));
	if (sp->spec == 'S')
		return (handle_custom_S(b, sp, ap));
	if (sp->spec == 'r')
		return (handle_rev(b, ap));
	if (sp->spec == 'R')
		return (handle_rot13(b, ap));
	return (-1);
}

/**
 * dispatch - dispatches the correct handler for a specifier
 * @b: buffer
 * @sp: parsed format specifier
 * @ap: va_list
 *
 * Return: number of chars written, or -2 for unknown
 */
static int dispatch(buf_t *b, fmt_spec_t *sp, va_list ap)
{
	int ret;

	if (sp->spec == 'c')
		return (handle_char(b, sp, ap));
	if (sp->spec == 's')
		return (handle_str(b, sp, ap));
	if (sp->spec == '%')
		return (handle_percent(b, sp));
	if (sp->spec == 'd' || sp->spec == 'i')
		return (handle_int(b, sp, ap));
	if (sp->spec == 'u')
		return (handle_uint(b, sp, ap));
	if (sp->spec == 'o')
		return (handle_oct(b, sp, ap));
	if (sp->spec == 'x')
		return (handle_hex(b, sp, ap, 0));
	if (sp->spec == 'X')
		return (handle_hex(b, sp, ap, 1));
	if (sp->spec == 'p')
		return (handle_ptr(b, sp, ap));
	ret = dispatch_custom(b, sp, ap);
	return (ret);
}

/**
 * process_fmt - processes the format string
 * @b: buffer
 * @format: format string
 * @ap: va_list
 *
 * Return: total chars written, or -1 on error
 */
static int process_fmt(buf_t *b, const char *format, va_list ap)
{
	int i = 0, count = 0, ret;
	fmt_spec_t sp;

	while (format[i])
	{
		if (format[i] != '%')
		{
			buf_add(b, format[i]);
			count++;
			i++;
			continue;
		}
		if (format[i + 1] == '\0')
			return (-1);
		i = parse_spec(format, i + 1, &sp);
		ret = dispatch(b, &sp, ap);
		if (ret == -1)
		{
			buf_add(b, '%');
			buf_add(b, sp.spec);
			count += 2;
		}
		else
			count += ret;
	}
	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string with directives
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list ap;
	buf_t b;
	int count;

	if (format == NULL)
		return (-1);
	buf_init(&b);
	va_start(ap, format);
	count = process_fmt(&b, format, ap);
	va_end(ap);
	buf_flush(&b);
	return (count);
}
