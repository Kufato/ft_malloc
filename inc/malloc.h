/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kufato <kufato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:37:41 by kufato            #+#    #+#             */
/*   Updated: 2024/07/05 15:53:10 by kufato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

// ############### Includes ###############

#include <stdio.h> // for the perror() function 

#include <sys/mman.h>
#include "../lib/libft/libft.h"

// ############### Defines ###############

#define ALIGN_64(x)				(((((x) - 1) >> 3) << 3) + 8)

#define PAGE_SIZE				((size_t) getpagesize())
#define	ZONE_SIZE				sizeof(t_zone)
#define BLOCK_SIZE				sizeof(t_block)

#define TINY_BLOCK_SIZE			((size_t) 128 + 16 - BLOCK_SIZE)
#define USED_TINY_ZONE_SIZE		(100 * (TINY_BLOCK_SIZE + BLOCK_SIZE) + ZONE_SIZE)
#define TINY_PADDING_SIZE		(USED_TINY_ZONE_SIZE % PAGE_SIZE)
#define	TINY_ZONE_SIZE			(USED_TINY_ZONE_SIZE + PAGE_SIZE - TINY_PADDING_SIZE)

#define SMALL_BLOCK_SIZE		((size_t) 1024 + 16 - BLOCK_SIZE)
#define USED_SMALL_ZONE_SIZE	(100 * (SMALL_BLOCK_SIZE + BLOCK_SIZE) + ZONE_SIZE)
#define SMALL_PADDING_SIZE		(ZONE_SIZE - (USED_SMALL_ZONE_SIZE % ZONE_SIZE))
#define SMALL_ZONE_SIZE			(USED_SMALL_ZONE_SIZE + SMALL_PADDING_SIZE)

// ############### Structures ###############

typedef struct  s_zone
{
	size_t			size;
	size_t			nb_block;
	struct s_zone	*next;
	struct s_zone	*prev;
}				t_zone;

typedef struct	s_block
{
	bool			free;
	size_t			size;
	struct s_block	*next;
}				t_block;

// ############### Global variables ###############

extern t_zone	*g_zones = NULL;

// ############### Functions ###############

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);
void    show_alloc_mem();

t_zone	*create_zone(t_zone **zone, size_t size);

#endif