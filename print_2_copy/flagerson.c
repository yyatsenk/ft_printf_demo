/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagerson.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:06:31 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/25 17:06:32 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char *flagerson(char *format, char *str, typer type)
{
	char *str_2;
	int num;

	str_2 = str;
	format++;
	while (*format == '+' || *format == ' ' || *format == '-' 
	|| *format == '0' || *format == '#')
	{
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
	return (str); 
}
