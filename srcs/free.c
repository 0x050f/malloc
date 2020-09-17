/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:56:14 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/17 02:58:13 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

void		free(void *ptr)
{
	if (munmap(ptr, 16) < 0)
	{
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	}
	return ;
}
