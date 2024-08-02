/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axcallet <axcallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:37:41 by kufato            #+#    #+#             */
/*   Updated: 2024/08/01 14:31:38 by axcallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

// ############### Includes ###############

#include <stdio.h> // for the perror() function 
#include <stdbool.h> // for the 'bool' type
#include <sys/mman.h>
#include "../lib/libft/libft.h"

// ############### Defines ###############

#define ALIGN_64(x)				((x + 7) & ~0x07)
#define ALIGN_4096(x)			((x + 4095) & ~0xFFF)

#define PAGE_SIZE				((size_t) getpagesize())
#define	ZONE_SIZE				sizeof(t_zone)
#define BLOCK_SIZE				sizeof(t_block)

#define TINY_BLOCK_SIZE			((size_t) 128 + 16 - BLOCK_SIZE)
#define TINY_ZONE_SIZE			(100 * (TINY_BLOCK_SIZE + BLOCK_SIZE) + ZONE_SIZE)
#define ALIGN_TINY_ZONE_SIZE	ALIGN_4096(TINY_ZONE_SIZE + PAGE_SIZE)

#define SMALL_BLOCK_SIZE		((size_t) 1024 + 16 - BLOCK_SIZE)
#define SMALL_ZONE_SIZE			(100 * (SMALL_BLOCK_SIZE + BLOCK_SIZE) + ZONE_SIZE)
#define ALIGN_SMALL_ZONE_SIZE	ALIGN_4096(SMALL_ZONE_SIZE + PAGE_SIZE)

// ############### Structures ###############

typedef struct	s_zone	t_zone;
typedef struct	s_block	t_block;

struct	s_block
{
	bool	free;
	size_t	size;
	t_block	*next;
};

struct  s_zone
{
	size_t	size;
	t_zone	*next;
	t_block	*blocks;
};

// ############### Global variables ###############

extern t_zone	*g_zones;

// ############### Functions ###############

//     * Mandatory *
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();

//     * Blocks *
void	*find_block(size_t block_size, size_t zone_size);
t_block	*create_block(size_t block_size);
t_block	*add_block(t_zone *zone, size_t block_size);

//     * Zones *
bool	check_empty_zone(t_zone *zone);
t_zone	*search_zone_from_block(void *block);
t_zone	*create_zone(t_zone **zone, size_t size);

#endif