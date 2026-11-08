/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:17:28 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/07 21:51:09 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
#define HEAP_H

typedef struct s_coder   t_coder;
typedef struct s_dongle   t_dongle;

typedef struct s_heap
{
	unsigned int	size;
	unsigned int	queue_size;
	t_coder			**queue;
	char			*scheduler;
} 					t_heap;

t_coder			*heap_pop(t_heap *heap);
t_coder			*heap_peek(t_heap *heap);
void			heap_push(t_heap *heap, t_coder *coder);
void			enqueue(t_coder *coder, t_dongle *first, t_dongle *second);
t_heap			*fifo(t_heap *heap);
t_heap			*edf(t_heap *heap);

#endif