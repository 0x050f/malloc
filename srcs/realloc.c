/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:56:50 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 15:47:13 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free_unthread(void *ptr)
{
	t_zone		*zone;

	if (!ptr)
		return ;
	zone = find_zone(ptr);
	if (!zone)
		return ;
	remove_block(zone, ptr);
	if (!zone->blocks)
		remove_zone(zone);
}

void		*malloc_unthread(size_t size)
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

void		*realloc(void *ptr, size_t size)
{
	size_t		block_size;
	t_zone		*zone;
	t_block		*block;
	void		*new;

	block_size = size + sizeof(t_block);
	pthread_mutex_lock(&g_mutex);
	if (!ptr)
		return (malloc_unthread(size));
	zone = find_zone(ptr);
	if (!zone)
		return (NULL);
	block = find_block(zone, ptr);
	if (block->size >= block_size || (block->next && (size_t)(block->next -
(void *)block) >= block_size))
	{
		block->size = block_size;
		return (ptr);
	}
	new = malloc_unthread(size);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, ptr, block->size - sizeof(t_block));
	free_unthread(ptr);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}
