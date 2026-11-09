/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 11:30:27 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 12:04:03 by ialrandr         ###   ########.fr       */
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

void    burnout_wake(t_simulation *sim)
{
    unsigned int i;

    i = -1;
    while (i < sim->args->nb_dongles)
    {
        pthread_mutex_lock(&sim->dongles[i].lock);
        pthread_cond_broadcast(&sim->dongles[i].cond);
        pthread_mutex_unlock(&sim->dongles[i].lock);
    }
}
