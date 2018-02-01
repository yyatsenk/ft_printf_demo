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

wchar_t *ft_white_swap_wstr(wchar_t *str, int wstrlen)
{
    wchar_t *white;
    wchar_t *tmp_1;
    wchar_t *tmp_2;
    wchar_t *res;
    int i;
    int j;

    i = 0;
    res = NULL;
    if (str != NULL)
    {
        while (str[i] == ' ' && str[i])
          i++;
        if (i == 0 || !(white = (wchar_t*)malloc(sizeof(wchar_t) * (i + 1))))
          return  (str);
     white = ft_wstrncpy(white, str, i);
        tmp_1 = white;
        j = i;
        if (j == 0 || !(res = (wchar_t*)malloc(sizeof(wchar_t) * (wstrlen + 1))))
            return  (str);
        res = ft_wstrncpy(res, &str[i], wstrlen);
        tmp_2 = res;
        res = ft_wstrjoin(res, white, wstrlen);
        free(tmp_1);
        free(tmp_2);
        free(str);
    }
    return (res);
}
