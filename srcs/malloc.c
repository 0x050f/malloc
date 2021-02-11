/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/11 10:54:33 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** initialize g_mutex here to prevent compilation from multiple g_mutex value
** (because we are compiling c files separately).
** And we can't call pthread_mutex_init because we could call
** realloc/free/show_alloc_mem before malloc
*/

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
** allocate size bytes of memory, returning the pointer corresponding to the
** allocated memory block (after t_block struct)
*/

void		*malloc(size_t size)
{
	void				*alloc;
	t_zone				*last;
	t_zone				*ptr;
	size_t				zone_size;

	alloc = NULL;
	pthread_mutex_lock(&g_mutex);
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
	pthread_mutex_unlock(&g_mutex);
	return (alloc);
}
