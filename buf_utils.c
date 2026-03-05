#include "main.h"

/**
 * buf_init - initializes a buffer struct
 * @b: pointer to buffer
 */
void buf_init(buf_t *b)
{
	b->len = 0;
}

/**
 * buf_flush - writes buffer contents to stdout and resets
 * @b: pointer to buffer
 *
 * Return: number of bytes written
 */
int buf_flush(buf_t *b)
{
	int written = 0;

	if (b->len > 0)
	{
		written = write(1, b->data, b->len);
		b->len = 0;
	}
	return (written);
}

/**
 * buf_add - adds a single character to the buffer
 * @b: pointer to buffer
 * @c: character to add
 *
 * Return: 1 on success
 */
int buf_add(buf_t *b, char c)
{
	if (b->len >= BUF_SIZE)
		buf_flush(b);
	b->data[b->len] = c;
	b->len++;
	return (1);
}

/**
 * buf_add_str - adds n characters from string to buffer
 * @b: pointer to buffer
 * @s: string to add
 * @n: number of characters to add
 *
 * Return: number of characters added
 */
int buf_add_str(buf_t *b, const char *s, int n)
{
	int i;

	for (i = 0; i < n; i++)
		buf_add(b, s[i]);
	return (n);
}
