/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:55:31 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/04 15:44:40 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "utils.h"
#include "scheduler.h"

void    log_message(t_coder *coder, char *message)
{
    if (!*coder->burnout)
    {
        unsigned int    timestamp;
    
        pthread_mutex_lock(coder->lock);
        timestamp = get_time(coder->start);
        printf("%d %d %s\n", timestamp, coder->id, message);
        pthread_mutex_unlock(coder->lock);
    }
}

void    acquire_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
	dongle->queue.coder_queue[dongle->queue.tail] = coder;
	dongle->queue.tail = (dongle->queue.tail + 1) % dongle->queue.size;
	// arrange queue depending on fifo or edf with the dongle lock on
	scheduler(dongle);
	// read head element wihtout pop
    while ((dongle->state != unused || dongle->queue.chosen_coder != coder) && !*coder->burnout) // check if the value at head is the coder
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	dongle->state = used;
    pthread_mutex_unlock(&dongle->lock);
    log_message(coder, "has taken a dongle");
}

void    release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->state = cooldown;
	pthread_mutex_unlock(&dongle->lock);
}

void    update_compile_time_dongle(t_dongle *dongle, t_coder *coder)
{
    unsigned int    current_t;
    
    current_t = get_time(coder->start);
    pthread_mutex_lock(&dongle->lock);
    dongle->last_compile_time = current_t;
    pthread_mutex_unlock(&dongle->lock);
}

void    update_compile_time_coder(t_coder *coder)
{
    unsigned int    current_t;
    
    current_t = get_time(coder->start);
    pthread_mutex_lock(coder->lock);
    coder->last_compile_time = current_t;
    pthread_mutex_unlock(coder->lock);
}
