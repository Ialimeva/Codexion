/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 10:17:28 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/06 13:48:40 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
#define HEAP_H

typedef struct s_coder   t_coder;

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
t_heap			*fifo(t_heap *heap);
t_heap			*edf(t_heap *heap);

#endif