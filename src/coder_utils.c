/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:55:31 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/08 13:47:39 by ialrandr         ###   ########.fr       */
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

void    acquire_dongle(t_coder *coder, t_dongle *da, t_dongle *db)
{
    pthread_mutex_lock(&da->lock);
    pthread_mutex_lock(&db->lock);
    while (!*coder->burnout
        && !(heap_peek(&da->heap) == coder && da->state == unused
          && heap_peek(&db->heap) == coder && db->state == unused))
    {
        pthread_mutex_unlock(&db->lock);
        pthread_mutex_unlock(&da->lock);
        usleep(1);
        pthread_mutex_lock(&da->lock);
        pthread_mutex_lock(&db->lock);
    }
    if (!*coder->burnout)
    {
        heap_pop(&da->heap);
        heap_pop(&db->heap);
        da->state = used;
        db->state = used;
    }
    pthread_mutex_unlock(&db->lock);
    pthread_mutex_unlock(&da->lock);
    log_message(coder, "has taken a dongle");
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
