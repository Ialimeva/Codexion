/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:34:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 09:16:17 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parser.h"
#include "models.h"
#include "simulation.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_simulation	simulation;

	if (parser(&argc, argv, &args))
		return (1);
	simulation.args = &args;
	simulation.compile_done = 0;
	simulation.burnout = 0;
	if (start_simulation(&simulation))
		return (1);
	return (0);
}
