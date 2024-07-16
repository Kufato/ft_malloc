/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kufato <kufato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:39:56 by kufato            #+#    #+#             */
/*   Updated: 2024/07/02 14:34:27 by kufato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Create, initialize and add to the chained list a new zone object
 * 
 * @param zone chained list of all the zones
 * @param size size of zone to be allocated
 * @param current a pointer to the first node of the chained list zones
 * @return t_zone* the new zone
 */
t_zone *create_zone(t_zone **zone, size_t size)
{
    t_zone *current = *zone;
    
    if (!zone)
        return (NULL);
    t_zone *new_zone = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new_zone == MAP_FAILED)
        return NULL;

    new_zone->next = NULL;
    new_zone->blocks.size = size - ZONE_SIZE;
    new_zone->blocks.free = true;
    new_zone->blocks.next = NULL;

    while (current && current->next)
        current = current->next;
    current->next = new_zone;
    
    return (current->next);
}