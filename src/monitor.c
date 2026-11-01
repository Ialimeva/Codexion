/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:02:01 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/01 21:35:27 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "utils.h"

void    dongle_cooldown(t_monitor *monitor)
{
    unsigned int    i;
    unsigned int    total_compile;
    unsigned int    current_time;
    unsigned int    total_time;

    total_compile = monitor->nb_dongles * monitor->compile_required;
    while (1)
    {
        i = -1;
        current_time = get_time(monitor->start);
        while (++i < monitor->nb_dongles)
        {
            total_time = (
                monitor->dongles[i].dongle_cooldown +
                monitor->dongles[i].last_compile_time
                );
            if (monitor->dongles[i].state == cooldown && current_time == total_time)
            {
                pthread_mutex_lock(&monitor->dongles[i].lock);
                monitor->dongles[i].state = unused;
                pthread_cond_broadcast(&monitor->dongles[i].cond);
                pthread_mutex_unlock(&monitor->dongles[i].lock);
            }
        }
        if (*monitor->compile_done == total_compile)
            break;
        usleep(10);
    }
}

void *monitor_routine(void *arg)
{
    t_monitor    *monitor;

    monitor = (t_monitor *) arg;
    dongle_cooldown(monitor);
    return NULL;
}

int	monitor_init(t_simulation *sim)
{
    int rc;
    
    sim->monitor.dongles = sim->dongles;
    sim->monitor.nb_dongles = sim->args->nb_dongles;
    sim->monitor.compile_required = sim->args->nb_of_compile_required;
    sim->monitor.compile_done = &sim->compile_done;
    sim->monitor.start = &sim->start;
    pthread_mutex_init(&sim->monitor.lock, NULL);
	rc = pthread_create(
        &sim->monitor.thread, NULL, monitor_routine, &sim->monitor
        );
    
    if (rc)
        return (1);
    return (0);
}
