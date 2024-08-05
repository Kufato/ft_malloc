/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:46 by kufato            #+#    #+#             */
/*   Updated: 2024/08/05 17:54:41 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void    *realloc(void *ptr, size_t size)
{
    if (!ptr && size)
        return (malloc(size));
    if (ptr && size == 0)
    {
        free(ptr);
        return (NULL);
    }
    
}