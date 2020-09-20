/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 23:00:13 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/15 12:22:49 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst)
	{
		if (lst->next)
			ft_lstiter(lst->next, f);
		f(lst);
	}
}

void	ft_lstiter_n(t_list *lst, void (*f)(t_list *elem))
{
	if (lst)
	{
		f(lst);
		if (lst->next)
			ft_lstiter_n(lst->next, f);
	}
}

void	ft_lstiter_ext_n(t_list *lst, void *stuff, void (*f)(t_list *, void *))
{
	if (lst)
	{
		f(lst, stuff);
		if (lst->next)
			ft_lstiter_ext(lst->next, stuff, f);
	}
}

void	ft_lstiter_ext(t_list *lst, void *stuff, void (*f)(t_list *, void *))
{
	if (lst)
	{
		if (lst->next)
			ft_lstiter_ext(lst->next, stuff, f);
		f(lst, stuff);
	}
}
