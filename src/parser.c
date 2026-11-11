/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:43:00 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/11 09:27:39 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lib.h"
#include "parser.h"

int	validate_args(char **argv)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (ft_strlen(argv[i]) > 6)
		{
			printf("Only 6 digits allowed.\n");
			return (1);
		}
		if (strcmp(argv[i], "0") && atoi(argv[i]) <= 0)
		{
			printf("Only positive numbers allowed.\n");
			return (1);
		}
		i++;
	}
	if (strcmp(argv[i], "fifo") && strcmp(argv[i], "edf"))
	{
		printf("Only fifo and edf are allowed.\n");
		return (1);
	}
	return (0);
}

int	parser(int *argc, char **argv, t_args *args)
{
	if (*argc != 9)
	{
		printf("8 arguments only.\n");
		return (1);
	}
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
