/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:34:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 11:14:18 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parser.h"
#include "models.h"
#include "simulation.h"

// TODO: Add error message
int	main(int argc, char **argv)
{
	t_args			args;
	t_simulation	simulation;

	if (parser(&argc, argv, &args))
		return (1);
	simulation.args = &args;
	if (start_simulation(&simulation))
		return (1);
	return (0);
}
