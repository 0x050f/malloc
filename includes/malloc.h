/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:19:23 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/17 05:03:46 by lmartin          ###   ########.fr       */
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

# define NB_ALLOC			100
# define TINY_ALLOC			256
# define SMALL_ALLOC		4096

t_list			*g_blocks;

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem(void);

#endif
