/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 15:26:46 by ialrandr         ###   ########.fr       */
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
	int timestamp;

    pthread_mutex_lock(coder->lock);
    while (dongle->state != unused)
	{
        pthread_cond_wait(coder->cond, coder->lock);
	}
	dongle->state = used;
	timestamp = get_time(coder->start);
	printf("%d %d has taken a dongle\n", timestamp, coder->id);
    pthread_mutex_unlock(coder->lock);
}

void	dongle_cooldown(t_dongle *dongle, t_coder *coder)
{
	unsigned int	current_time;
	unsigned int	cooldown_duration;

	pthread_mutex_lock(coder->lock);
	current_time = get_time(coder->start);
	cooldown_duration = current_time + (dongle->dongle_cooldown * 1000);
	usleep(cooldown_duration);
	dongle->state = unused;
	pthread_mutex_unlock(coder->lock);
}