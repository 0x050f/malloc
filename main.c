/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 00:29:09 by lmartin           #+#    #+#             */
/*   Updated: 2020/09/17 03:08:28 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	lol(void)
{
	char	*addr;

	addr = malloc(16);
	if (addr)
	{
		addr[0] = 's';
		addr[1] = 's';
		addr[2] = '\0';
		write(1, addr, ft_strlen(addr));
//		free(addr);
	}
}

int		main(void)
{
	int		i;
	
	lol();
	i = 0;
	while (i < 1024)
		i++;
	while (1)
		;
	return (i);
}
