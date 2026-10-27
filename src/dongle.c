/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:39:05 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/27 12:09:44 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

int	dongles_init(t_simulation *sim)
{
	unsigned int	i;

	i = -1;
	sim->dongles = malloc(sim->args->nb_dongles * sizeof(t_dongle));
	if (!sim->dongles)
		return (1);
	while (++i < sim->args->nb_dongles)
	{
		sim->dongles[i].id = i + 1;
		sim->dongles[i].state = unused;
	}
	return (0);
}
