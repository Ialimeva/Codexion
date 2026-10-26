/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:00 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 09:43:02 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "lib.h"
#include "parser.h"

// TODO: atoi long for impossible integers
int	validate_args(char **argv)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (strcmp(argv[i], "0") && atoi(argv[i]) <= 0)
			print_error("Only positive numbers allowed.");
		i++;
	}
	if (strcmp(argv[i], "fifo") && strcmp(argv[i], "edf"))
		print_error("Only fifo and edf are allowed.");
	return (0);
}

int	parser(int *argc, char **argv, t_args *args)
{
	if (*argc != 9)
		print_error("8 arguments only");
	if (!validate_args(argv))
	{
		args->nb_of_coders = atoi(argv[1]);
		args->nb_dongles = atoi(argv[1]);
		args->time_to_burnout = atoi(argv[2]);
		args->time_to_compile = atoi(argv[3]);
		args->time_to_debug = atoi(argv[4]);
		args->time_to_refractor = atoi(argv[5]);
		args->nb_of_compile_required = atoi(argv[6]);
		args->dongle_cooldown = atoi(argv[7]);
		args->scheduler = argv[8];
		return (0);
	}
	return (1);
}
