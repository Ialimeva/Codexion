/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 11:25:10 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 15:32:02 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef enum e_state
{
	free,
	used,
	cooldown,
}	t_state;

typedef struct s_coder
{
	unsigned int	id;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	pthread_t		thread;
}	t_coder;

typedef struct s_dongle
{
	unsigned int	id;
	t_state			state;
}	t_dongle;

typedef struct s_simulation
{
	t_args			*args;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
}	t_simulation;
