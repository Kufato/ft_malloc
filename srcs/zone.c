/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:39:56 by kufato            #+#    #+#             */
/*   Updated: 2024/08/01 16:33:08 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Free the zone with munmap().
 * 
 * @param zone : the zone to free
 */
void    free_zone(t_zone *zone)
{
    t_zone	*current = g_zones;

	while (current && current->next)
	{
		if (current == zone)
		{
			munmap(current, ZONE_SIZE);
			return ;
		}
		current = current->next;
	}
}

/**
 * @brief Check if the zone is empty, if the size equal the ZONE_SIZE, the zone is empty
 * 
 * @param zone : the zone to search
 * @return true : the zone is empty
 * @return false : the zone is not empty
 */
bool    check_empty_zone(t_zone *zone)
{
    if (zone->size = ZONE_SIZE)
        return (true);
    return (false);
}

/**
 * @brief Find the zone from which the block originates 
 * 
 * @param block : the block to find
 * @return t_zone* : the zone which the block originates or NULL
 */
t_zone	*search_zone_from_block(void *block)
{
	t_zone	*zone;

	if (!g_zones)
		return (NULL);
	zone = g_zones;
	while (zone && zone->next)
	{
		while (zone->blocks && zone->blocks->next)
		{
			if ((void *)zone->blocks == block)
				return (zone);
			zone->blocks = zone->blocks->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

/**
 * @brief Create, initialize and add to the chained list a new zone
 * 
 * @param block_size : the size of the block to be allocated
 * @param zone_size : the size of the zone to 
 * @param current : a pointer to the first node of the chained list zones
 * @return t_zone* : the new zone
 */
t_zone  *create_zone(size_t block_size, size_t zone_size)
{
    t_zone  *new_zone;
    t_zone  *current = g_zones;
    
    new_zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new_zone == MAP_FAILED)
        return NULL;
    new_zone->next = NULL;
    new_zone->size = zone_size;
    if (block_size)
    {
        new_zone->blocks->next = NULL;
        new_zone->blocks->free = true;
        new_zone->blocks->size = block_size;
    }
    else
        new_zone->blocks = NULL;
    while (current && current->next)
        current = current->next;
    current->next = new_zone;
    return (current->next);
}