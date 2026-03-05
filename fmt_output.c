#include "main.h"

/**
 * pad_buf - adds n copies of character c to buffer
 * @b: buffer
 * @n: number of characters
 * @c: character to pad with
 *
 * Return: number of characters added
 */
int pad_buf(buf_t *b, int n, char c)
{
	int i;

	for (i = 0; i < n; i++)
		buf_add(b, c);
	return (n > 0 ? n : 0);
}

/**
 * fmt_str_out - outputs a string with width and precision applied
 * @b: buffer
 * @sp: format specifier
 * @s: string to output
 * @slen: length of the string
 *
 * Return: total chars written
 */
int fmt_str_out(buf_t *b, fmt_spec_t *sp, const char *s, int slen)
{
	int out_len, total = 0;

	out_len = slen;
	if (sp->prec >= 0 && sp->prec < out_len)
		out_len = sp->prec;
	if (!sp->flag_minus && sp->width > out_len)
		total += pad_buf(b, sp->width - out_len, ' ');
	total += buf_add_str(b, s, out_len);
	if (sp->flag_minus && sp->width > out_len)
		total += pad_buf(b, sp->width - out_len, ' ');
	return (total);
}

/**
 * write_num_body - writes prefix, zero-padding, and body digits
 * @b: buffer
 * @body: digit string
 * @pfx: prefix string (like "-", "0x", etc.)
 * @info: array: [0]=pfx_len [1]=body_len [2]=zeros [3]=total
 *
 * Return: chars written for prefix + zeros + body
 */
static int write_num_body(buf_t *b, char *body, char *pfx, int *info)
{
	int written = 0;

	written += buf_add_str(b, pfx, info[0]);
	written += pad_buf(b, info[2], '0');
	written += buf_add_str(b, body, info[1]);
	return (written);
}

/**
 * fmt_num - outputs a number with full formatting
 * @b: buffer
 * @sp: format specifier
 * @body: the digit string (no sign/prefix)
 * @pfx: prefix string ("-", "+", " ", "0x", "0X", "0", "")
 *
 * Return: total chars written
 */
int fmt_num(buf_t *b, fmt_spec_t *sp, char *body, char *pfx)
{
	int body_len, pfx_len, zeros = 0, total_len, count = 0;
	int info[4];
	char pad_c;

	body_len = _strlen(body);
	pfx_len = _strlen(pfx);
	if (sp->prec == 0 && body_len == 1 && body[0] == '0')
		body_len = 0;
	if (sp->prec > body_len)
		zeros = sp->prec - body_len;
	total_len = pfx_len + zeros + body_len;
	info[0] = pfx_len;
	info[1] = body_len;
	info[2] = zeros;
	info[3] = total_len;
	if (sp->flag_zero && sp->prec < 0 && sp->width > total_len)
	{
		zeros += sp->width - total_len;
		info[2] = zeros;
		total_len = sp->width;
		info[3] = total_len;
	}
	pad_c = ' ';
	if (!sp->flag_minus && sp->width > total_len)
		count += pad_buf(b, sp->width - total_len, pad_c);
	count += write_num_body(b, body, pfx, info);
	if (sp->flag_minus && sp->width > total_len)
		count += pad_buf(b, sp->width - total_len, ' ');
	return (count);
}
