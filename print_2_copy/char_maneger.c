/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_maneger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:06:22 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/25 17:06:24 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static void char_manege_help(int maybe, char *format, int i, int sign)
{
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

void char_manege(char *format, va_list *ap)
{
	char c;
	int maybe;
	int sign;
	int i;

	sign = 0;
	maybe = 0;
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
	char_manege_help(maybe, format, i, sign);
}