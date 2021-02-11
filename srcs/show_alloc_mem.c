/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:01:23 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/11 09:58:31 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** print a block (addresses and size in memory)
** returning the memory allocated (without t_block struct size)
*/

size_t		print_block(t_block *block)
{
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)block + sizeof(t_block));
	write(STDOUT_FILENO, " - ", 3);
	write(STDOUT_FILENO, "0x", 2);
	ft_puthexa((unsigned long)block + block->size);
	write(STDOUT_FILENO, " : ", 3);
	ft_putnbr(block->size - sizeof(t_block));
	write(STDOUT_FILENO, " bytes\n", 7);
	return (block->size - sizeof(t_block));
}

/*
** print a zone (adress and blocks in memory)
** returning the sum in bytes of the memory allocated by each ptr of the zone
*/

size_t		print_zone(t_zone *zone)
{
	size_t		sum;
	t_block		*tmp;

	tmp = zone->blocks;
	if (tmp->size <= TINY_ALLOC)
		write(STDOUT_FILENO, "TINY : 0x", 9);
	else if (tmp->size <= SMALL_ALLOC)
		write(STDOUT_FILENO, "SMALL : 0x", 10);
	else
		write(STDOUT_FILENO, "LARGE : 0x", 10);
	ft_puthexa((unsigned long)zone + sizeof(t_zone));
	write(STDOUT_FILENO, "\n", 1);
	sum = 0;
	while (tmp)
	{
		sum += print_block(tmp);
		tmp = tmp->next;
	}
	return (sum);
}

/*
** Show allocate zones in memory and their allocations, print also a total
** of bytes allocated
*/

void		show_alloc_mem(void)
{
	size_t		total;
	t_zone		*tmp;

	total = 0;
	pthread_mutex_lock(&g_mutex);
	tmp = g_zones;
	while (tmp)
	{
		total += print_zone(tmp);
		tmp = tmp->next;
	}
	write(STDOUT_FILENO, "Total : ", 8);
	ft_putnbr(total);
	write(STDOUT_FILENO, " bytes\n", 7);
	pthread_mutex_unlock(&g_mutex);
}
