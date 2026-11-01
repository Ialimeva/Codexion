/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:39:05 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/01 20:38:19 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

int	dongles_init(t_simulation *sim)
{
	unsigned int	i;

	i = -1;
	sim->dongles = malloc(sim->args->nb_dongles * sizeof(t_dongle));
	if (!sim->dongles)
		return (1);
	while (++i < sim->args->nb_dongles)
	{
		sim->dongles[i].id = i + 1;
		sim->dongles[i].state = unused;
		sim->dongles[i].dongle_cooldown = sim->args->dongle_cooldown;
		sim->dongles[i].last_compile_time = 0;
		pthread_mutex_init(&sim->dongles[i].lock, NULL);
		pthread_cond_init(&sim->dongles[i].cond, NULL);
	}
	return (0);
}
