/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/01 09:55:34 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

void	print_error(char *message)
{
	printf("%s", message);

}
float	get_time(struct timeval *start)
{
	struct timeval	end;
	float			time_taken;

	gettimeofday(&end, NULL);

	time_taken = (
		(end.tv_sec - start->tv_sec) * 1000 +
		(end.tv_usec - start->tv_usec) / 1000
		);

	return (time_taken);
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

void	dongle_cooldown(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	usleep(dongle->dongle_cooldown * 1000);
	dongle->state = unused;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}

void    release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->state = cooldown;
	pthread_mutex_unlock(&dongle->lock);
	dongle_cooldown(dongle);
}
