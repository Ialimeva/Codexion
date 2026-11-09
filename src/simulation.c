/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:40:19 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 19:47:48 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "dongle.h"
#include "coder.h"
#include "monitor.h"
#include "cleanup.h"

// TODO: Add error message
int	start_simulation(t_simulation *sim)
{
	unsigned int	i;

	i = -1;
	gettimeofday(&sim->start, NULL);
	if (dongles_init(sim))
		return (1);
	if (coders_init(sim))
	{
		free_dongles(sim);
		return (1);
	}
	pthread_mutex_init(&sim->lock, NULL);
	if (monitor_init(sim) || coder_threads(sim))
	{
		free_sim(sim);
		return (1);
	}
	pthread_join(sim->monitor.thread, NULL);
	while (++i < sim->args->nb_of_coders)
		pthread_join(sim->coders[i].thread, NULL);
	free_sim(sim);
	return (0);
}
