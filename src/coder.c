/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:17:41 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/27 12:38:12 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"
#include "coder_routines.h"

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
		sim->coders[i].right_dongle = &sim->dongles[((i - 1)+ size) % size];
		sim->coders[i].time_to_compile = sim->args->time_to_compile;
		sim->coders[i].time_to_debug = sim->args->time_to_debug;
		sim->coders[i].time_to_refractor = sim->args->time_to_refractor;
		sim->coders[i].compile_required = sim->args->nb_of_compile_required;
		sim->coders[i].lock = &sim->lock;
		sim->coders[i].cond = &sim->cond;
	}
	return (0);
}

void *coder_routine(void *arg)
{
	t_coder 		*coder;
	unsigned int 	i;

	coder = (t_coder *) arg;
	i = -1;
	while (++i < coder->compile_required)
	{
		// acquire_dongles(coder);	// acquire dongles
		compile(coder);	// compile at t time
		// release_dongles(coder);	// release dongles
		debugging(coder);	// debug
		refractoring(coder);	// reafrator
	}
	return NULL;	
}

int coder_threads(t_simulation *sim)
{
	unsigned int	i;
	int 			rc;

	i = -1;
	while (++i < sim->args->nb_of_coders)
	{
		rc = pthread_create(
			&sim->coders[i].thread, NULL, coder_routine, &sim->coders[i]
		);
		if (rc)
			return(1);
	}
	return (0);
}
