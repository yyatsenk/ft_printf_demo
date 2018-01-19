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

/*static void pointer_manege(va_list *ap)
{
	int i;
	unsigned int *p = va_arg(*ap,unsigned int);
	//intptr_t p = (intptr_t)&pp;
    char *res;
	printf("%ld", p);
}
*/
static char *hex_help(char format, char *str, typer **type, uintmax_t num)
{
	if (format == 'x' || format == 'X')
	{
		if (format == 'x' && (**type = x))
			str = ft_itoa_base(num, 16, 0);
		if (format == 'X' && (**type = X))
			str = ft_itoa_base(num, 16, 1);
	}
	return (str);
}
static char *type_help(char format, va_list *ap, typer *type, char *str_2)
{
	uintmax_t num;
	char *str;

	if (str_2 != NULL) 
	{
		str = str_2;
		num = ft_atoi(str);
	}
	str = NULL;
	if (str_2 == NULL && format != 's' && format != 'S' && format != 'c' && format != 'C')
		num = va_arg(*ap, uintmax_t);
	if (str_2 == NULL && (format == 's' || format == 'S') && (*type = s))
		str = va_arg(*ap, char *);
	if ((format == 'd' || format == 'D' || format == 'i') && (*type = d))
		str = ft_itoa_long(num);
	if ((format == 'o' || format == 'O') && (*type = o))
		str = ft_itoa_base(num, 8, 0);
	if ((format == 'u' || format == 'U') && (*type = u))
		str = ft_itoa_long(num);
	str = hex_help(format, str, &type, num);
	//if (format == 'p' && (*type = p))
	//	pointer_manege(ap);
	return (str);		
}

char *typizator(char *format, va_list *ap, char *str, typer *type)
{
	char *str_2;

	str_2 = NULL;
	format++;
	while (*format != 's' && *format != 'S' 
	&& *format != 'd' && *format != 'D' 
	&& *format != 'i' && *format != 'o' && *format != 'O' &&
	*format != 'u' && *format != 'U' && *format != 'x' && *format != 'X'
	 && *format != 'p' && *format != '%' && *format)
		format++;
	if (*format == '%')
	{
		str_2 = (char *)malloc(sizeof(char) * 2);
		str_2[0] = '%';
		str_2[1] = '\0';
		return (str_2);
	}
	if (*format != '\0')
		str_2 = type_help(*format, ap, type, str);
	return (str_2); 
}
