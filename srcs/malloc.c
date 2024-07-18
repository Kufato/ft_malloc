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
 * @param zone_size the size of a zone
 * @param block_size the size of the block to be allocated
 * @return void* the pointer to the allocated block
 */
void    *find_block(size_t block_size, size_t zone_size)
{
    t_zone *zone = g_zones;

    while (zone && zone->next)
	{
        if (zone->size == zone_size)
		{
            t_block *block = zone->blocks;
            while (block && block->next)
			{
                if (block->size >= block_size && block->free)
				{
                    block->free = false;
                    return (void *)(block + 1);
                }
                block = block->next;
            }
        }
        zone = zone->next;
    }

    t_zone  *new_zone = create_zone(block_size, zone_size);
    t_block *new_block = new_zone->blocks;
    return (void *)(new_block);
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
	size_t	align_size;

	if (!size)
		return (NULL);
	align_size = ALIGN_64(size);
	if (!g_zones)
		pre_alloc();
	if (align_size <= TINY_BLOCK_SIZE)
		block = find_block(align_size, TINY_ZONE_SIZE);
	else if (align_size <= SMALL_BLOCK_SIZE)
		block = find_block(align_size, SMALL_ZONE_SIZE);
	else
    {
        return ;
    }
	return (block);
}