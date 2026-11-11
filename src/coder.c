/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:17:41 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 10:30:32 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder_routines.h"
#include "lib.h"
#include "models.h"
#include "monitor.h"
#include "utils.h"

int	coders_init(t_simulation *sim)
{
	unsigned int	i;
	unsigned int	size;

	i = -1;
	size = sim->args->nb_of_coders;
	sim->coders = malloc(size * sizeof(t_coder));
	if (!sim->coders)
		return (1);
	while (++i < sim->args->nb_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].left_dongle = &sim->dongles[i];
		sim->coders[i].right_dongle = &sim->dongles[((i - 1) + size) % size];
		sim->coders[i].time_to_compile = sim->args->time_to_compile;
		sim->coders[i].time_to_debug = sim->args->time_to_debug;
		sim->coders[i].time_to_refractor = sim->args->time_to_refractor;
		sim->coders[i].time_to_burnout = sim->args->time_to_burnout;
		sim->coders[i].compile_required = sim->args->nb_of_compile_required;
		sim->coders[i].lock = &sim->lock;
		sim->coders[i].start = &sim->start;
		sim->coders[i].compile_done = &sim->compile_done;
		sim->coders[i].burnout = &sim->burnout;
		sim->coders[i].last_compile_time = 0;
	}
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder			*coder;
	unsigned int	i;

	coder = (t_coder *)arg;
	i = -1;
	if (coder->left_dongle == coder->right_dongle)
	{
		lonely_coder(coder);
		return (NULL);
	}
	if (coder->id % 2 == 0 && !strcmp(coder->left_dongle->scheduler, "edf"))
		smart_sleep(coder, coder->time_to_compile);
	while (++i < coder->compile_required && !check_burnout(coder))
	{
		acquire_dongles(coder);
		if (check_burnout(coder))
			break ;
		compile(coder);
		release_dongles(coder);
		debugging(coder);
		refractoring(coder);
	}
	return (NULL);
}

int	coder_threads(t_simulation *sim)
{
	unsigned int	i;
	int				rc;

	i = -1;
	while (++i < sim->args->nb_of_coders)
	{
		rc = pthread_create(&sim->coders[i].thread, NULL, coder_routine,
				&sim->coders[i]);
		if (rc)
			return (1);
	}
	return (0);
}
