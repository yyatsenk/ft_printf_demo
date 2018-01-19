/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 15:51:15 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/24 15:51:16 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include "./ft_printf.h"

static int mod_norm_help(char *format, char **str, perech *data, int num)
{
	if (format[0] == 'l' && format[1] != 'l' && (*data = L))
	{
		num = (long int)num;
		*str = ft_itoa_long(num);
		return (1);
	}
	else if (!ft_strncmp(format, "ll", 2) && (*data = LL))
	{
		num = (long long int)num;
		*str = ft_itoa_long_long(num);
		return (1);
	}
	else if (format[0] == 'j' && (*data = J))
	{
		num = (uintmax_t)num;
		*str = ft_itoa_long_long(num);
		return (1);
	}
	else if (format[0] == 'z' && (*data = Z))
	{
		num = (size_t)num;
		*str = ft_itoa_long(num);
		return (1);
	}
	return (0);
}

static char *mod_help(char *format, va_list *ap, perech *data)
{
	uintmax_t num;
	char *str;

	str = NULL;
   	num = va_arg(*ap,uintmax_t);
	if (format[0] == 'h' && format[1] && format[1] != 'h' &&(*data = H))
	{
		num = (short int)num;
		str = ft_itoa_long(num);
	}
	else if (!ft_strncmp(format, "hh", 2) && (*data = HH))
		str = va_arg(*ap, char *);
	else if (mod_norm_help(format, &str, data, num))
		;
	else 
		*data = no;
	return (str);			
}

char *modify(char *format, va_list *ap, perech *data)
{
	char *str;

	str = NULL;
	while (*format != 'h' && ft_strncmp(format, "hh", 2) 
	&& *format != 'l' && ft_strncmp(format, "ll", 2)
	&& *format != 'j' && *format != 'z' && *format != 's' && *format != 'S' 
	&& *format != 'd' && *format != 'D' 
	&& *format != 'i' && *format != 'o' && *format != 'O' &&
	*format != 'u' && *format != 'U' && *format != 'x' && *format != 'X' &&
	*format != 'c' && *format != 'C' && *format)
		format++;
	if (*format != '\0' && *format != 's' && *format != 'S' 
	&& *format != 'd' && *format != 'D' 
	&& *format != 'i' && *format != 'o' && *format != 'O' &&
	*format != 'u' && *format != 'U' && *format != 'x' && *format != 'X' &&
	*format != 'c' && *format != 'C')
		str = mod_help(format, ap, data);
	return (str);
}
