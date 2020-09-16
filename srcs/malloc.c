/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/16 15:05:34 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size)
{
	void *addr = mmap((void *)0, size, PROT_READ+PROT_WRITE,MAP_SHARED, 1,0);
	return (addr);
}
