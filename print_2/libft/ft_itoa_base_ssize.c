/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:08:28 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/19 18:08:30 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int ft_size(ssize_t nb, int base)
{
	int size = 1;

	while (nb >= (ssize_t)base)
	{
		nb /= base;
		++size;
	}
	return size;
}

char *ft_itoa_base_ssize(ssize_t value, int base, int whatcase)
{
	int sign = 0;
	int i;
	char *res;
	char *hex = "0123456789ABCDEF";

	if (whatcase == 0)
		hex = "0123456789abcdef";
	i = ft_size(value, base);
	if (value < 0 && (sign = 1))
		if (value < -9223372036854775807)
		{
			res = ft_strnew(20);
			res = ft_strcpy(res,"-9223372036854775808");
			return (res);
		}
	if (value == -1)
	{
		res = ft_strnew(2);
		res =  ft_strcpy(res,"-1");
		return (res);
	}
	res = (char*)malloc(sizeof(char) * i + sign + 1);
	res[sign + i] = '\0';
	if (sign)
		res[0] = '-';
	while (i)
	{
		res[sign + i - 1] = hex[value % base];
		value /= base;
		--i;
	}
	return res;
}
