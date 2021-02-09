/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:56:50 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 14:37:54 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	size_t		block_size;
	t_zone		*zone;
	t_block		*block;
	void		*new;

	block_size = size + sizeof(t_block);
	if (!ptr)
		return (malloc(size));
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
	new = malloc(size);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, ptr, block->size - sizeof(t_block));
	free(ptr);
	return (new);
}
