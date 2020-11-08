/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/11/08 17:31:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size)
{
	static t_zone		*zones;

	zones = create_zone(size);
	add_block_to_zone(zones);
	/*
	addr = NULL;
	if (size < TINY_ALLOC)
	{
		size = (NB_ALLOC / (page_size / TINY_ALLOC)) * page_size;
		printf("TINY %d\n", TINY_ALLOC);
		block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	}
	else if (size < SMALL_ALLOC)
	{
		size = (NB_ALLOC / (page_size / SMALL_ALLOC)) * page_size;
		printf("SMALL %d\n", SMALL_ALLOC);
		block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	}
	else
	{
		printf("LARGE %d and beyond\n", SMALL_ALLOC + 1);
		block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	}
	if (block == MAP_FAILED)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		addr = NULL;
	}
	*/
	return (NULL);
}
