/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:54:39 by kufato            #+#    #+#             */
/*   Updated: 2024/07/24 14:32:05 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void  free(void *ptr)
{
    size_t page_size = getpagesize();
    if (munmap(ptr, page_size) == -1)
		perror("munmap");
}