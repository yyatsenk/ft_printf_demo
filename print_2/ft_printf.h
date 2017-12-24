/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:59:30 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/19 18:59:32 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft/libft.h"
#include "ft_printf.h"

/*typedef enum	t	
{
	none,
	s,
	p,
	d,
	i,
	o,
	u,
	x,
	c,
}				typer;

typedef enum		mode
{
	no,
	H,
	HH,
	L,
	LL,
	J,
	Z,
} 					perech;
*/
int ft_printf(char *format, ...);
#endif
