/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:30:27 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 19:49:20 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

void	free_dongles(t_simulation *sim)
{
	unsigned int	i;

	i = -1;
	while (++i < sim->args->nb_of_coders)
	{
		free(sim->dongles[i].heap.queue);
		pthread_mutex_destroy(&sim->dongles[i].lock);
		pthread_cond_destroy(&sim->dongles[i].cond);
	}
	free(sim->dongles);
}

void	free_sim(t_simulation *sim)
{
    free_dongles(sim);
    free(sim->coders);
    pthread_mutex_destroy(&sim->lock);
}
