/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:18:03 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/11 10:12:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** find and return the t_block from the given zone corresponding to the pointer
** alloc that is the returned allocate memory by a malloc
*/

t_block		*find_block(t_zone *zone, void *alloc)
{
	t_block		*ptr;

	ptr = zone->blocks;
	while (ptr && ((void *)ptr + sizeof(t_block)) != alloc)
		ptr = ptr->next;
	return (ptr);
}

/*
** create and add block in memory
*/

void		*add_block(void *addr, size_t block_size, void *next)
{
	t_block		*block;

	block = addr;
	block->size = block_size;
	block->next = next;
	return (block);
}

/*
** insert a block at the beginning/middle or end of the zone depending on how
** many bytes of size we have to allocate and what is the memory left in each
** interval of other blocks
*/

void		*insert_block(t_zone *zone, size_t size)
{
	t_block		*block;

	if (((void *)zone + sizeof(t_zone)) < zone->blocks &&
(size_t)(zone->blocks - ((void *)zone + sizeof(t_zone))) >= size)
	{
		block = add_block((void *)zone + sizeof(t_zone), size, zone->blocks);
		zone->blocks = block;
		return (block);
	}
	block = zone->blocks;
	while (block->next)
	{
		if ((size_t)(block->next - ((void *)block + block->size)) >= size)
		{
			return ((block->next = add_block((void *)block + block->size, size,
block->next)));
		}
		block = block->next;
	}
	if (zone->size - (((void *)block + block->size) - (void *)zone) > size)
	{
		return ((block->next = add_block((void *)block + block->size,
size, NULL)));
	}
	return (NULL);
}

/*
** add a block to a zone, creating the first block after the zone struct in
** memory or calling insert_block is the memory left on the zone is enought.
** returning null if we can't allock memory on this zone
*/

void		*add_block_to_zone(t_zone *zone, size_t size)
{
	size_t		block_size;
	int			size_taken;
	t_block		*block;

	block = NULL;
	block_size = size + sizeof(t_block);
	if (!zone->blocks)
	{
		block = add_block((void *)zone + sizeof(t_zone), block_size, NULL);
		zone->blocks = block;
	}
	else
	{
		size_taken = get_size_taken_zone(zone);
		if (zone->size - size_taken > block_size)
			block = insert_block(zone, block_size);
	}
	if (!block)
		return (NULL);
	return ((void *)block + sizeof(t_block));
}
