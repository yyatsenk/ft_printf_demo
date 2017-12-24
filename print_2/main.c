/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:23:50 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/15 17:23:51 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

static char *proc_finder(char **format)
{
	char *tmp;

	tmp = *format;
	while(*tmp != '%' && *tmp)
	{
		write(1, tmp, 1);
		tmp++;
	}
	return (tmp);
}

char *width(char *format, char *str, typer type, char c)
{
	int maybe;
	int chlen;
	int num;
	int i;
	char *str_new;
	
	num = ft_atoi(str);
	i = -1;
	while (!ft_isdigit(*format) && *format)
		format++;
	maybe = ft_atoi(format);
	if(type != s && type != c && type != p)
		if (num < 0)
			maybe--;
		chlen = maybe - ft_strlen(str);
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = '\0';
	str = ft_strjoin(str_new, str);
	return (str);
}

char *flagerson(char *format, char *str, typer type)
{
	char *str_2;
	int num;

	str_2 = str;
	format++;
	if ((*format == '+' || *format == ' ' ) && (num = ft_atoi(str)))
	{
		if(num > 0 && *format == '+' 
		&& type != o && type != x && type != X)
			str = ft_strjoin("+", str);
		if(num > 0 && *format == ' ' 
		&& type != o && type != x && type != X)
			str = ft_strjoin(" ", str);
	}
	if (*format == '#' && type == o)
		str = ft_strjoin("0", str);
	if (*format == '#' && type == x)
		str = ft_strjoin("0x", str);
	if (*format == '#' && type == X)
		str = ft_strjoin("0X", str);
	return (str); 
}
int ft_printf(char *format,...)
{
	int flag;
	perech data;
	typer type;
	char *str;
	char *str_copy;
	va_list ap;

	flag = 0;
	str = NULL;
	data = no;
	type = none;
	va_start(ap, format);
		format = proc_finder(&format);
		str = modify(format, &ap, &data, &flag);
		str_copy = typizator(format, &ap, flag, &type);
		if(str_copy != NULL)
			str = str_copy;
		str = flagerson(format, str, type);
		if (format[1] == '0')
			str = width(format, str, type, '0');
		else
			str = width(format, str, type, ' ');
		if (format[1] == '-')
			str = ft_white_swap(str);
		ft_putstr(str);
	va_end (ap);
	return (1);
}

int main(void)
{
	int *d1;
	wchar_t *wmessage = L"Привет, сучки";
	short int d2=1234;
	long long int d3=1998;
	//printf ("Hello % hd\n",32767);
	//ft_printf("%6x",d3);
	printf("%ls",wmessage);
   //ft_putnbr(123);
   return (0);
}
