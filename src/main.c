/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:34:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 10:49:49 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "parser.h"

int	main(int argc, char **argv)
{
	t_args	args;

	if (parser(&argc, argv, &args))
		return (1);
	printf("%d", args.time_to_debug);
	return (0);
}
