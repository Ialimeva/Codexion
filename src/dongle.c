/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:39:05 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 11:40:50 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

int	dongles_init(t_simulation *sim)
{
	unsigned int	i;
	unsigned int	q_size;

	i = -1;
	q_size = 2;
	sim->dongles = malloc(sim->args->nb_dongles * sizeof(t_dongle));
	if (!sim->dongles)
		return (1);
	while (++i < sim->args->nb_dongles)
	{
		sim->dongles[i].id = i + 1;
		sim->dongles[i].state = unused;
		sim->dongles[i].dongle_cooldown = sim->args->dongle_cooldown;
		sim->dongles[i].last_compile_time = 0;
		sim->dongles[i].scheduler = sim->args->scheduler;
		sim->dongles[i].heap.scheduler = sim->args->scheduler;
		sim->dongles[i].heap.queue_size = q_size;
		sim->dongles[i].heap.size = 0;
		sim->dongles[i].heap.queue = malloc(q_size * sizeof(t_coder *));
		memset(sim->dongles[i].heap.queue, 0, q_size * sizeof(t_coder *));
		pthread_mutex_init(&sim->dongles[i].lock, NULL);
	}
	return (0);
}
