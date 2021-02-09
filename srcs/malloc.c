/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 11:36:01 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size)
{
	void				*alloc;
	t_zone				*last;
	t_zone				*ptr;
	size_t				zone_size;

	alloc = NULL;
	zone_size = get_zone_size(size);
	if (!g_zones)
		g_zones = create_zone(size);
	ptr = g_zones;
	while (!alloc && ptr)
	{
		if (zone_size == ptr->size)
			alloc = add_block_to_zone(ptr, size);
		last = ptr;
		ptr = ptr->next;
	}
	if (!alloc)
	{
		last->next = create_zone(size);
		alloc = add_block_to_zone(last->next, size);
	}
	return (alloc);
}
