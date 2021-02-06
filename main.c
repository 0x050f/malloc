/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 00:29:09 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/06 17:19:32 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*pt;

	i = 0;
	while (s1[i])
		i++;
	if (!(pt = malloc((i + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (s1[++i])
		pt[i] = s1[i];
	pt[i] = '\0';
	return (pt);
}

int		main(void)
{
	int		i;
	char	*array[1024];
	
	i = -1;
	while (++i < 1024)
		array[i] = ft_strdup("looool\n");
	i = -1;
	while (++i < 1024)
		write(STDOUT_FILENO, array[i], ft_strlen(array[i]));
	return (i);
}
