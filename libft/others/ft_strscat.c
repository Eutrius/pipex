/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:25:27 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/21 17:51:12 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strscat(char **strs, char *str)
{
	size_t	strs_len;
	char	**res;
	int		i;

	i = 0;
	if (!strs)
		return (NULL);
	strs_len = ft_strslen(strs);
	res = malloc(sizeof(char *) * (strs_len + 2));
	if (!res)
		return (NULL);
	while (strs[i] != NULL)
	{
		res[i] = strs[i];
		i++;
	}
	res[i] = str;
	res[i + 1] = NULL;
	free(strs);
	return (res);
}
