/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 11:25:10 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 14:57:52 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODELS_H
#define MODELS_H

#include "parser.h"
#include "lib.h"

typedef enum e_state
{
	unused,
	used,
	cooldown,
}	t_state;

typedef struct s_minitor
{
	pthread_t		thread;
	pthread_cond_t	cooldown;
}	t_monitor;

typedef struct s_dongle
{
	unsigned int	id;
	unsigned int 	dongle_cooldown;
	t_state			state;
}	t_dongle;

typedef struct s_coder
{
	unsigned int	id;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refractor;
	unsigned int	compile_required;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_monitor		*monitor;
	pthread_t		thread;
	pthread_mutex_t	*lock;
	pthread_cond_t	*cond;
	struct timeval	*start;
}	t_coder;



typedef struct s_simulation
{
	t_args			*args;
	t_coder			*coders;
	t_dongle		*dongles;
	t_monitor		monitor;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	struct timeval	start;
}	t_simulation;

#endif