/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kufato <kufato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:43 by kufato            #+#    #+#             */
/*   Updated: 2024/07/05 15:27:19 by kufato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Search for the appropriate zone in the chained list of zones.
 * Then search the chained list of blocks in that zone.
 * If a block is free and the right size, send it back, otherwise create a new one.
 * If the zone is full, create a new zone.
 * 
 * @param size size to allocate
 * @param zone_size size of a zone (depend of @param size)
 * @param block_size size of a block (depend of @param size)
 * @param used_zone_size size of zone with all the metadata
 * @return void* the pointer to the allocated block
 */
void *find_block(size_t size, size_t zone_size, size_t used_zone_size)
{
    t_zone *zone = g_zones;

    while (zone)
	{
        if (zone->size == used_zone_size)
		{
            t_block *block = &zone->blocks;
            while (block)
			{
                if (block->size >= size && block->free)
				{
                    block->free = false;
                    return (void *)(block + 1);
                }
                block = block->next;
            }
        }
        zone = zone->next;
    }

    t_zone *new_zone = create_zone(&g_zones, zone_size);
    if (!new_zone)
		return NULL;
    new_zone->next = g_zones;
    g_zones = new_zone;

    t_block *new_block = &new_zone->blocks;
    new_block->size = new_zone->size - ZONE_SIZE;
    new_block->free = false;
    new_block->next = NULL;

    return (void *)(new_block + 1);
}

/**
 * @brief pre-allocate two zones, one TINY and one SMALL, as requested in the subject.
 */
void    pre_alloc()
{
	create_zone(&g_zones, TINY_ZONE_SIZE);
	create_zone(&g_zones, SMALL_ZONE_SIZE);
}

/**
 * @brief return a pointer to the allocate space in the heap depends of the size 
 * 
 * @param size the size to be allocated
 * @return void* the pointer to the allocate space
 */
void    *malloc(size_t size)
{
	void	*block;
	size_t	al_size;

	if (!size)
		return (NULL);
	al_size = ALIGN_64(size);
	if (!g_zones)
		pre_alloc();
	if (al_size <= TINY_BLOCK_SIZE)
		block = find_block(al_size, TINY_ZONE_SIZE, USED_TINY_ZONE_SIZE);
	else if (al_size <= SMALL_BLOCK_SIZE)
		block = find_block(al_size, SMALL_ZONE_SIZE, USED_SMALL_ZONE_SIZE);
	else
    {
        size_t large_zone_size = ALIGN_64(size + sizeof(t_block));
        t_zone *new_zone = create_zone(&g_zones, large_zone_size);
        if (!new_zone)
            return NULL;
        t_block *large_block = &new_zone->blocks;
        large_block->size = size;
        large_block->free = false;
        large_block->next = NULL;
        return (void *)(large_block + 1);
    }
	return (block);
}