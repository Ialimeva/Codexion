/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 09:45:18 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/26 09:45:20 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct args
{
	unsigned int	nb_of_coders;
	unsigned int	nb_dongles;
	unsigned int	time_to_burnout;
	unsigned int	time_to_compile;
	unsigned int	time_to_debug;
	unsigned int	time_to_refractor;
	unsigned int	nb_of_compile_required;
	unsigned int	dongle_cooldown;
	char			*scheduler;
}					t_args;

int					parser(int *argc, char **argv, t_args *args);

#endif