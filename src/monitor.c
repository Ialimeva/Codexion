/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:02:01 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/03 07:29:41 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "utils.h"
#include "coder.h"

void    change_dongle_state(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    dongle->state = unused;
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->lock);
}

void    routine(t_monitor *m)
{
    unsigned int    i;
    unsigned int    total_compile;
    unsigned int    current_t;
    unsigned int    burnout_t;
    unsigned int    total_t;
    
    total_compile = m->nb_coders * m->compile_required;
    while (1)
    {
        i = -1;
        current_t = get_time(m->start);
        while (++i < m->nb_coders)
        {
            total_t = (
                m->dongles[i].dongle_cooldown +
                m->dongles[i].last_compile_time
            );
            burnout_t = (
                m->coders[i].time_to_burnout +
                m->coders[i].last_compile_time
                );
            if (m->dongles[i].state == cooldown && current_t >= total_t)
                change_dongle_state(&m->dongles[i]);
            if (current_t >= burnout_t)
            {
                pthread_mutex_lock(m->coders[i].lock);
                *m->burnout = 1;
                printf("%d %d has burned out", current_t, m->coders[i].id);
                pthread_mutex_unlock(m->coders[i].lock);
                break;
            }
        }
        if (*m->compile_done == total_compile || *m->burnout)
            break;
        usleep(10);
    }
}

void *monitor_routine(void *arg)
{
    t_monitor    *monitor;

    monitor = (t_monitor *) arg;
    routine(monitor);
    return (NULL);
}

int	monitor_init(t_simulation *sim)
{
    int rc;
    
    sim->monitor.dongles = sim->dongles;
    sim->monitor.coders = sim->coders;
    sim->monitor.nb_coders = sim->args->nb_of_coders;
    sim->monitor.compile_required = sim->args->nb_of_compile_required;
    sim->monitor.compile_done = &sim->compile_done;
    sim->monitor.start = &sim->start;
    sim->monitor.burnout = &sim->burnout;
    pthread_mutex_init(&sim->monitor.lock, NULL);
	rc = pthread_create(
        &sim->monitor.thread, NULL, monitor_routine, &sim->monitor
        );
    
    if (rc)
        return (1);
    return (0);
}
