/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:55:31 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/06 14:15:27 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "utils.h"
#include "heap.h"

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
	// heap_push(&dongle->heap, coder);
    // while ((heap_peek(&dongle->heap) != coder || dongle->state != unused) && !*coder->burnout) // check if first coder in the queue is them
	// 	pthread_cond_wait(&dongle->cond, &dongle->lock);
	dongle->state = used;
	heap_pop(&dongle->heap);
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
