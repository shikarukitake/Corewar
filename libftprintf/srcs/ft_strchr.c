/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:18:03 by sdagger           #+#    #+#             */
/*   Updated: 2020/08/03 17:54:24 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (c == '\0')
		return ((char*)(s + ft_strlen(s)));
	while (*s)
	{
		if (*s == c)
			return ((char*)(s));
		s++;
	}
	return (NULL);
}