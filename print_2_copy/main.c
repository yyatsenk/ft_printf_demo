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
#include "./ft_printf.h"

static int proc_finder(char **format)
{
	char *tmp;
	int count;

	count = 0;
	//tmp = *format;
	while(**format != '%' && **format)
	{
		write(1, *format, 1);
		*format = *format + 1; 
		count++;
	}
	return (count);
}

void type_finder(char **format)
{
	while ( **format != 's' && **format != 'S' 
	&& **format != 'd' && **format != 'D' 
	&& **format != 'i' && **format != 'o' && **format != 'O' &&
	**format != 'u' && **format != 'U' && **format != 'x' && **format != 'X' &&
	**format != 'c' && **format != 'C' && **format != '%'  && **format)
		*format = *format + 1;
}

char *last_part(char **format, char **str, va_list *ap)
{
	if (((*format)[1] && (*format)[1] == '-') || ((*format)[2] && (*format)[2] == '-')
		|| ((*format)[3] && (*format)[3] == '-'))
			*str = ft_white_swap(*str);
		if (*str != NULL)
			ft_putstr(*str);
		else
			char_manege(*format, ap);
		*format = *format + 1;
		type_finder(format);
		*format = *format + 1;
	return (*str);
}
char *width(char *format, char *str, char c, typer type)
{
	int maybe;
	int chlen;
	int num;
	int i;
	char *str_new;
	
	chlen = 0;
	if ((type == x || type == X )&& (*(format + 1) == '0' || *(format + 2) == '0'))
		chlen -= 2;
	if (str == NULL || *(format + 1) == '-')
		return (str);
	num = ft_atoi(str);
	i = -1;
	while ((!ft_isdigit(*format) && *format) || *format == '0')
		format++;
	if(*format == '\0')
		return (str);
	maybe = ft_atoi(format);
//	if(type != s && type != c && type != p)
		//if (num < 0)
		//	maybe--;
		chlen += maybe - ft_strlen(str);
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

	str_2 = format;;
	format++;
	while ((*format == '+' || *format == ' ' || *format == '-' 
	|| *format == '0' || *format == '#') && *str && *str != '%')
	{
	if (*format == '0' || *(format + 1) == '0')
			str = width(str_2, str, '0', type);
	if ((*format == '+' || *format == ' ' )&& str && (num = ft_atoi(str)))
	{
		if(num > 0 && *format == '+' 
		&& type != o && type != x && type != X)
			str = ft_strjoin("+", str);
		if(num > 0 && *format == ' ' 
		&& type != o && type != x && type != X)
			str = ft_strjoin(" ", str);
	}
	if (*format == '#' && *str  && str[0] != '0' && type == o)
		str = ft_strjoin("0", str);
	if (*format == '#' && *str && type == x)
		str = ft_strjoin("0x", str);
	if (*format == '#' && *str && type == X)
		str = ft_strjoin("0X", str);
	format++;
	}
	str = width(format, str, ' ', type);
	return (str); 
}
char *precision(char *format,char *str, typer type)
{
	int num_1;
	//int num_2;
	int chlen;
	char *str_new;
	int i;

	i = -1;
	if(type != s && type != c && type != p && str != NULL && *str != '%')
	{
	//if (format[1] == '0')
	//	format[1] = '1';
	while (*format != '.' && *format)
		format++;
	if (*format == '\0')
		return (str);
	num_1 = ft_atoi((format + 1));
	//num_2 = ft_atoi(str);
		chlen = num_1 - ft_strlen(str);
		if (chlen >= 0)
			str_new = ft_strnew(chlen);
		else
			return (str);
		while (++i < chlen)
			str_new[i] = '0';
		str_new[i] = '\0';
		//if (num_2 < 0)
		//{
		//	str_new[0] = '-';
		//	str[0] = '0';
		//}
		str = ft_strjoin(str_new, str);
	}
	return (str);

}

void char_manege(char *format, va_list *ap)
{
	char c;
	int maybe;
	int sign;
	int i;

	sign = 0;
	i = -1;
	c = va_arg(*ap, int);
	if (format[1] == '-')
		sign = 1;
	while (!ft_isdigit(*format) && *format != 'c' && *format != 'C' && *format)
		format++;
	if(*format == '\0' || *format == 'c' || *format == 'C')
	{	
		ft_putchar(c);
		return ;
	}
	else
		maybe = ft_atoi(format);
	if ((maybe - 1) > 0)
	{
		if (sign == 0)
		{
			while (++i < maybe - 1)
				ft_putchar(' ');
		ft_putchar(c);
		}
		else
		{
			ft_putchar(c);
			while (++i < maybe - 1)
				ft_putchar(' ');
		}
	}
}
int ft_printf(char *format,...)
{
	perech data;
	typer type;
	int retur;
	char *str;
	char *str_copy;
	va_list ap;

	retur = 0;
	va_start(ap, format);
	while(*format)
	{
		str = NULL;
		data = no;
		type = none;
		retur = proc_finder(&format);
		if (*format == '\0')
			return (retur);
		str = modify(format, &ap, &data);
		str_copy = typizator(format, &ap, str, &type);
		if(str_copy != NULL)
			str = str_copy;
		str = precision(format, str, type);
		str = flagerson(format, str, type);
		str = last_part(&format, &str, &ap);
	}
	va_end (ap);
	return (1);
}

int main(void)
{
	//char *d1 = "Hello";
	//char *dd;
	char c = 255;
	//printf("%X\n", (unsigned char)c);
	//ft_printf("%hhX", c);
	//wchar_t *wmessage = L"Hello, world"
	//long long int d3=1998;
	//printf("%x", 100L);
	ft_printf("%hd\n", 2147483647);
		//printf("Hello %5.7s\n","world123");
		//ft_printf("Hello %5.7s\n","world123");
		//ft_printf("%10%");
   return (0);
}
