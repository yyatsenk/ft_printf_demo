/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:06:14 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/25 17:06:15 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

char *width(char *format, char *str, char c, typer type)
{
	int maybe;
	int chlen;
	int num;
	int i;
	char *str_new;
	
	if (str == NULL)
		return (str);
	num = ft_atoi(str);
	i = -1;
	while (!ft_isdigit(*format) && *format)
		format++;
	if(*format == '\0')
		return (str);
	maybe = ft_atoi(format);
	chlen = maybe - ft_strlen(str);
	if (type == x || type == X)
		chlen -= 2;
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
