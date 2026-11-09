/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialrandr <ialrandr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 12:02:05 by ialrandr          #+#    #+#             */
/*   Updated: 2026/11/09 21:20:47 by ialrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
#define MONITOR_H

#include "models.h"

int monitor_init(t_simulation *sim);
void    change_dongle_state(t_dongle *dongle);
void    check_limits(t_monitor *m, t_dongle *d, t_coder *c);
void    burnout(t_coder *coder, t_monitor *m);
int    end_monitor(t_monitor *m);

#endif