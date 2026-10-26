/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:17:41 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 15:54:28 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "models.h"

int	coders_init(t_simulation *sim)
{
	int	i;
	int	rc;
	int	size;

	i = -1;
	size = sim->args->nb_of_coders;
	sim->coders = malloc(size * sizeof(t_coder));
	if (!sim->coders)
		return (1);
	while (++i < sim->args->nb_of_coders)
	{
		sim->coders[i].id = i + 1;
		sim->coders[i].left_dongle = &sim->dongles[i];
		sim->coders[i].right_dongle = &sim->dongles[(i % size) + size];
	}
	return (0);
}
