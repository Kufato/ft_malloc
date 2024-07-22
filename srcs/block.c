/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:20 by axcallet          #+#    #+#             */
/*   Updated: 2024/07/22 18:00:24 by axcallet         ###   ########.fr       */
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
    t_zone	*current = g_zones;

    while (current && current->next)
	{
        if (current->size == zone_size)
		{       
            t_block	*block = current->blocks;
            while (block && block->next)
			{
                if (block->size >= block_size && block->free)
				{
                    block->free = false;
                    return (void *)(block + 1);
                }
                block = block->next;
            }
            t_block *new_block = create_block(current, block_size);
            return (void *)(new_block);
        }
        current = current->next;
    }
    t_zone  *new_zone = create_zone(block_size, zone_size);
    return (void *)(new_zone->blocks);
}

t_block *create_block(t_zone *zone, size_t block_size)
{
	t_block *current = zone->blocks;
	
    if (!zone->blocks)
		
	while (current && current->next)
	{
		if (zone->size >= block_size)
		{
			
		}
		current = current->next;
	}
}