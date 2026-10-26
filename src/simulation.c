/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 12:40:19 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 15:56:53 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "dongle.h"
#include "coder.h"

void	start_simulation(t_simulation *sim)
{
	dongles_init(sim);
	coders_init(sim);
	pthread_mutex_init(&sim->lock, NULL);
	pthread_cond_init(&sim->cond, NULL);
	// start coder threads (with t time for each action do not forget)
	// monitor
}
