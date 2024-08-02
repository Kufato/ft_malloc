/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:39 by kufato            #+#    #+#             */
/*   Updated: 2024/08/01 15:48:54 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Free the memory space pointed by ptr.
 * 
 * @param ptr : the pointer to the memory space
 */
void  free(void *ptr)
{
	t_zone *zone = search_zone_from_block(ptr);

	if (!zone)
		return ;
	while (zone->blocks && zone->blocks->next)
	{
		if ((void *)zone->blocks == ptr)
		{
			zone->size += zone->blocks->size;
			ft_bzero(ptr - BLOCK_SIZE, BLOCK_SIZE);
		}
		zone->blocks = zone->blocks->next;
	}
	if (!check_empty_zone(zone))
		free_zone(zone);
	return ;
}