/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:45:08 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 09:22:51 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "heap.h"

t_heap	*fifo(t_heap *h)
{
	return (h);
}

t_heap	*edf(t_heap *h)
{
	unsigned int	c1;
	unsigned int	c2;
	t_coder			*coder;

	if (h->size > 1)
	{
		c1 = h->queue[0]->last_compile_time + h->queue[0]->time_to_burnout;
		c2 = h->queue[1]->last_compile_time + h->queue[1]->time_to_burnout;
		if (c1 > c2)
		{
			coder = h->queue[0];
			h->queue[0] = h->queue[1];
			h->queue[1] = coder;
		}
	}
	return (h);
}
