/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:19:23 by lmartin           #+#    #+#             */
/*   Updated: 2020/11/08 16:23:20 by lmartin          ###   ########.fr       */
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

# include "libft.h"

/* TO DELETE */
#include <stdio.h>

typedef unsigned int		t_bool;

# define false				0
# define true				1

# define NB_ALLOC			100
# define TINY_ALLOC			256
# define SMALL_ALLOC		4096

typedef struct				s_block
{
	int						size;
	void					*next;
}							t_block;

typedef struct				s_zone
{
	int						size;
	t_block					*blocks;
	void					*next;
}							t_zone;

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);

t_zone		*create_zone(size_t size);

#endif
