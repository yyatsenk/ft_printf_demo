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
#include <stdlib.h>
#include <locale.h>
#include <stdarg.h>
#include "./ft_printf.h"
#include "libft/libft.h"
#include <limits.h>
#include <wchar.h>
int ft_size_bin(wint_t nb)
{
	int size;
	char *str;
	char *str_free;

	size = 1;
	//str = malloc(sizeof(*str));
	//free(str);
	str = NULL;
	//free(str_free);
	while (nb /= 2)
		++size;
	return (size);
} 

wchar_t	*ft_wstrncpy(wchar_t *dst,wchar_t *src, size_t len)
{
	size_t i;
	size_t counter;
	size_t res;

	counter = 0;
	res = 0;
	i = -1;
	while (counter < len && src[++i])
	{
		counter += ft_wcharlen(src[i]);
		if (counter <= len)
			res++;
	}
	i = -1;
	while (src[++i] != '\0' && i < res)
		dst[i] = src[i];
	dst[i] = L'\0';
	return (dst);
}

wchar_t		*ft_wstrjoin(wchar_t  *s1, wchar_t *s2, int wstrlen)
{
	int		i;
	int		sum;
	int		j;
	wchar_t	*p;

	i = 0;
	j = -1;
	sum = 0;
	if (!s1 || !s2)
		return (0);
	if (!*s1)
		return (s2);
	if (!*s2)
		return (s1);
	sum = ft_wstrlen(s1);
	sum += ft_wstrlen(s2);
	if (!(p = (wchar_t *)malloc(sizeof(wchar_t) * (sum + 1))))
		return (NULL);
	while (s1[++j] != '\0')
		p[j] = s1[j];
	i = -1;
	while (s2[++i] != '\0')
		p[j++] = s2[i];
	p[j] = '\0';
	return (p);
}

int write_wchar(wchar_t value)
{
       // setlocale(LC_ALL, "en_US.UTF-8");
 
        //我是一只猫。
        unsigned int mask0 = 0;
        unsigned int mask1 = 49280;
        unsigned int mask2= 14712960;
        unsigned int mask3= 4034953344;
 
        unsigned int v = value;
        int size = ft_size_bin((long long int)value);
        int res = 0;
       // printf("size %d\n", size);
        unsigned char octet;
 
        if (size <= 7)
        {
                octet = value;
                write(1, &octet, 1);
				return (1);
        }
        else  if (size <= 11)
        {
                unsigned char o2 = (v << 26) >> 26; // Восстановление первых 6 бит 110xxxxx 10(xxxxxx)
                unsigned char o1 = ((v >> 6) << 27) >> 27; // Восстановление последних 5 бит 110(xxxxx) 10xxxxxx
       
                octet = (mask1 >> 8) | o1; // Применение первой битовой маски ко первому байту
                write(1, &octet, 1);
                octet = ((mask1 << 24) >> 24) | o2; // Применение второй битовой маски ко второму байту
                write(1, &octet, 1);
				return (2);
        }
        else  if (size <= 16)
        {
                unsigned char o3 = (v << 26) >> 26; // Восстановление первых 6 бит 1110xxxx 10xxxxxx 10(xxxxxx)
                unsigned char o2 = ((v >> 6) << 26) >> 26; // Восстановление вторых 6 бит 1110xxxx 10(xxxxxx) 10xxxxxx
                unsigned char o1 = ((v >> 12) << 28) >> 28; // Восстановление последних 4 бит 1110(xxxx) 10xxxxxx 10xxxxxx
       
                octet = (mask2 >> 16) | o1; // Применение первой битовой маски ко первому байту
                write(1, &octet, 1);
                octet = ((mask2 << 16) >> 24) | o2; // Применение второй битовой маски ко второму байту
                write(1, &octet, 1);
                octet = ((mask2 << 24) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
                write(1, &octet, 1);
				return (3);
        }
        else
        {
                unsigned char o4 = (v << 26) >> 26; // Восстановление первых 6 11110xxx 10xxxxxx 10xxxxxx 10(xxxxxx)
                unsigned char o3 = ((v >> 6) << 26) >> 26; // Восстановление вторых 6 бит 11110xxx 10xxxxxx 10(xxxxxx) 10xxxxxx
                unsigned char o2 = ((v >> 12) << 26) >> 26;  // Восстановление третьих 6 бит bits 11110xxx 10(xxxxxx) 10xxxxxx 10xxxxxx
                unsigned char o1 = ((v >> 18) << 29) >> 29; // Восстановление последних 3 бита 11110(xxx) 10xxxxxx 10xxxxxx 10xxxxxx
       
                octet = (mask3 >> 24) | o1; // Применение бит первого байта на первый байт маски
                write(1, &octet, 1);
                octet = ((mask3 << 8) >> 24) | o2; // Применение второй битовой маски ко второму байту
                write(1, &octet, 1);
                octet = ((mask3 << 16) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
                write(1, &octet, 1);
                octet = ((mask3 << 24) >> 24) | o4; // Применение последней битовой маски ко последнему байту
                write(1, &octet, 1);
				return (4);
        }
}
static size_t	string_length_2(long int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa_long(long int n)
{
	size_t			str_len;
	long int	    tmp_n;
	char			*str;

	str_len = string_length_2(n);
	tmp_n = n;
	if (n < 0)
	{
		if (n < -9223372036854775807)
		{
			str = ft_strnew(str_len);
			str = ft_strcpy(str,"-9223372036854775808");
			return (str);
		}
		tmp_n = -n;
		str_len++;
	}
	if (!(str = ft_strnew(str_len)))
		return (0);
	str[--str_len] = tmp_n % 10 + '0';
	while (tmp_n /= 10)
		str[--str_len] = tmp_n % 10 + '0';
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}

static size_t	string_length(long long int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa_long_long(long long int n)
{
	size_t			str_len;
	long long int	tmp_n;
	char			*str;

	str_len = string_length(n);
	tmp_n = n;
	if (n < 0)
	{
		if (n < -9223372036854775807)
		{
			str = ft_strnew(str_len);
			str = ft_strcpy(str,"-9223372036854775808");
			return (str);
		}
		tmp_n = -n;
		str_len++;
	}
	if (!(str = ft_strnew(str_len)))
		return (0);
	str[--str_len] = tmp_n % 10 + '0';
	while (tmp_n /= 10)
		str[--str_len] = tmp_n % 10 + '0';
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}

static int proc_finder(char **format)
{
	int count;

	count = 0;
	while(**format != '%' && **format)
	{
		write(1, &**format, 1);
		*format = *format + 1;
		count++;
	}
	return (count);
}

static char *ft_white_swap_num(char *str, int space)
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
        if ( i == 0 || !(white = ft_strnew(i)))
          return  (str);
      	i -= space;
     	white = ft_strncpy(white, str, i);
     	if (*white == '\0')
     		return (str);
        tmp_1 = white;
        j = i;
        while (ft_isalpha(str[j]) || ft_isdigit(str[j]) || ft_isascii(str[j]))
            j++;
        if ( j == 0 || !(res = (char*)malloc(sizeof(char)* (j - i + 1))))
            return  (str);
        res = ft_strncpy(res, &str[i], j - i);
        tmp_2 = res;
        res = ft_strjoin(res, white);
       	free(tmp_1);
       	free(tmp_2);
       	free(str);
    }
    return (res);
}

char  *error_format_cat(char **format)
{
	int counter;
	char *format_line;

	counter = 1;
	while ((*format)[counter] && ((*format)[counter] == '-' || (*format)[counter] == '+' 
	|| (*format)[counter] == ' ' || (*format)[counter] == '#' ||
	 (*format)[counter] == '0' || ft_isdigit((*format)[counter]) 
	 || (*format)[counter] == '.' || (*format)[counter] == 'h' || 
	 (*format)[counter] == 'l' || (*format)[counter] == 'j' ||
	 (*format)[counter] == 'z' || !ft_strncmp("ll", &(*format)[counter], 2) ||
	 !ft_strncmp("hh", &(*format)[counter], 2)))
		counter++;
	if ((*format)[counter])
	{
		format_line = ft_strnew(counter + 1);
		format_line = ft_strncpy(format_line, *format, counter + 1);
		*format += counter + 1;
		return (format_line);
	}
	else
	{
		*format += counter;
		//if (*format)
		//	*format += 1;
		return (NULL);
	}
}

static char *format_cat(char **format)
{
	char *format_line;
	int counter;

	counter = 1;
	while ((*format)[counter] && (*format)[counter] != 's' && (*format)[counter] != 'S' 
	&& (*format)[counter] != 'd' && (*format)[counter]  != 'D' 
	&& (*format)[counter] != 'i' && (*format)[counter]  != 'o' && (*format)[counter] != 'O' &&
	(*format)[counter]  != 'u' && (*format)[counter]  != 'U' && (*format)[counter]  != 'x' && (*format)[counter]  != 'X'
	 && (*format)[counter] != 'p' && (*format)[counter]  != 'c' && (*format)[counter]  != 'C' && (*format)[counter]  != '%'
	 && ((*format)[counter] == '-' || (*format)[counter] == '+' 
	|| (*format)[counter] == ' ' || (*format)[counter] == '#' ||
	 (*format)[counter] == '0' || ft_isdigit((*format)[counter]) 
	 || (*format)[counter] == '.' || (*format)[counter] == 'h' || 
	 (*format)[counter] == 'l' || (*format)[counter] == 'j' ||
	 (*format)[counter] == 'z' || !ft_strncmp("ll", &(*format)[counter], 2) ||
	 !ft_strncmp("hh", &(*format)[counter], 2)))
		counter++;
	if ((*format)[counter])
	{
		format_line = ft_strnew(counter + 1);
		format_line = ft_strncpy(format_line, *format, counter + 1);
		*format += counter + 1;
		return (format_line);
	}
	else if(!(*format)[counter])
	{
		format_line = error_format_cat(format);
		return (format_line);
	}
	else
		*format = *format + 1;
	return (NULL);
}
//char------------------------------------------------------------------------------------------------------------------------
static char *width_char(char *format_line, char *str, char c, typer type)
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
	free(str_new);
	return (str);
}

static char *flag_width_pres_maintain_char(char *format_line, char *str, typer type)
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
		str = ft_white_swap_num(str, 0);
	return (str);
}

static int char_maintain(char *format_line,va_list *ap, typer *type, perech *data)
{
	char c;
	char *str;
	wchar_t c_w;
	wchar_t *str_w;
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
		if (c == 0)
		{
			c = '\0';
			str = ft_strnew(0);
			str[0] = '\0';
			str = flag_width_pres_maintain_char(format_line, str, *type);
			i = ft_strlen(str + 1);
			write(1, str + 1, i + 1);
			free(str);
			return (i + 1);
		}
		else
		{
			str = ft_strnew(1);
			str[0] = c;
			str[1] = '\0';
		}
		str = flag_width_pres_maintain_char(format_line, str, *type);
		write(1, str, ft_strlen(str));
		return (ft_strlen(str));
	}
	else
	{
		c_w = va_arg(*ap, wint_t);
		//write_wchar(c_w);
		return (write_wchar(c_w));
	}
}
//char_end--------------------------------------------------------------------------------------------------------------------
//str-------------------------------------------------------------------------------------------------------------------------
static char *width_str(char *format_line, char *str, char c, typer type)
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
	free(str_new);
	return (str);
}

static char *precision_str(char *format_line,char *str, typer type, int *nil)
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

static char *flag_width_pres_maintain_str(char *format_line, char *str, typer type)
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

static void ft_modify_str(char *format, perech *data, int *nill)
{
	while (*format && *format != 'l' && *format != 'S')
	{
		if (*format == '0')
			*nill = 1;
		format++;
		if (!ft_strncmp(format, "ll", 2))
			return ;
	}
	if (*format != '\0' && (*data = L))
		;
}


//wstr_maintain-------------------------------------------------------------------------------------------------------------------------------------------------
int ft_wstrlen(wchar_t *wstr)
{
        int size;
        int res;
		int i;

		i = -1;
		size = 0;
		res = 0; 
        while (wstr && wstr[++i] != L'\0')
		{
			size = ft_size_bin(wstr[i]);
			if (size <= 7)
            	res += 1;
       		else  if (size <= 11)
           		res += 2;
        	else  if (size <= 16)
        		res += 3;
      	  	else
        		res += 4;
		}
		return (res);
}
int write_wstr(wchar_t *wstr)
{
	int i;
	int counter;
	int len;

	i = -1;
	counter = 0;
	if (!wstr)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*wstr && *wstr != L'\0')
	{
		counter += write_wchar(*wstr);
		wstr += 1;
	}
	return (counter);
}

static wchar_t *width_wstr(char *format_line, wchar_t *str, wchar_t c, int wstrlen)
{
	int rozmir;
	int chlen;
	int i;
	wchar_t *str_new;
	
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
	chlen = rozmir - ft_wstrlen(str);
	if (chlen >= 0)
		str_new = (wchar_t*)malloc(sizeof(wchar_t) * (chlen + 1));
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = L'\0';
	str = ft_wstrjoin(str_new, str,ft_strlen((char*)str));
	free(str_new);
	return (str);
}

static wchar_t *precision_wstr(char *format_line,wchar_t *str, int wstrlen, int *nil)
{
	int rozmir;
	int chlen;
	wchar_t *str_new;
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
	chlen = rozmir - wstrlen;
	if (chlen < 0)
		str_new = (wchar_t*)malloc(sizeof(wchar_t) * (wstrlen + chlen + 1));
	else 
		return (str);
	str_new = ft_wstrncpy(str_new, str, wstrlen + chlen);
	//free(str);
//	str_new[wstrlen + chlen] = L'\0';
	return (str_new);
}

static wchar_t *flag_width_pres_maintain_wstr(char *format_line, wchar_t *str, int wstrlen)
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
	str = precision_wstr(format_line, str, wstrlen, &flag.nil);
	if (flag.nil == 1 && flag.minus != 1)
		str = width_wstr(format_line, str, L'0', wstrlen);
	else
	 	str = width_wstr(format_line, str, L' ', wstrlen);
	if (flag.minus == 1)
		str = ft_white_swap_wstr(str, wstrlen);
	return (str);
}
//wstr_maintain_end-------------------------------------------------------------------------------------------------------------------------------------------------
static int str_maintain(char *format_line,va_list *ap,typer *type,perech *data)
{
	char *str;
	wchar_t *str_w_pres;
	wchar_t *str_w;
	int nill;

	nill = 0;
	ft_modify_str(format_line, data, &nill);
	if (*data == L && (*type = S))
	{
		str_w = va_arg(*ap, wchar_t*);
		str_w_pres = flag_width_pres_maintain_wstr(format_line, str_w, ft_wstrlen(str_w));
		return (write_wstr(str_w_pres));
	}
	else if ((*type = s))
	{
		str = va_arg(*ap, char *);
		if (str == NULL && nill == 1 && (str = ft_strnew(1)))
			str[0] = '0';
		if (str != NULL)
		{
			str = flag_width_pres_maintain_str(format_line, str, *type);
			write(1, str, ft_strlen(str));
			return (ft_strlen(str));
		}
		write(1, "(null)", 6);
		return (6);
	}
	return (-1);
}
//str_end-------------------------------------------------------------------------------------------------------------------------
//ptr------------------------------------------------------------------------------------------------------------------------
static char *width_ptr(char *format_line, char *str, char c, typer type)
{
	int rozmir;
	int chlen;
	int i;
	char *str_new;
	char *str_free;
	
	if (str == NULL)
		return (str);
	i = -1;
	chlen = 0;
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
	if (c == '0' && (chlen = -2))
		str += 2;
	chlen += rozmir - ft_strlen(str);
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else
	{	if (c == '0')
			str -= 2;
		return (str);
	}
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = '\0';
	str = ft_strjoin(str_new, str);
	free(str_new);
	if (c == '0' && (str_free = str))
	{
		str = ft_strjoin("0x", str);
		free(str_free);
	}
	return (str);
}

static char *precision_ptr(char *format_line,char *str, typer type, int *prec)
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
	*prec = 1;
	if (*(format_line + 1) == '0' || !ft_isdigit(*(format_line + 1)))
		return (ft_strdup("0x"));
	rozmir = ft_atoi((format_line + 1));
	str += 2;
	chlen = rozmir - ft_strlen(str); 
	if (chlen > 0)
		str_new = ft_strnew(chlen);
	else
		return (str - 2);
	while (++i < chlen)
		str_new[i] = '0';
	str_new[i] = '\0';
	str_new_2 = ft_strjoin(str_new, str);
	free(str_new);
	str_new_2 = ft_strjoin("0x", str_new_2);
	return (str_new_2);
}

static int ptr_maintain(char *format_line,va_list *ap,typer *type,perech *data)
{
	size_t num_ptr;
	char *str;
	char *str_free;
	int prec;
	int i;

	i = 0;
	prec = 0;
	num_ptr = va_arg(*ap, size_t);
	str = ft_itoa_base_size(num_ptr, 16, 0);
	str_free = str;
	str = ft_strjoin("0x", str);
	free(str_free);
	str = precision_ptr(format_line, str, *type, &prec);
	while (format_line[i] && format_line[i] != '0')
		i++;
	if (format_line[i] && !ft_isdigit(format_line[i -1]) && !(i = 0) && prec != 1)
	{
		while (format_line[i] && format_line[i] != '-')
			i++;
		if (!format_line[i])
			str = width_ptr(format_line, str, '0', *type);
	}
	if (prec == 1 || format_line[i] || !format_line[i])
		str = width_ptr(format_line, str, ' ', *type);
	i = 0;
	while (format_line[i] && format_line[i] != '-')
		i++;
	if (format_line[i])
		str = ft_white_swap_num(str, 0);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}

//ptr_end------------------------------------------------------------------------------------------------------------------------
//NUM-------------------------------------------------------------------------------------------------------------------------
//flag_maintan******************************************************************************************
static char *width_num(char *format_line, char *str, char c, typer type)
{
	int rozmir;
	int chlen;
	int sign;
	int hash;
	int pres;
	int i;
	char *str_new;
	char *str_new_2;
	
	if (str == NULL)
		return (str);
	i = -1;
	hash = 0;
	pres = 0;
	rozmir = 0;
	sign = 0;
	while (format_line[++i])
		if (format_line[i] == '.')
			pres = 1;
	i = -1;
	while (!ft_isdigit(*format_line) && *format_line)
	{
		if (*format_line == '#')
			hash = 1;
		if (*format_line == '.')
			return (str);
		format_line++;
		while (*format_line == '0')
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
	if ((type == x || type == X)&& c == '0' && hash == 1)
	chlen -= 2;
	if (chlen > 0)
		str_new = ft_strnew(chlen - sign);
	else if (*(str -1) == '-')
		return (str - 1);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = '\0';
	if (c == ' ' && sign == 1 && !(sign = 0))
		str--;
	str_new_2 = str;
	str = ft_strjoin(str_new, str);
	free(str_new);
	if (sign == 1)
		str_new_2--;
	if (str_new_2[0] == '-' && c != ' ')
		str = ft_strjoin("-", str);
	free(str_new_2);
	return (str);
}


static char *precision_num(char *format_line,char *str, typer type, int *nil)
{
	int rozmir;
	int chlen;
	int hash;
	int sign;
	char *str_new;
	char *str_new_2;
	char *str_new_3;
	int i;

	i = -1;
	hash = 0;
	sign = 0;
	str_new_3 = NULL;
	while (*format_line != '.' && *format_line)
	{
		if (*format_line == '#')
			hash = 1;
			format_line++;
	}
	if (*format_line == '\0')
		return (str);
	*nil = 0;
	if ((!ft_isdigit(format_line[1]) || format_line[1] == '0' )&& type != d && str[0] == '0')
	{
		str = ft_strnew(0);
		str[0] = '\0';
		return (str);
	}
	rozmir = ft_atoi((format_line + 1));
	if (str[0] == '-' && (sign = 1))
		str++;
	chlen = rozmir - ft_strlen(str); 
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else if (*(str -1) == '-')
		return (str - 1);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = '0';
	str_new[i] = '\0';
	str_new_2 = str;
	str = ft_strjoin(str_new, str);
	free(str_new);
	if (sign)
		str_new_2--;
	if (str_new_2[0] == '-' && (str_new_3 = str))
		str = ft_strjoin("-", str);
	free(str_new_2);
	if (str_new_3)
	free(str_new_3);
	return (str);
}

static char *flag_width_pres_maintain(char *format_line, char *str, typer type)
{
	t_flag flag;
	int i;
	char *str_free;

	i = 0;
	str_free = NULL;
	flag.minus = 0;
	flag.plus = 0;
	flag.space = 0;
	flag.hash = 0;
	flag.nil = 0;
	while (format_line[++i] &&(format_line[i] == '-' || format_line[i] == '+' 
	|| format_line[i] == ' ' || format_line[i] == '#' || format_line[i] == '0' 
	|| ft_isdigit(format_line[i]) || !ft_strncmp("ll", &format_line[i], 2) || format_line[i] == 'l'
	|| format_line[i] == 'h' || format_line[i] == 'j'
	|| format_line[i] == 'z' || ft_isdigit(format_line[i])|| format_line[i] == '.'))
	{
		if (format_line[i] == '-')
			flag.minus = 1;
		if (format_line[i] == '+')
			flag.plus = 1;
		if (format_line[i] == ' ')
			flag.space = 1;
		if (format_line[i] == '#')
			flag.hash = 1;
		if (format_line[i] == '0' && !ft_isdigit(format_line[i - 1]))
			flag.nil = 1;
	}
	if (flag.minus == 1)
		flag.nil = 0;
	if (flag.plus == 1)
		flag.space = 0;
	if (str[0] == '0' && str[1] == '\0' && type != o && type != O)
		type = none;
	str = precision_num(format_line, str, type, &flag.nil);
	//if (str[0] == '\0')
	//	return (str); 
	if (flag.nil == 1)
		str = width_num(format_line, str, '0', type);
	if (flag.hash == 1 && (type == o  || type == O)&& str[0] != '0' && (str_free = str))
		str = ft_strjoin("0", str);
	else if (flag.hash == 1 && type == x && (str_free = str))
		str = ft_strjoin("0x", str);
	else if (flag.hash == 1 && type == X && (str_free = str))
		str = ft_strjoin("0X", str);
	if (str_free)
		free(str_free);
	if (type == u || type == d || type == i || type == none)
	{
		if (flag.plus == 1)
		{
			if (str[0] != '-' && flag.space != 1 && type != u && (str_free = str))
			{
				str = ft_strjoin("+", str);
				free(str_free);
			}
		}
	}
	if (str[0] != '-' && flag.space == 1 && type != u && type != x && type != o && type != O && type != X && (str_free = str))
	{
		str = ft_strjoin(" ", str);
		free(str_free);
	}
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
static int mod_norm_help(char *format, char **str, typer type, intmax_t num)
{
	if (format[0] == 'l' && format[1] && format[1] != 'l')
	{
		if (type == u)
		{	
			num = (unsigned long int)num;
			*str = ft_itoa_long_unsigned(num);
		}
		else if (type == o || type == O)
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
		else
		{
			num = (long int)num;
			*str = ft_itoa_long(num);
		}
		return (1);
	}
	else if (format[0] == 'h' && format[1] && format[1] == 'h')
	{
		if (type == u)
		{	
			num = (unsigned char)num;
			*str = ft_itoa_base(num, 10, 0);
		}
		else if (type == U)
		{	
			num = (unsigned short)num;
			*str = ft_itoa_base_unsig_short(num, 10, 0);
		}
		else if (type == D)
		{
			num = (unsigned short)num;
			*str = ft_itoa_base_unsig_short(num, 10, 0);
		}
		else if (type == o)
		{
			num = (unsigned char)num;
			*str = ft_itoa_base(num, 8, 0);
		}
		else if (type == O)
		{
			num = (unsigned short)num;
			*str = ft_itoa_base_unsig_short(num, 8, 0);
		}
		else if (type == x)
		{
			num = (unsigned char)num;
			*str = ft_itoa_base(num, 16, 0);
		}
		else if (type == X)
		{
			num = (unsigned char)num;
			*str = ft_itoa_base(num, 16, 1);
		}
		else
		{
			num = (signed char)num;
			*str = ft_itoa_long(num);
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
		else if (type == o || type == O)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 8, 0);
		}
		else if (type == x)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 0);
		}
		else if (type == X)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 1);
		}
		else
		{
			num = (long long int)num;
			*str = ft_itoa_long_long(num);
		}
		return (1);
	}
	else if (format[0] == 'j' )
	{
		if (type == u)
		{	
			num = (unsigned long long int)num;
			*str = ft_itoa_long_long_unsigned(num);
		}
		else if (type == o || type == O)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 8, 0);
		}
		else if (type == x)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 0);
		}
		else if (type == X)
		{
			num = (unsigned long long int)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 1);
		}
		else
		{
			num = (long long int)num;
			*str = ft_itoa_long_long(num);
		}
		return (1);
	}
	else if (format[0] == 'z')
	{
		if (type == u)
		{	
			num = (unsigned long long)num;
			*str = ft_itoa_base_unsigned_long_long(num, 10, 0);
		}
		else if (type == U)
		{
			num = (unsigned long long)num;
			*str = ft_itoa_base_unsigned_long_long(num, 10, 0);
		}
		//else if (type == o)
		//{
		//	num = (ssize_t)num;
		//	*str = ft_itoa_base_ssize(num, 8, 0);
		//}
		else if (type == O || type == o)
		{
			num = (unsigned long long)num;
			*str = ft_itoa_base_unsigned_long_long(num, 8, 0);
		}
		else if (type == x)
		{
			num = (unsigned long long)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 0);
		}
		else if (type == X)
		{
			num = (unsigned long long)num;
			*str = ft_itoa_base_unsigned_long_long(num, 16, 1);
		}
		else
		{
			num = (ssize_t)num;
			*str = ft_itoa_base_ssize(num, 10, 0);
		}
		return (1);
	}
	return (0);
}


static char *mod_help(char *format, va_list *ap, perech *data, typer type)
{
	intmax_t num;
	char *str;

	str = NULL;
	num = 0;
   	num = va_arg(*ap,intmax_t);
	while(*format && *format != 'j' && *format != 'z')
		format += 1;
	while (*format != 'h' && *format != 'l' && *format != 'j' && *format != 'z')
		format -= 1;
	if (*format == 'h' || *format == 'l')
		if (*(format - 1) == 'h' || *(format - 1) == 'l')
			format -= 1;
	if (format[0] == 'h' && format[1] && format[1] != 'h' &&(*data = H))
	{
		if (type == u || type == o || type == O || type == x || type == X)
		{
				num = (unsigned short int)num;
				if (type == u)
					str = ft_itoa_base_unsig_short(num, 10, 0);
				else if (type == o || type == O)
					str = ft_itoa_base_unsig_short(num, 8, 0);
				else if (type == x)
					str = ft_itoa_base_unsig_short(num, 16, 0);
				else if (type == X)
					str = ft_itoa_base_unsig_short(num, 16, 1);
		}
		else if (type == U)
		{
			num = (unsigned long int)num;
			str = ft_itoa_long_unsigned(num);
		}
		else if (type == D)
		{
			num = (unsigned short int)num;
			str = ft_itoa_base_unsig_short(num, 10, 0);
		}
		else
		{
			num = (short int)num;
			str = ft_itoa_long(num);
		}
	}
	if (format[0] == 'l' && format[1] && format[1] != 'l')
		*data = L;
	else if (!ft_strncmp(format, "ll", 2))
		*data = LL;
	else if (!ft_strncmp(format, "hh", 2))
		*data = HH;
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

static char *ft_modify(char *format, va_list *ap, perech *data,typer type)
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

static int num_maintain(char *format_line, va_list *ap, typer *type, perech *data)
{
	int i;
	intmax_t num;
	char *str;
	char *str_free;

	num = 0;
	i = 0;
	while (format_line[i])
		i++;
	if ((format_line[i - 1] == 'd' || format_line[i - 1] == 'D' 
	|| format_line[i - 1] == 'i') && (*type = d))
		num = (int)num;
	else
		num = (unsigned int)num;
	if (format_line[i - 1] == 'o')
		*type = o;
	if (format_line[i - 1] == 'O')
		*type = O;
	if (format_line[i - 1] == 'u')
		*type = u;
	if (format_line[i - 1] == 'U')
		*type = U;
	if (format_line[i - 1] == 'D')
		*type = D;
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
		else if (*type == D)
		{
			num  = va_arg(*ap, long long);
			str = ft_itoa_long_long(num);
		}
		else if (*type == O)
		{
			num  = va_arg(*ap,unsigned long long);
			str = ft_itoa_base_unsigned_long_long(num, 8, 0);
		}
		else if (format_line[i - 1] == 'U')
		{
			num  = va_arg(*ap, unsigned long);
			str = ft_itoa_long_unsigned(num);
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
	i = ft_strlen(str);
	write(1, str, i);
	//if (ft_strcmp(str, "-9223372036854775808"))
		free(str);
	return (i);
}
static int char_maintain_percent(char *format_line,va_list *ap, typer *type, perech *data)
{
	char c;
	char *str;
	int i;
	
		str = ft_strnew(1);
		str[0] = '%';
		str[1] = '\0';
		str = flag_width_pres_maintain_char(format_line, str, *type);
		i = ft_strlen(str);
		write(1, str, i);
		free(str);
		return (i);
}
int error_maintain(char *format_line, typer *type)
{
	char c;
	char *str;
	char *str_free;
	int i;

	i = 0;
	while (format_line[i])
		i++;
	c = format_line[i - 1];
	format_line[i - 1] = 'c';
	str = ft_strnew(1);
	str[0] = c;
	str[1] = '\0';
	str_free = str;
	str = flag_width_pres_maintain_char(format_line, str, *type);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}
static int way_definder(char *format_line, va_list *ap, typer *type, perech *data)
{
	int i;
	int retur;

	i = 0;
	retur = 0;
	if (format_line == NULL)
		return (0);
	while (format_line[i])
		i++;
	if (format_line[i - 1] == 'd' || format_line[i - 1] == 'D' 
	|| format_line[i - 1] == 'i' || format_line[i - 1] == 'o' 
	|| format_line[i - 1] == 'O' || format_line[i - 1] == 'u' || format_line[i - 1] == 'U' 
	|| format_line[i - 1] == 'x' || format_line[i - 1] == 'X')
		retur = num_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == 's' || format_line[i - 1] == 'S')
		retur = str_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == 'c' || format_line[i - 1] == 'C')
		retur = char_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == 'p')
		retur = ptr_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == '%' && (retur = 1))
		retur = char_maintain_percent(format_line, ap, type, data);
	else
		retur = error_maintain(format_line, type);
	free(format_line);
	return (retur);
}
//num_end------------------------------------------------------------------------------------------------------------------------------------------

int ft_printf(char *format,...)
{
	perech data;
	typer type;
	int retur;
	va_list ap;

	retur = 0;
	va_start(ap, format);
	while(*format)
	{
		data = no;
		type = none;
		retur += proc_finder(&format);
		if (*format == '\0')
			return (retur);
		retur += way_definder(format_cat(&format), &ap, &type, &data); 
	}
	va_end (ap);
	return (retur);
}

 /*int main(void)
 {
 	wchar_t l = L'米';
 	int i=42;
 	char c;
 	c = 'a';
// //	printf("%d\n", l);
 	setlocale(LC_ALL, "en_US.UTF-8");
 	printf("%d\n", printf("%4.15S\n", L"我是一只猫。"));
 	printf("%d\n", ft_printf("%4.15S\n", L"我是一只猫。"));
}*/