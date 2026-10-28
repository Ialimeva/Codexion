/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 11:09:59 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 15:19:42 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "utils.h"

void    acquire_dongles(t_coder *coder)
{
    acquire_dongle(coder, coder->left_dongle);
    acquire_dongle(coder, coder->right_dongle);
}

void    compile(t_coder *coder)
{
	unsigned int	timestamp;

    pthread_mutex_lock(coder->lock);
	timestamp = get_time(coder->start);
    printf("%d %d is compiling\n", timestamp, coder->id);
    pthread_mutex_unlock(coder->lock);
    usleep(coder->time_to_compile * 1000);
}

void    release_dongles(t_coder *coder)
{
    pthread_mutex_lock(coder->lock);
    coder->left_dongle->state = cooldown;
    coder->right_dongle->state = cooldown;
	dongle_cooldown(coder->left_dongle, coder);
	dongle_cooldown(coder->right_dongle, coder);
    pthread_mutex_unlock(coder->lock);
}

void    debugging(t_coder *coder)
{
	unsigned int	timestamp;

    pthread_mutex_lock(coder->lock);
	timestamp = get_time(coder->start);
    printf("%d %d is debugging\n", timestamp, coder->id);
    pthread_mutex_unlock(coder->lock);
    usleep(coder->time_to_debug * 1000);
}

void    refractoring(t_coder *coder)
{
	unsigned int	timestamp;

    pthread_mutex_lock(coder->lock);
	timestamp = get_time(coder->start);
    printf("%d %d is refractoring\n", timestamp, coder->id);
    pthread_mutex_unlock(coder->lock);
    usleep(coder->time_to_refractor * 1000);
}
