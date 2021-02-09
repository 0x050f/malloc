/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 14:05:37 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 09:57:23 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		get_alloc_size(size_t block_size)
{
	if (block_size <= TINY_ALLOC)
		return (TINY_ALLOC);
	else if (block_size <= SMALL_ALLOC)
		return (SMALL_ALLOC);
	return (block_size);
}

size_t		get_zone_size(size_t block_size)
{
	size_t	new_size;
	size_t	page_size;
	size_t	alloc_size;

	page_size = getpagesize();
	alloc_size = get_alloc_size(block_size);
	if (block_size <= SMALL_ALLOC)
	{
		new_size = (NB_ALLOC / (page_size / alloc_size) + 1) * page_size;
		if (new_size - NB_ALLOC * alloc_size < (int)sizeof(t_zone))
			new_size += page_size;
	}
	else
	{
		new_size = (alloc_size / page_size + 1) * page_size;
		if (new_size - alloc_size < (int)sizeof(t_zone))
			new_size += page_size;
	}
	return (new_size);
}

t_zone		*create_zone(size_t size)
{
	t_zone		*new_zone;
	size_t		zone_size;

	zone_size = get_zone_size((size_t)(size + sizeof(t_block)));
	new_zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE |
MAP_ANON, -1, 0);
	new_zone->size = zone_size;
	new_zone->blocks = NULL;
	new_zone->next = NULL;
	return (new_zone);
}

size_t		get_size_taken_zone(t_zone *zone)
{
	size_t		size;
	t_block		*tmp;

	size = sizeof(t_zone);
	if (zone->blocks)
	{
		tmp = zone->blocks;
		while (tmp)
		{
			size += tmp->size;
			tmp = tmp->next;
		}
	}
	return (size);
}

t_zone		*find_zone(void *block)
{
	t_zone		*tmp;
	t_block		*ptr;

	tmp = g_zones;
	while (tmp)
	{
		ptr = tmp->blocks;
		while (ptr)
		{
			if (((void *)ptr + sizeof(t_block)) == block)
				return (tmp);
			ptr = ptr->next;
		}
		tmp = tmp->next;
	}
	return (NULL);
}
