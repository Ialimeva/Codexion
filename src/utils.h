/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 10:46:54 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 10:44:10 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "models.h"

void	print_error(char *message);
float	get_time(struct timeval *start);
unsigned int	ft_strlen(char *str);
void	smart_sleep(t_coder *coder, unsigned int ms);

#endif