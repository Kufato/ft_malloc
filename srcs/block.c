/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:20 by axcallet          #+#    #+#             */
/*   Updated: 2024/08/01 14:23:18 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief Create a block object.
 * 
 * @param block_size : the size of the requested block
 * @return t_block* 
 */
t_block	*create_block (size_t block_size)
{
    t_block *new_block;

    new_block->next = NULL;
    new_block->size = block_size;
    new_block->free = true;

	return (new_block);
}

/**
 * @brief Find if the block can fit in the zone.
 * If yes create a new block with @param create_block().
 * If no return NULL.
 * 
 * @param zone : the zone of the research
 * @param block_size : the size of the requested block
 * @return t_block* 
 */
t_block *add_block(t_zone *zone, size_t block_size)
{
	t_zone	*curr_zone = zone;
	t_block *curr_block;
	
    if (!curr_zone->blocks)
	{
		t_block *new_block = create_block(block_size);
		curr_zone->blocks = new_block;
		curr_zone->size = curr_zone->size - block_size;
		return (curr_zone->blocks);
    }
	curr_block = curr_zone->blocks;
	if (curr_zone->size >= block_size)
	{
    	while (curr_block && curr_block->next)
		{
            t_block *new_block = create_block(block_size);
			curr_zone->blocks = new_block;
			curr_zone->size = curr_zone->size - block_size;
			return (curr_zone->blocks);
		}
		curr_block = curr_block->next;
	}
	return (NULL);
}

/**
 * @brief Search for the appropriate zone in the chained list of zones.
 * Then search the chained list of blocks in that zone.
 * If a block is free and the right size, send it back, otherwise create a new one.
 * If the zone is full, create a new zone.
 * 
 * @param zone_size : the size of a zone
 * @param block_size : the size of the block to be allocated
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
            t_block *new_block = add_block(current, block_size);
			if (!new_block)
				break;
			return (void *)(new_block);
        }
        current = current->next;
    }
    t_zone  *new_zone = create_zone(block_size, zone_size);
    return (void *)(new_zone->blocks);
}