/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:22 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/04 10:46:48 by ialrandr         ###   ########.fr       */
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

unsigned int	queue_len(t_coder **queue)
{
	unsigned int i;

	i = 0;
	while (queue[i])
		i++;
	return (i);
}
