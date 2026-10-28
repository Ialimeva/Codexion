/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:40:19 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 11:14:56 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "dongle.h"
#include "coder.h"

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
	pthread_cond_init(&sim->cond, NULL);
	if (coder_threads(sim))	// start coder threads (with t time for each action do not forget)
		return (1);
	// monitor
	while (++i < sim->args->nb_of_coders)
		pthread_join(sim->coders[i].thread, NULL);
	pthread_mutex_destroy(&sim->lock);
	pthread_cond_destroy(&sim->cond);
	free(sim->coders);
	free(sim->dongles);
	return (0);
}
