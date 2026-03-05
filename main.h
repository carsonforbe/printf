#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

/**
 * struct fmt_spec - parsed format specifier
 * @flag_plus: flag +
 * @flag_space: flag space
 * @flag_hash: flag #
 * @flag_zero: flag 0
 * @flag_minus: flag -
 * @width: field width
 * @prec: precision (-1 if not specified)
 * @len_h: h modifier
 * @len_l: l modifier
 * @spec: conversion specifier character
 */
typedef struct fmt_spec
{
	int flag_plus;
	int flag_space;
	int flag_hash;
	int flag_zero;
	int flag_minus;
	int width;
	int prec;
	int len_h;
	int len_l;
	char spec;
} fmt_spec_t;

/**
 * struct buf - output buffer struct
 * @data: buffer array
 * @len: current length of data in buffer
 */
typedef struct buf
{
	char data[BUF_SIZE];
	int len;
} buf_t;

/* buffer utilities - buf_utils.c */
void buf_init(buf_t *b);
int buf_flush(buf_t *b);
int buf_add(buf_t *b, char c);
int buf_add_str(buf_t *b, const char *s, int n);

/* _printf core - _printf.c */
int _printf(const char *format, ...);

/* format parser - parse_spec.c */
int parse_spec(const char *fmt, int i, fmt_spec_t *sp);

/* number to string - num_utils.c */
int num_to_str(char *out, long int n, int base, int upper);
int unum_to_str(char *out, unsigned long int n, int base, int up);
int _strlen(const char *s);

/* handlers - handle_chars.c */
int handle_char(buf_t *b, fmt_spec_t *sp, va_list ap);
int handle_str(buf_t *b, fmt_spec_t *sp, va_list ap);
int handle_percent(buf_t *b, fmt_spec_t *sp);
int handle_custom_S(buf_t *b, fmt_spec_t *sp, va_list ap);

/* handlers - handle_nums.c */
int handle_int(buf_t *b, fmt_spec_t *sp, va_list ap);
int handle_uint(buf_t *b, fmt_spec_t *sp, va_list ap);
int handle_oct(buf_t *b, fmt_spec_t *sp, va_list ap);

/* handlers - handle_hex.c */
int handle_hex(buf_t *b, fmt_spec_t *sp, va_list ap, int upper);
int handle_bin(buf_t *b, va_list ap);
int handle_ptr(buf_t *b, fmt_spec_t *sp, va_list ap);

/* handlers - handle_rev.c */
int handle_rev(buf_t *b, va_list ap);
int handle_rot13(buf_t *b, va_list ap);

/* format output with width/prec/flags - fmt_output.c */
int fmt_num(buf_t *b, fmt_spec_t *sp, char *body, char *pfx);
int fmt_str_out(buf_t *b, fmt_spec_t *sp, const char *s, int slen);
int pad_buf(buf_t *b, int n, char c);

#endif
