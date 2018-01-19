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
/*char 				*ft_itoa_base(int value, int base, int whatcase);
char 				*typizator(char *format, va_list *ap, char *str, typer *type);
char 				*ft_white_swap(char *str);
char 				*modify(char *format, va_list *ap, perech *data);
char 				*width(char *format, char *str, char c);
char 				*flagerson(char *format, char *str, typer type);
char 				*precision(char *format,char *str, typer type);
void 				char_manege(char *format, va_list *ap);*/
#endif
