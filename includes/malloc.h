/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:19:23 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/07 14:44:46 by lmartin          ###   ########.fr       */
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

# define false			0
# define true			1

# define NB_ALLOC		100
# define TINY_ALLOC		256
# define SMALL_ALLOC	4096

typedef struct			s_block
{
	int					size;
	void				*next;
}						t_block;

typedef struct			s_zone
{
	int					size;
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

/*
** zone.c
*/

int						get_alloc_size(size_t block_size);
int						get_zone_size(size_t block_size);
t_zone					*create_zone(size_t size);
int						get_size_taken_zone(t_zone *zone);
t_zone					*find_zone(void *block);

/*
** block.c
*/

void					*add_block_to_zone(t_zone *zone, size_t size);

#endif
