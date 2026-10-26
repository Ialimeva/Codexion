/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:34:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 15:37:38 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parser.h"
#include "models.h"

int	main(int argc, char **argv)
{
	t_args			args;
	t_simulation	simulation;

	if (parser(&argc, argv, &args))
		return (1);
	simulation.args = &args;
	// run simulation
	printf("%d", args.time_to_debug);
	return (0);
}
