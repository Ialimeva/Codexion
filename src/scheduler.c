/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 08:36:11 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/04 15:01:37 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "utils.h"

void	fifo(t_dongle	*dongle)
{
	t_coder *coder;

	coder = dongle->queue.coder_queue[dongle->queue.head];
	dongle->queue.chosen_coder = coder;
	dongle->queue.head = (dongle->queue.head + 1) % dongle->queue.size;
}

// void	edf(t_dongle *dongle)
// {
// 	unsigned int	i;
// 	unsigned int 	last_
// 	t_coder			*coder;
	
// 	i = -1;
// 	coder = dongle->queue.coder_queue[dongle->queue.head];
// 	while (++i < dongle->queue.size)
// 	{
// 		if (dongle->queue.coder_queue[i]->last_compile_time + )
// 	}
// }

void	scheduler(t_dongle *dongle)
{
	fifo(dongle);
	// if (!strcmp(dongle->scheduler, "fifo"))
	// else
	// 	edf(dongle);
}