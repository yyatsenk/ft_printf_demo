/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 10:38:34 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/10/29 10:38:35 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int	m;
	int n_copy;

	n_copy = n;
	if (n < 0)
	{
		ft_putchar('-');
		if (n_copy == -2147483648)
			n++;
		n = (unsigned int)(-n);
		if (n > 9)
			ft_putnbr(n / 10);
		m = (n % 10);
		if (n_copy == -2147483648)
			m++;
		ft_putchar(m + '0');
	}
	else
		if (n > 9)
		{
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else
			ft_putchar(n + '0');
}
