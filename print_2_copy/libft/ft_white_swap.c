/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_white_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:03:55 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/22 13:03:56 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_white_swap(char *str)
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
     white = ft_strncpy(white, str, i);
        tmp_1 = white;
        j = i;
        while (ft_isalpha(str[j]) || ft_isdigit(str[j]))
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
