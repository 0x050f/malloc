/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:19:23 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 10:03:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <stddef.h>
# include <pthread.h>
# include <sys/mman.h>
# include <sys/resource.h>

# include <errno.h>
# include <string.h>

typedef unsigned int	t_bool;

# define NB_ALLOC		100
# define TINY_ALLOC		256
# define SMALL_ALLOC	4096

typedef struct			s_block
{
	size_t				size;
	void				*next;
}						t_block;

typedef struct			s_zone
{
	size_t				size;
	void				*blocks;
	void				*next;
}						t_zone;

t_zone					*g_zones;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);

/*
** utils.c
*/

size_t					ft_strlen(const char *s);
void					ft_putnbr(unsigned long n);
void					ft_puthexa(unsigned long n);

/*
** zone.c
*/

size_t					get_alloc_size(size_t block_size);
size_t					get_zone_size(size_t block_size);
t_zone					*create_zone(size_t size);
size_t					get_size_taken_zone(t_zone *zone);
t_zone					*find_zone(void *block);

/*
** block.c
*/

void					*add_block_to_zone(t_zone *zone, size_t size);

#endif
