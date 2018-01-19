/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:23:50 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/15 17:23:51 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "./ft_printf.h"
#include <wchar.h>

static int proc_finder(char **format)
{
	int count;

	count = 0;
	while(**format != '%' && **format)
	{
		*format = *format + 1; 
		count++;
	}
	return (count);
}

char *ft_white_swap_num(char *str, int space)
{
    char *white;
    char *tmp_1;
    char *tmp_2;
    char *res;
    int i;
    int j;

    i = 0;
    res = NULL;
    if (str != NULL)
    {
        while (str[i] == ' ' && str[i])
          i++;
        if ( i == 0 || !(white = (char*)malloc(sizeof(char)* (i + 1))))
          return  (str);
      	i -= space; 
     	white = ft_strncpy(white, str, i);
     	if (*white == '\0')
     		return (str);
        tmp_1 = white;
        j = i;
        while (ft_isalpha(str[j]) || ft_isdigit(str[j]) || str[j] == '+' || str[j] == '-' || str[j] == ' ')
            j++;
        if ( j == 0 || !(res = (char*)malloc(sizeof(char)* (j - i + 1))))
            return  (str);
        res = ft_strncpy(res, &str[i], j - i);
        tmp_2 = res;
        res = ft_strjoin(res, white);
       	free(tmp_1);
       	free(tmp_2);
    }
    return (res);
}


void type_finder(char **format)
{
	while ( **format != 's' && **format != 'S' 
	&& **format != 'd' && **format != 'D' 
	&& **format != 'i' && **format != 'o' && **format != 'O' &&
	**format != 'u' && **format != 'U' && **format != 'x' && **format != 'X' &&
	**format != 'c' && **format != 'C' && **format != '%'  && **format)
		*format = *format + 1;
}

char *last_part(char **format, char **str, va_list *ap)
{
	if (((*format)[1] && (*format)[1] == '-') || ((*format)[2] && (*format)[2] == '-')
		|| ((*format)[3] && (*format)[3] == '-'))
			*str = ft_white_swap(*str);
		if (*str != NULL)
			ft_putstr(*str);
		else
			char_manege(*format, ap);
		*format = *format + 1;
		type_finder(format);
		*format = *format + 1;
	return (*str);
}
char *width(char *format, char *str, char c, typer type)
{
	int maybe;
	int chlen;
	int num;
	int i;
	char *str_new;
	
	chlen = 0;
	if ((type == x || type == X )&& (*(format + 1) == '0' || *(format + 2) == '0'))
		chlen -= 2;
	if (str == NULL || *(format + 1) == '-')
		return (str);
	num = ft_atoi(str);
	i = -1;
	while ((!ft_isdigit(*format) && *format) || *format == '0')
		format++;
	if(*format == '\0')
		return (str);
	maybe = ft_atoi(format);
//	if(type != s && type != c && type != p)
		//if (num < 0)
		//	maybe--;
		chlen += maybe - ft_strlen(str);
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

char *flagerson(char *format, char *str, typer type)
{
	char *str_2;
	int num;

	str_2 = format;;
	format++;
	while ((*format == '+' || *format == ' ' || *format == '-' 
	|| *format == '0' || *format == '#') && *str && *str != '%')
	{
	if (*format == '0' || *(format + 1) == '0')
			str = width(str_2, str, '0', type);
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
	str = width(format, str, ' ', type);
	return (str); 
}

void char_manege(char *format, va_list *ap)
{
	char c;
	int maybe;
	int sign;
	int i;

	sign = 0;
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
	else
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
char *format_cat(char **format)
{
	char *format_line;
	int counter;

	counter = 1;
	while ((*format)[counter] && (*format)[counter] != 's' && (*format)[counter] != 'S' 
	&& (*format)[counter] != 'd' && (*format)[counter]  != 'D' 
	&& (*format)[counter] != 'i' && (*format)[counter]  != 'o' && (*format)[counter] != 'O' &&
	(*format)[counter]  != 'u' && (*format)[counter]  != 'U' && (*format)[counter]  != 'x' && (*format)[counter]  != 'X'
	 && (*format)[counter] != 'p' && (*format)[counter]  != 'c' && (*format)[counter]  != 'C' && (*format)[counter]  != '%')
		counter++;
	if ((*format)[counter])
	{
		format_line = ft_strnew(counter + 1);
		format_line = ft_strncpy(format_line, *format, counter + 1);
		*format += counter + 1;
		return (format_line);
	}
	//*format += counter;
	return (NULL);
}
//char------------------------------------------------------------------------------------------------------------------------
char *width_char(char *format_line, char *str, char c, typer type)
{
	int rozmir;
	int chlen;
	int i;
	char *str_new;
	
	if (str == NULL)
		return (str);
	i = -1;
	while (!ft_isdigit(*format_line) && *format_line)
	{
		if (*format_line == '.')
			return (str);
		format_line++;
		if (*format_line == '0')
			format_line++;
	}
	if(*format_line == '\0')
		return (str);
	rozmir = ft_atoi(format_line);
	chlen = rozmir - ft_strlen(str);
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

char *flag_width_pres_maintain_char(char *format_line, char *str, typer type)
{
	t_flag flag;
	int i;

	i = -1;
	flag.minus = 0;
	flag.nil = 0;
	while (format_line[++i] && format_line[i] != '-')
		;
	if (format_line[i] != '\0')
		flag.minus = 1;
	i = -1;
	while (format_line[++i] != '.' && format_line[i])
	{
		if (format_line[i] == '0' && !ft_isdigit(format_line[i - 1]))
			flag.nil = 1;
	}
	if (flag.nil == 1 && flag.minus != 1)
		str = width_char(format_line, str, '0', type);
	else
	 	str = width_char(format_line, str, ' ', type);
	if (flag.minus == 1)
		str = ft_white_swap(str);
	return (str);
}

void char_maintain(char *format_line,va_list *ap, typer *type, perech *data)
{
	char c;
	char *str;
	wchar_t c_w;
	int i;

	i = 0;
	while (format_line[i] && ft_strncmp("hh", &format_line[i], 2))
		i++;
	if (format_line[i])
		c = (unsigned char)c;
	i = 0;
	while (format_line[i] && format_line[i]!= 'l' && format_line[i]!= 'C')
		i++;
	if (!format_line[i])
	{
		c = va_arg(*ap, int);
		str = ft_strnew(1);
		str[0] = c;
		str[1] = '\0';
		str = flag_width_pres_maintain_char(format_line, str, *type);
		printf("%s\n", str);
	}
	else
	{
		c_w = va_arg(*ap, wint_t);
		printf("%C\n", c_w);
	}
}
//char_end--------------------------------------------------------------------------------------------------------------------
//str-------------------------------------------------------------------------------------------------------------------------
char *width_str(char *format_line, char *str, char c, typer type)
{
	int rozmir;
	int chlen;
	int i;
	char *str_new;
	
	if (str == NULL)
		return (str);
	i = -1;
	while (!ft_isdigit(*format_line) && *format_line)
	{
		if (*format_line == '.')
			return (str);
		format_line++;
		if (*format_line == '0')
			format_line++;
	}
	if(*format_line == '\0')
		return (str);
	rozmir = ft_atoi(format_line);
	chlen = rozmir - ft_strlen(str);
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

char *precision_str(char *format_line,char *str, typer type, int *nil)
{
	int rozmir;
	int chlen;
	char *str_new;
	int i;

	i = -1;
	while (*format_line != '.' && *format_line)
	{
		if (*format_line == '0' && !ft_isdigit(*(format_line - 1)))
			*nil = 1;
		format_line++;
	}
	if (*format_line == '\0')
		return (str);
	rozmir = ft_atoi((format_line + 1));
	chlen = rozmir - ft_strlen(str);
	if (chlen < 0)
		str_new = ft_strnew(ft_strlen(str) + chlen);
	else 
		return (str);
	str_new = ft_strncpy(str_new, str, ft_strlen(str) + chlen);
	return (str_new);
}

char *flag_width_pres_maintain_str(char *format_line, char *str, typer type)
{
	t_flag flag;
	int i;

	i = -1;
	flag.minus = 0;
	flag.nil = 0;
	while (format_line[++i] && format_line[i] != '-')
		;
	if (format_line[i] != '\0')
		flag.minus = 1;
	str = precision_str(format_line, str, type, &flag.nil);
	if (flag.nil == 1 && flag.minus != 1)
		str = width_str(format_line, str, '0', type);
	else
	 	str = width_str(format_line, str, ' ', type);
	if (flag.minus == 1)
		str = ft_white_swap(str);
	return (str);
}

void ft_modify_str(char *format, va_list *ap, perech *data,typer *type)
{
	while (*format && *format != 'l' && *format != 'S')
	{
		format++;
		if (!ft_strncmp(format, "ll", 2))
			return ;
	}
	if (*format != '\0' && (*data = L))
		;
}

void str_maintain(char *format_line,va_list *ap,typer *type,perech *data)
{
	char *str;
	wchar_t *str_w;

	ft_modify_str(format_line, ap, data, type);
	if (*data == L && (*type = S))
	{
		str_w = va_arg(*ap, wchar_t *);
		printf("%S\n", str_w);
	}
	else if ((*type = s))
	{
		str = va_arg(*ap, char *);
		str = flag_width_pres_maintain_str(format_line, str, *type);
		printf("%s\n", str);
	}
}
//str_end-------------------------------------------------------------------------------------------------------------------------
//ptr------------------------------------------------------------------------------------------------------------------------

void ptr_maintain(char *format_line,va_list *ap,typer *type,perech *data)
{
	unsigned num_ptr;
	char *str;
	int i;

	i = 0;
	num_ptr = va_arg(*ap, unsigned);
	str = ft_itoa_base(num_ptr, 16, 0);
	str = ft_strjoin("0x7ffe", str);
	str = width_str(format_line, str, ' ', *type);
	while (format_line[i] && format_line[i] != '-')
		i++;
	if (format_line[i])
		str = ft_white_swap_num(str, 0);
	printf("%s\n", str);
}

//ptr_end------------------------------------------------------------------------------------------------------------------------
//NUM-------------------------------------------------------------------------------------------------------------------------
//flag_maintan******************************************************************************************
char *width_num(char *format_line, char *str, char c, typer type)
{
	int rozmir;
	int chlen;
	int sign;
	int pres;
	int i;
	char *str_new;
	char *str_new_2;
	
	if (str == NULL)
		return (str);
	i = -1;
	pres = 0;
	rozmir = 0;
	sign = 0;
	while (format_line[++i])
		if (format_line[i] == '.')
			pres = 1;
	i = -1;
	while (!ft_isdigit(*format_line) && *format_line)
	{
		if (*format_line == '.')
			return (str);
		format_line++;
		if (*format_line == '0')
			format_line++;
		if ((*format_line == '+' ||*format_line == ' ') && c == '0' && pres == 0)
			rozmir = -1;
	}
	if(*format_line == '\0')
		return (str);
	if (str[0] == '+')
		rozmir = 0;
	if (str[0] == '-'  && str[1] != '0'  && (sign = 1) && !(rozmir = 0))
		str++;
	rozmir += ft_atoi(format_line);
	chlen = rozmir - ft_strlen(str) - sign;
	if ((type == x || type == X)&& c == '0')
	chlen -= 2;
	if (chlen > 0)
		str_new = ft_strnew(chlen - sign);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = '\0';
	if (c == ' ' && sign == 1 && !(sign = 0))
		str--;
	str_new_2 = ft_strjoin(str_new, str);
	if (sign == 1)
		str--;
	if (str[0] == '-' && c != ' ')
		str_new_2 = ft_strjoin("-", str_new_2);
	return (str_new_2);
}


char *precision_num(char *format_line,char *str, typer type, int *nil)
{
	int rozmir;
	int chlen;
	char *str_new;
	char *str_new_2;
	int i;

	i = -1;
	while (*format_line != '.' && *format_line)
		format_line++;
	if (*format_line == '\0')
		return (str);
	*nil = 0;
	rozmir = ft_atoi((format_line + 1));
	if (str[0] == '-')
		str++;
	chlen = rozmir - ft_strlen(str); 
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = '0';
	str_new[i] = '\0';
	str_new_2 = ft_strjoin(str_new, str);
	str--;
	if (str[0] == '-')
	str = ft_strjoin("-", str_new_2);
	else
		return (str_new_2);
	return (str);
}

char *flag_width_pres_maintain(char *format_line, char *str, typer type)
{
	t_flag flag;
	int i;

	i = 0;
	flag.minus = 0;
	flag.plus = 0;
	flag.space = 0;
	flag.hash = 0;
	flag.nil = 0;
	while (format_line[++i] &&(format_line[i] == '-' || format_line[i] == '+' 
	|| format_line[i] == ' ' || format_line[i] == '#' || format_line[i] == '0'))
	{
		if (format_line[i] == '-')
			flag.minus = 1;
		if (format_line[i] == '+')
			flag.plus = 1;
		if (format_line[i] == ' ')
			flag.space = 1;
		if (format_line[i] == '#')
			flag.hash = 1;
		if (format_line[i] == '0')
			flag.nil = 1;
	}
	if (flag.minus == 1)
		flag.nil = 0;
	if (flag.plus == 1)
		flag.space = 0;
	str = precision_num(format_line, str, type, &flag.nil);
	if (flag.nil == 1)
		str = width_num(format_line, str, '0', type);
	if (flag.hash == 1 && type == o && str[0] != '0')
		str = ft_strjoin("0", str);
	else if (flag.hash == 1 && type == x)
		str = ft_strjoin("0x", str);
	else if (flag.hash == 1 && type == X)
		str = ft_strjoin("0X", str);
	if (type == u || type == d || type == i)
	{
		if (flag.plus == 1)
		{
			if (str[0] != '-' && flag.space != 1 && type != u)
				str = ft_strjoin("+", str);
		}
	}
	if (str[0] != '-' && flag.space == 1 && type != u)
		str = ft_strjoin(" ", str);
	if (str[0] == '-' || type == u)
		flag.space = 0;
	if (flag.nil == 0)
		str = width_num(format_line, str, ' ', type);
	if (flag.minus == 1)
		str = ft_white_swap_num(str, flag.space);
	return (str);
}
//flag_maintan******************************************************************************************
//size and type maintain********************************************************************************
static int mod_norm_help(char *format, char **str, typer type, uintmax_t num)
{
	if (format[0] == 'l' && format[1] && format[1] != 'l')
	{
		if (type == u)
		{	
			num = (unsigned long int)num;
			*str = ft_itoa_long_unsigned(num);
		}
		else if (type == o)
		{
			num = (long int)num;
			*str = ft_itoa_base_long_unsigned(num, 8, 0);
		}
		else if (type == x)
		{
			num = (long int)num;
			*str = ft_itoa_base_long_unsigned(num, 16, 0);
		}
		else if (type == X)
		{
			num = (long int)num;
			*str = ft_itoa_base_long_unsigned(num, 16, 1);
		}
		return (1);
	}
	else if (!ft_strncmp(format, "ll", 2))
	{
		if (type == u)
		{	
			num = (unsigned long long int)num;
			*str = ft_itoa_long_long_unsigned(num);
		}
		else if (type == o)
		{
			num = (long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 8, 0);
		}
		else if (type == x)
		{
			num = (long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 0);
		}
		else if (type == X)
		{
			num = (long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 1);
		}
		return (1);
	}
	else if (format[0] == 'j' )
	{
		num = (uintmax_t)num;
		*str = ft_itoa_long_long_unsigned(num);
		return (1);
	}
	else if (format[0] == 'z')
	{
		num = (size_t)num;
		*str = ft_itoa_long(num);
		return (1);
	}
	return (0);
}


static char *mod_help(char *format, va_list *ap, perech *data, typer type)
{
	uintmax_t num;
	char *str;

	str = NULL;
   	num = va_arg(*ap,uintmax_t);
	if (format[0] == 'h' && format[1] && format[1] != 'h' &&(*data = H))
	{
		if (type == u)
			num = (unsigned short int)num;
		else
			num = (short int)num;
		str = ft_itoa_long(num);
	}
	if (format[0] == 'l' && format[1] && format[1] != 'l')
		*data = L;
	else if (!ft_strncmp(format, "ll", 2))
		*data = LL;
	else if (format[0] == 'j' )
		*data = J;
	else if (format[0] == 'z')
		*data  = Z;
	else 
	{
		*data = no;
		return (str);
	}
	mod_norm_help(format, &str, type, num);
	return (str);			
}

char *ft_modify(char *format, va_list *ap, perech *data,typer type)
{
	char *str;

	str = NULL;
	while (*format != 'h'&& *format != 'l' && ft_strncmp(format, "ll", 2)
	&& *format != 'j' && *format != 'z' && *format)
		format++;
	if (*format != '\0')
		str = mod_help(format, ap, data, type);
	return (str);
}
//size and type maintain********************************************************************************

void num_maintain(char *format_line, va_list *ap, typer *type, perech *data)
{
	int i;
	uintmax_t num;
	char *str;

	num = 0;
	i = 0;
	while (format_line[i])
		i++;
	if ((format_line[i - 1] == 'd' || format_line[i - 1] == 'D' 
	|| format_line[i - 1] == 'i') && (*type = d))
		num = (int)num;
	else
		num = (unsigned int)num;
	if (format_line[i - 1] == 'o' || format_line[i - 1] == 'O')
		*type = o;
	if (format_line[i - 1] == 'u' || format_line[i - 1] == 'U')
		*type = u;
	if (format_line[i - 1] == 'x')
		*type = x;
	if (format_line[i - 1] == 'X')
		*type = X;
	if (!(str = ft_modify(format_line, ap, data, *type)))
	{	
		if (*type == d)
		{
			num  = va_arg(*ap, int);
			str = ft_itoa_long(num);
		}
		else
		{
			num  = va_arg(*ap, unsigned int);
			if (*type == o)
				str = ft_itoa_base(num, 8, 0);
			else if (*type == x)
				str = ft_itoa_base(num, 16, 0);
			else if (*type == X)
				str = ft_itoa_base(num, 16, 1);
			else
				str = ft_itoa_long(num);
		}
	}
	str = flag_width_pres_maintain(format_line, str, *type);
	printf("%s\n", str);
}
int way_definder(char *format_line, va_list *ap, typer *type, perech *data)
{
	int i;

	i = 0;
	if (format_line == NULL)
		return (0);
	while (format_line[i])
		i++;
	if (format_line[i - 1] == 'd' || format_line[i - 1] == 'D' 
	|| format_line[i - 1] == 'i' || format_line[i - 1] == 'o' 
	|| format_line[i - 1] == 'O' || format_line[i - 1] == 'u' || format_line[i - 1] == 'U' 
	|| format_line[i - 1] == 'x' || format_line[i - 1] == 'X')
		num_maintain(format_line, ap, type, data);
	if (format_line[i - 1] == 's' || format_line[i - 1] == 'S')
		str_maintain(format_line, ap, type, data);
	if (format_line[i - 1] == 'c' || format_line[i - 1] == 'C')
		char_maintain(format_line, ap, type, data);
	if (format_line[i - 1] == 'p')
		ptr_maintain(format_line, ap, type, data);
	if (format_line[i - 1] == '%')
		write(1,"%", 1);
	return (0);
}
//num_end------------------------------------------------------------------------------------------------------------------------------------------

int ft_printf(char *format,...)
{
	perech data;
	typer type;
	int retur;
	char *str;
	char *str_copy;
	va_list ap;

	retur = 0;
	va_start(ap, format);
	while(*format)
	{
		str = NULL;
		data = no;
		type = none;
		retur = proc_finder(&format);
		if (*format == '\0')
			return (retur);
		way_definder(format_cat(&format), &ap, &type, &data); 
		/*str_copy = typizator(format, &ap, str, &type);
		if(str_copy != NULL)
			str = str_copy;
		str = modify(format, &ap, &data);
		str = precision(format, str, type);
		str = flagerson(format, str, type);
		str = last_part(&format, &str, &ap);*/
	}
	va_end (ap);
	return (1);
}

int main(void)
{
	char ca='A';
   	wchar_t wca=L'A';
	unsigned i;
	int ll = 1;
	char *str = "Hello %5.7d   ";

	//i = &ll;
	//printf("%X\n", (unsigned char)c);
	//ft_printf("%hhX", c);
	//wchar_t *wmessage = L"Hello, world"
	//long long int d3=1998;
	printf("%-30p\n",&ll);
	ft_printf("%-30p\n",&ll);
    //ft_printf("%p\n\n",&ca);
		//printf("Hello %5.7s\n","world123");
		//ft_printf("Hello %5.7s\n","world123");
		//ft_printf("%10%");
   return (0);
}
