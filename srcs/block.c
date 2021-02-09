/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:18:03 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 11:41:32 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*add_block(void *addr, size_t size, void *next)
{
	t_block		*block;

	block = addr;
	block->size = size;
	block->next = next;
	return (block);
}

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
