/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 09:27:06 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "monitor.h"

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

unsigned int	ft_strlen(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	smart_sleep(t_coder *coder, unsigned int ms)
{
	unsigned int	end;

	end = get_time(coder->start) + ms;
	while (!check_burnout(coder) && get_time(coder->start) < end)
		usleep(5);
}
