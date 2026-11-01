/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:40:19 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/01 19:20:22 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "dongle.h"
#include "coder.h"
#include "monitor.h"

// TODO: Add error message
int	start_simulation(t_simulation *sim)
{
	unsigned int	i;

	i = -1;
	gettimeofday(&sim->start, NULL);
	// TODO: Free the dongle if error on coders malloc
	if (dongles_init(sim) || coders_init(sim))
		return (1);
	pthread_mutex_init(&sim->lock, NULL);
	if (monitor_init(sim))
		return (1);
	if (coder_threads(sim))	// start coder threads (with t time for each action do not forget)
		return (1);
	// monitor
	while (++i < sim->args->nb_of_coders)
		pthread_join(sim->coders[i].thread, NULL);
	pthread_join(sim->monitor.thread, NULL);
	pthread_mutex_destroy(&sim->lock);
	free(sim->coders);
	free(sim->dongles);
	return (0);
}
