/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:43 by kufato            #+#    #+#             */
/*   Updated: 2024/07/19 16:02:38 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/**
 * @brief pre-allocate two zones, one TINY and one SMALL, as requested in the subject.
 */
void    pre_alloc()
{
	create_zone(TINY_BLOCK_SIZE, TINY_ZONE_SIZE);
	create_zone(SMALL_BLOCK_SIZE, SMALL_ZONE_SIZE);
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
        t_zone  *large_zone = create_zone(align_size, align_size);
        return (large_zone->blocks);
    }
	return (block);
}