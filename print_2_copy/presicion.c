/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presicion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:06:08 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/25 17:06:09 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char *precision(char *format,char *str, typer type)
{
	int num_1;
	int chlen;
	char *str_new;
	int i;

	i = -1;
	if(type != s && type != c && type != p && str != NULL)
	{
		if (format[1] == '0')
			format[1] = '1';
		while (*format != '.' && *format)
			format++;
		if (*format == '\0')
			return (str);
		num_1 = ft_atoi((format + 1));
		chlen = num_1 - ft_strlen(str);
		if (chlen < 0)
			return (str);
		str_new = ft_strnew(chlen);
		while (++i < chlen)
			str_new[i] = '0';
		str_new[i] = '\0';
		str = ft_strjoin(str_new, str);
	}
	return (str);
}
