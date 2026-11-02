/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 15:50:30 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/02 11:39:12 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

#include "models.h"

int	coders_init(t_simulation *sim);
int coder_threads(t_simulation *sim);
void    acquire_dongle(t_coder *coder, t_dongle *dongle);
void    release_dongle(t_dongle *dongle);
void    update_compile_time(t_dongle *dongle, t_coder *coder);
void    log_message(t_coder *coder, char *message);

#endif
