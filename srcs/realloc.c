/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:56:50 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/11 09:54:01 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** same as free() without mutex because we lock it in realloc()
*/

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

/*
** same as malloc() without mutex because we lock it in realloc()
*/

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

/*
** Check if the alloc_size (TINY - SMALL - LARGE) of the new size corresponding
** to the old size, if this is the case, check if the new allocation can fit
** at the same place, otherwise, call malloc, copy memory, and free the old
** block
*/

void		*realloc_unthread(void *ptr, size_t size)
{
	t_zone		*zone;
	t_block		*block;
	void		*new;

	zone = find_zone(ptr);
	if (!zone)
		return (NULL);
	block = find_block(zone, ptr);
	if (get_alloc_size(block->size) == get_alloc_size(size + sizeof(t_block)) &&
(block->size >= size + sizeof(t_block) || (block->next &&
(size_t)(block->next - (void *)block) >= size + sizeof(t_block))))
	{
		block->size = size + sizeof(t_block);
		return (ptr);
	}
	new = malloc_unthread(size);
	if (!new)
		return (NULL);
	if (block->size - sizeof(t_block) <= size)
		new = ft_memcpy(new, ptr, block->size - sizeof(t_block));
	else
		new = ft_memcpy(new, ptr, size);
	free_unthread(ptr);
	return (new);
}

/*
** reallocate a ptr in memory assigning or not a new block in zone and copying
** previous data on need (see realloc_unthread) returning the new ptr
*/

void		*realloc(void *ptr, size_t size)
{
	void		*new;

	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_mutex);
	new = realloc_unthread(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}
