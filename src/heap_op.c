/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:45:08 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/06 10:17:41 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "heap.h"

t_heap	*fifo(t_heap *heap)
{
	return (heap);
}

t_heap	*edf(t_heap *heap)
{
	unsigned int	c1;
	unsigned int	c2;
	t_coder			*coder;

	if (heap->size > 1)
	{
		c1 = heap->queue[0]->last_compile_time + heap->queue[0]->time_to_burnout;
		c2 = heap->queue[1]->last_compile_time + heap->queue[1]->time_to_burnout;
		if (c1 > c2)
		{
			coder = heap->queue[0];
			heap->queue[0] = heap->queue[1];
			heap->queue[1] = coder;
		}
	}
	return (heap);
}