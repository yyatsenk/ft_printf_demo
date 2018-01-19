/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_of_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 11:40:28 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/11/05 11:40:29 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_num_of_words(char **arr)
{
	int	i;

	i = 0;
	while (*arr)
	{
		i++;
		arr++;
	}
	return (i);
}