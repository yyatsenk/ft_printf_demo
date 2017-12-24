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
#include "ft_printf.h"

static char *mod_help(char *format, va_list *ap, perech *data)
{
	uintmax_t num;
	char *str;

	str = NULL;
    num = 0;
	if (format[0] == 'h' && format[1] && format[1] != 'h' &&(*data = H))
	{
		num = va_arg(*ap,int);
		num = (short int)num;
		str = ft_itoa_long(num);
	}
	else if (!ft_strncmp(format, "hh", 2) && (*data = HH))
		str = va_arg(*ap, char *);
	else if (format[0] == 'l' && format[1] != 'l' && (*data = L))
	{
		num = (long int)num;
		num = va_arg(*ap,long int);
		str = ft_itoa_long(num);
	}
	else if (!ft_strncmp(format, "ll", 2) && (*data = LL))
	{
		num = va_arg(*ap,long long int);
		str = ft_itoa_long_long(num);
	}
	else 
		*data = no;
	return (str);		
}

char *modify(char *format, va_list *ap, perech *data, int *flag)
{
	char *str;

	str = NULL;
	while (*format != 'h' && ft_strncmp(format, "hh", 2) 
	&& *format != 'l' && ft_strncmp(format, "ll", 2)
	&& *format != 'j' && *format != 'z' && *format)
		format++;
	if (*format != '\0')
	{
		str = mod_help(format, ap, data);
		*flag = 1;
	}
	return (str);
}
