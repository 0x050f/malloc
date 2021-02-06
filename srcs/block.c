/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 17:18:03 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/06 17:28:59 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*add_block_to_zone(t_zone *zone, size_t size)
{
	int			block_size;
	int			size_taken;
	t_block		*block;

	block_size = size + sizeof(t_block);
	if (!zone->blocks)
	{
		zone->blocks = ((void *)((unsigned long)zone + sizeof(t_zone)));
		block = zone->blocks;
	}
	else
	{
		size_taken = get_size_taken_zone(zone);
		if (zone->size - size_taken > block_size)
		{
			block = zone->blocks;
			while (block->next)
				block = block->next;
			block->next = (void *)((unsigned long)block + block->size);
			block = block->next;
		}
		else
			return (NULL);
	}
	block->size = block_size;
	block->next = NULL;
	return ((void *)((unsigned long)block + sizeof(t_block)));
}
