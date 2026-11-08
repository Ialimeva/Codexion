/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:02:01 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/07 17:31:28 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "utils.h"
#include "coder.h"

static void    change_dongle_state(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    dongle->state = unused;
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->lock);
}
static void    check_limits(t_monitor *m, t_dongle *d, t_coder *c)
{
    m->total_t = d->dongle_cooldown + d->last_compile_time;
    m->burnout_t = c->time_to_burnout + c->last_compile_time;
}

void    routine(t_monitor *m)
{
    unsigned int    i;
    
    while (1)
    {
        i = -1;
        m->current_t = get_time(m->start);
        while (++i < m->nb_coders)
        {
            check_limits(m, &m->dongles[i], &m->coders[i]);
            if (m->dongles[i].state == cooldown && m->current_t >= m->total_t)
                change_dongle_state(&m->dongles[i]);
            if (m->current_t >= m->burnout_t)
            {
                pthread_mutex_lock(m->coders[i].lock);
                *m->burnout = 1;
                printf("%d %d has burned out\n", m->current_t, m->coders[i].id);
                pthread_mutex_unlock(m->coders[i].lock);
                break;
            }
        }
        if (*m->compile_done == m->total_compile || *m->burnout)
            break;
        usleep(10);
    }
}

void *monitor_routine(void *arg)
{
    t_monitor    *monitor;

    monitor = (t_monitor *) arg;
    monitor->current_t = 0;
    monitor->burnout_t = 0;
    monitor->total_t = 0;
    monitor->total_compile = monitor->nb_coders * monitor->compile_required;
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
