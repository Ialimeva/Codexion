/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 10:46:54 by ialrandr          #+#    #+#             */
/*   Updated: 2026/10/28 15:20:44 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "models.h"

void	print_error(char *message);
void    acquire_dongle(t_coder *coder, t_dongle *dongle);
float	get_time(struct timeval *start);
void	dongle_cooldown(t_dongle *dongle, t_coder *coder);

#endif