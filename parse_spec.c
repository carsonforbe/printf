#include "main.h"

/**
 * init_spec - initializes a fmt_spec_t struct
 * @sp: pointer to spec
 */
static void init_spec(fmt_spec_t *sp)
{
	sp->flag_plus = 0;
	sp->flag_space = 0;
	sp->flag_hash = 0;
	sp->flag_zero = 0;
	sp->flag_minus = 0;
	sp->width = 0;
	sp->prec = -1;
	sp->len_h = 0;
	sp->len_l = 0;
	sp->spec = 0;
}

/**
 * parse_flags - parses flag characters from format string
 * @fmt: format string
 * @i: current index (after '%')
 * @sp: pointer to spec struct
 *
 * Return: updated index
 */
static int parse_flags(const char *fmt, int i, fmt_spec_t *sp)
{
	while (fmt[i])
	{
		if (fmt[i] == '+')
			sp->flag_plus = 1;
		else if (fmt[i] == ' ')
			sp->flag_space = 1;
		else if (fmt[i] == '#')
			sp->flag_hash = 1;
		else if (fmt[i] == '0')
			sp->flag_zero = 1;
		else if (fmt[i] == '-')
			sp->flag_minus = 1;
		else
			break;
		i++;
	}
	return (i);
}

/**
 * parse_width_prec - parses width and precision
 * @fmt: format string
 * @i: current index
 * @sp: pointer to spec struct
 *
 * Return: updated index
 */
static int parse_width_prec(const char *fmt, int i, fmt_spec_t *sp)
{
	while (fmt[i] >= '0' && fmt[i] <= '9')
	{
		sp->width = sp->width * 10 + (fmt[i] - '0');
		i++;
	}
	if (fmt[i] == '.')
	{
		sp->prec = 0;
		i++;
		while (fmt[i] >= '0' && fmt[i] <= '9')
		{
			sp->prec = sp->prec * 10 + (fmt[i] - '0');
			i++;
		}
	}
	return (i);
}

/**
 * parse_spec - parses a full format specifier after '%'
 * @fmt: the format string
 * @i: index right after '%'
 * @sp: pointer to fmt_spec_t to fill
 *
 * Return: index of the character AFTER the specifier
 */
int parse_spec(const char *fmt, int i, fmt_spec_t *sp)
{
	init_spec(sp);
	i = parse_flags(fmt, i, sp);
	i = parse_width_prec(fmt, i, sp);

	if (fmt[i] == 'h')
	{
		sp->len_h = 1;
		i++;
	}
	else if (fmt[i] == 'l')
	{
		sp->len_l = 1;
		i++;
	}
	sp->spec = fmt[i];
	if (sp->flag_minus)
		sp->flag_zero = 0;
	return (i + 1);
}
