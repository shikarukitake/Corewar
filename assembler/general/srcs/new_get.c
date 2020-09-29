/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdagger <sdagger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:29:37 by sdagger           #+#    #+#             */
/*   Updated: 2020/09/29 16:32:49 by sdagger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label			*new_label(char *name, int point)
{
	t_label	*label;

	label = malloc(sizeof(t_label));
	if (label == NULL)
		error_f("new_label malloc", 0);
	label->name = ft_strdup(name);
	if (label->name == NULL)
		error_f("new_label malloc", 0);
	label->point = point;
	return (label);
}

t_ref_label		*new_ref(char *name, unsigned start_end[2],
				unsigned comm_start, t_ctype type)
{
	t_ref_label		*ref;

	ref = malloc(sizeof(t_ref_label));
	if (ref == NULL)
		error_f("new_ref malloc", 0);
	ref->name = ft_strdup(name);
	if (ref->name == NULL)
		error_f("new_ref malloc", 0);
	ref->comm_start = comm_start;
	ref->type = type;
	ref->start = start_end[0];
	ref->end = start_end[1];
	return (ref);
}
