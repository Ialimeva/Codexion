/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:02:01 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 21:20:09 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "lib.h"
#include "models.h"
#include "monitor.h"
#include "utils.h"

void	routine(t_monitor *m)
{
	unsigned int	i;
	t_state			state;

	while (1)
	{
		i = -1;
		m->current_t = get_time(m->start);
		while (++i < m->nb_coders)
		{
			check_limits(m, &m->dongles[i], &m->coders[i]);
			pthread_mutex_lock(&m->dongles[i].lock);
			state = m->dongles[i].state;
			pthread_mutex_unlock(&m->dongles[i].lock);
			if (state == cooldown && m->current_t >= m->total_t)
				change_dongle_state(&m->dongles[i]);
			if (m->current_t > m->burnout_t)
			{
				burnout(&m->coders[i], m);
				break ;
			}
		}
		if (end_monitor(m))
			break ;
		usleep(10);
	}
}

void	*monitor_routine(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	monitor->current_t = 0;
	monitor->burnout_t = 0;
	monitor->total_t = 0;
	monitor->total_compile = monitor->nb_coders * monitor->compile_required;
	routine(monitor);
	return (NULL);
}

int	monitor_init(t_simulation *sim)
{
	int	rc;

	sim->monitor.dongles = sim->dongles;
	sim->monitor.coders = sim->coders;
	sim->monitor.nb_coders = sim->args->nb_of_coders;
	sim->monitor.compile_required = sim->args->nb_of_compile_required;
	sim->monitor.compile_done = &sim->compile_done;
	sim->monitor.start = &sim->start;
	sim->monitor.burnout = &sim->burnout;
	sim->monitor.lock = &sim->lock;
	rc = pthread_create(&sim->monitor.thread, NULL, monitor_routine,
			&sim->monitor);
	if (rc)
		return (1);
	return (0);
}
