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

void	*search_block(t_zone *zone, size_t size)
{
	t_zone  current = g_zone;
	while (current && !(current->free && current->size >= size ))
	{
		*zone = current;
		current = current->next;
	}
	return (current);
}

void	*create_block(size_t size, size_t zone_size)
{
    void    *new_block;
    t_zone  *new_zone = g_zone;

    new_block = search_block(g_zone);
    if (!new_block)
    {
        new_zone = create_zone(&g_zone, zone_size)
        if (!new_zone)
            return (NULL);
    }
    return (new_block)
}

void    pre_alloc()
{
    create_zone(g_zone, TINY_ZONE_SIZE);
    create_zone(g_zone, SMALL_ZONE_SIZE);
}

void    *malloc(size_t size)
{
    void    *new_block;
    size_t  s = ALIGN_64(size);

    if (!size)
        return (NULL);
    if (!g_zones)
        pre_alloc();
    if (size <= TINY_BLOCK_SIZE)
        new_block = create_block(size, TINY_ZONE_SIZE)
    else if (size <= SMALL_BLOCK_SIZE)
        // allocation SMALL
    else
        // allocation LARGE




    // size_t  page_size = getpagesize();

    // size = ((size + page_size - 1) / page_size) * page_size;

    // void    *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    // if (ptr == MAP_FAILED)
    // {
    //     perror("mmap");
    //     return (NULL);
    // }

    return (new_block);
}