/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:46 by kufato            #+#    #+#             */
/*   Updated: 2024/08/07 14:15:26 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block	*is_malloced(void *ptr)
{
	if (!g_zones)
		return (NULL);
	t_zone	*zone = g_zones;
	while (zone && zone->next)
	{
		while (zone->blocks && zone->blocks->next)
		{
			if (ptr == (void *)zone->blocks)
				return (zone->blocks);
			zone->blocks = zone->blocks->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

/**
 * @brief The realloc function change the size of the memory block pointed by ptr
 * 
 * @param ptr : the memory block to change 
 * @param size : the new size for the memory block
 * @return void* : the new pointer to the memory block
 */
void    *realloc(void *ptr, size_t size)
{
    if (!ptr && size)
        return (malloc(size));
    if (ptr && size == 0)
    {
        free(ptr);
        return (NULL);
    }
	t_block	*block = is_malloced(ptr);
    if (!block)
        return (NULL);
	if ()
}