/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:56:14 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/10 11:15:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		remove_zone(t_zone *zone)
{
	t_zone	*prev;
	t_zone	*tmp;

	prev = NULL;
	tmp = g_zones;
	while (tmp && tmp != zone)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!prev)
		g_zones = tmp->next;
	else
		prev->next = tmp->next;
	munmap(zone, zone->size);
}

void		remove_block(t_zone *zone, void *block)
{
	t_block		*prev;
	t_block		*ptr;

	prev = NULL;
	ptr = zone->blocks;
	while (ptr && ((void *)ptr + sizeof(t_block)) != block)
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (!prev)
		zone->blocks = ptr->next;
	else
		prev->next = ptr->next;
}

void		free(void *ptr)
{
	t_zone		*zone;

	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	zone = find_zone(ptr);
	pthread_mutex_unlock(&g_mutex);
	if (!zone)
		return ;
	pthread_mutex_lock(&g_mutex);
	remove_block(zone, ptr);
	if (!zone->blocks)
		remove_zone(zone);
	pthread_mutex_unlock(&g_mutex);
}
