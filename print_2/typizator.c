/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typizator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 12:25:53 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/20 12:25:54 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdarg.h>
#include "ft_printf.h"

static char *type_help(char format, va_list *ap, typer *type)
{
	int num;
	char *str;

	str = NULL;
	if (format != 's' && format != 'S' && format != 'c' && format != 'C')
		num = va_arg(*ap, int);
	if ((format == 's' || format == 'S') && (*type = s))
		str = va_arg(*ap, char *);
	if ((format == 'd' || format == 'D' || format == 'i') && (*type = d))
		str = ft_itoa_long(num);
	if ((format == 'o' || format == 'O') && (*type = o))
		str = ft_itoa_base(num, 8, 0);
	if ((format == 'u' || format == 'U') && (*type = u))
		str = ft_itoa_long(num);
	if (format == 'x' || format == 'X')
	{
		if (format == 'x' && (*type = x))
			str = ft_itoa_base(num, 16, 0);
		if (format == 'X' && (*type = X))
			str = ft_itoa_base(num, 16, 1);
	}
	if ((format == 'c' || format == 'C' )&& (*type = c))
		str = va_arg(*ap, char *);
	return (str);		
}

char *typizator(char *format, va_list *ap, int flag, typer *type)
{
	char *str;

	str = NULL;
	if (*(format + 1) == '%')
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '%';
		str[1] = '\0';
		return (str);
	}
	while ((flag == 0 && *format != 's' && *format != 'S' 
	&& *format != 'd' && *format != 'D' 
	&& *format != 'i' && *format != 'o' && *format != 'O' &&
	*format != 'u' && *format != 'U' && *format != 'x' && *format != 'X' &&
	*format != 'c' && *format != 'C' )&& *format)
		format++; 
	if (flag == 0 && *format != '\0')
		str = type_help(*format, ap, type);
	return (str); 
}
