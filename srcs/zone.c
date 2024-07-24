/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:39:56 by kufato            #+#    #+#             */
/*   Updated: 2024/07/23 14:45:20 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Create, initialize and add to the chained list a new zone
 * 
 * @param block_size the size of the block to be allocated
 * @param zone_size the size of the zone to 
 * @param current a pointer to the first node of the chained list zones
 * @return t_zone* the new zone
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