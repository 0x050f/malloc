/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:18:31 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/17 00:36:43 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size)
{
	(void) size;
	char str[]= "salut";

	write(1, str, ft_strlen(str));
	return (NULL);
}
