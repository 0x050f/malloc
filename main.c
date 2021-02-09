/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 00:29:09 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/09 09:18:46 by lmartin          ###   ########.fr       */
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
	char	*tiny[10];
	/*
	char	*medium[10];
	char	*big[10];
	*/
	
	i = -1;
	while (++i < 10)
		tiny[i] = malloc(200);
	show_alloc_mem();
	i = -1;
	while (++i < 5)
		free(tiny[i]);
	show_alloc_mem();
	/*
	i = -1;
	while (++i < 20)
		tiny[i] = malloc(200);
	*/
	/*
	i = -1;
	while (++i < 10)
		medium[i] = malloc(2500);
	i = -1;
	while (++i < 10)
		big[i] = malloc(5000);
	*/
//	show_alloc_mem();
	/*
	i = -1;
	while (++i < 1024)
	{
		write(STDOUT_FILENO, tiny[i], ft_strlen(tiny[i]));
		free(tiny[i]);
	}
	*/
	return (0);
}
