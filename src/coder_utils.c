/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 10:55:31 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/02 11:38:23 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models.h"
#include "lib.h"
#include "utils.h"

void    log_message(t_coder *coder, char *message)
{
    unsigned int    timestamp;

    pthread_mutex_lock(coder->lock);
    timestamp = get_time(coder->start);
    printf("%d %d %s\n", timestamp, coder->id, message);
    pthread_mutex_unlock(coder->lock);

}

void    acquire_dongle(t_coder *coder, t_dongle *dongle)
{
	unsigned int	timestamp;

    pthread_mutex_lock(&dongle->lock);
    while (dongle->state != unused)
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	dongle->state = used;
	timestamp = get_time(coder->start);
	printf("%d %d has taken a dongle\n", timestamp, coder->id);
    pthread_mutex_unlock(&dongle->lock);
}

void    release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->state = cooldown;
	pthread_mutex_unlock(&dongle->lock);
}

void    update_compile_time(t_dongle *dongle, t_coder *coder)
{
    pthread_mutex_lock(&dongle->lock);
    dongle->last_compile_time = get_time(coder->start);
    pthread_mutex_unlock(&dongle->lock);
}
