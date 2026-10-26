/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:34:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 10:12:15 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parser.h"

int	main(int argc, char **argv)
{
	t_args	args;

	parser(&argc, argv, &args);
	printf("%d", args.time_to_debug);
	return (0);
}
