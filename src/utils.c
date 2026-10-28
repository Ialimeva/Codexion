/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 11:21:49 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

void	print_error(char *message)
{
	printf("%s", message);

}
void    acquire_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(coder->lock);
    while (dongle->state != unused)
        pthread_cond_wait(coder->cond, coder->lock);
    dongle->state = used;
    pthread_mutex_unlock(coder->lock);
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