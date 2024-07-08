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

t_zone	*create_zone(t_zone **zone, size_t zone_size)
{
    t_zone  *new_zone;
    t_zone  *current;

    current = *zone;
    if (!zone)
        return (NULL);
    new_zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new_zone == MAP_FAILED)
        return (NULL);
    new_zone->next = NULL;
    new_zone->size = zone_size
    if (!current)
    {
        *zone = new_zone;
        return (*zone);
    }
    while (current && current->next)
        current = current->next;
    current->next = new_zone;
    return (current->next);
}