/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 11:25:10 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/03 15:40:33 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODELS_H
#define MODELS_H

#include "parser.h"
#include "lib.h"

typedef	struct s_queue	t_queue;

typedef enum e_state
{
	unused,
	used,
	cooldown,
}	t_state;

typedef struct s_dongle
{
	unsigned int	id;
	unsigned int 	dongle_cooldown;
	unsigned int 	last_compile_time;
	t_state			state;
	t_queue			queue;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	unsigned int	id;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refractor;
	unsigned int	time_to_burnout;
	unsigned int	compile_required;
	unsigned int 	last_compile_time;
	unsigned int	*compile_done;
	unsigned int	*burnout;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread;
	pthread_mutex_t	*lock;
	struct timeval	*start;
}	t_coder;

typedef struct s_monitor
{
	unsigned int    total_compile;
    unsigned int    current_t;
    unsigned int    burnout_t;
    unsigned int    total_t;
	unsigned int	nb_coders;
	unsigned int	compile_required;
	unsigned int	*burnout;
	unsigned int	*compile_done;
	t_dongle		*dongles;
	t_coder			*coders;
	pthread_t		thread;
	pthread_mutex_t	lock;
	struct timeval	*start;
}	t_monitor;

typedef	struct s_queue
{
	unsigned int size;
	unsigned int head;
	unsigned int tail;
	t_coder		*coder_queue;
}	t_queue;

typedef struct s_simulation
{
	unsigned int	compile_done;
	unsigned int	burnout;
	t_args			*args;
	t_coder			*coders;
	t_dongle		*dongles;
	t_monitor		monitor;
	pthread_mutex_t	lock;
	struct timeval	start;
}	t_simulation;

#endif