/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 08:36:11 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/05 16:10:49 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "lib.h"
#include "models.h"

unsigned int	queue_size(t_coder **queue)
{
	unsigned int	i;

	i = 0;
	while (queue[i])
		i++;
	return (i);
}

t_coder	*heap_pop(t_heap *heap)
{
	t_coder *coder;
	
	coder = NULL;
	if (queue_size(heap->queue) > 0)
	{
		coder = heap->queue[0];
		if (heap->queue[1])
		{
			heap->queue[0] = heap->queue[1];
			heap->queue[1] = NULL;
		}
		else
			heap->queue[0] = NULL;
	}
	return (coder);
}

t_coder	*heap_peek(t_heap *heap)
{
	return (heap->queue[0]);
}

void	heap_push(t_heap *heap, t_coder *coder)
{
	heap->size = queue_size(heap->queue);
	heap->queue[heap->size] = coder;
	if (queue_size(heap->queue) > 1)
	{
		// comparaison function
		if (!strcmp(heap->scheduler, "fifo"))
			fifo(heap);
		else
			edf(heap);
	}
}