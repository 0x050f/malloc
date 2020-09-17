/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/17 05:04:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		*malloc(size_t size)
{
	void	*addr;
	void	*block;
	t_list	*new;
	int page_size = getpagesize();
	printf("getpagesize %d\n", page_size);
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
	else
	{
		new = mmap(NULL, sizeof(t_list), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	}
	return (addr);
}
