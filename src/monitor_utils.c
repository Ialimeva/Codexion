/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 20:13:53 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 10:29:41 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

void    change_dongle_state(t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    dongle->state = unused;
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->lock);
}

void    check_limits(t_monitor *m, t_dongle *d, t_coder *c)
{
    pthread_mutex_lock(&d->lock);
    m->total_t = d->dongle_cooldown + d->last_compile_time;
    pthread_mutex_unlock(&d->lock);
    pthread_mutex_lock(c->lock);
    m->burnout_t = c->time_to_burnout + c->last_compile_time;
    pthread_mutex_unlock(c->lock);
}

void    burnout(t_coder *coder, t_monitor *m)
{
    pthread_mutex_lock(coder->lock);
    *m->burnout = 1;
    pthread_mutex_unlock(coder->lock);
    printf("%d %d has burned out\n", m->current_t, coder->id);
}

int    end_monitor(t_monitor *m)
{
    pthread_mutex_lock(m->lock);
    if (*m->compile_done == m->total_compile || *m->burnout)
    {
        pthread_mutex_unlock(m->lock);
        return (1);
    }
    pthread_mutex_unlock(m->lock);
    return (0);
}

int	check_burnout(t_coder *coder)
{
	int	b;

	pthread_mutex_lock(coder->lock);
	b = *coder->burnout;
	pthread_mutex_unlock(coder->lock);
	return (b);
}
