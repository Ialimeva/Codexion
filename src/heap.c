/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 08:36:11 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 09:20:53 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "lib.h"
#include "models.h"

t_coder	*heap_pop(t_heap *heap)
{
	t_coder	*coder;

	coder = NULL;
	if (heap->size > 0)
	{
		heap->size--;
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
	heap->queue[heap->size] = coder;
	heap->size++;
	if (heap->size > 1)
	{
		if (!strcmp(heap->scheduler, "fifo"))
			fifo(heap);
		else
			edf(heap);
	}
}

void	enqueue(t_coder *coder, t_dongle *first, t_dongle *second)
{
	pthread_mutex_lock(&first->lock);
	heap_push(&first->heap, coder);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_lock(&second->lock);
	heap_push(&second->heap, coder);
	pthread_mutex_unlock(&second->lock);
}
